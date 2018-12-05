#include "conflictgraph.h"

extern vector<TreeNode *> gramma_sequence;
extern vector<TreeNode *> worklist_sequence;

void Graph::Build() {
    set<int> set_result;

    precolored = SymTable::precolored;	// Pre-colored in Mid
    initial = SymTable::initial;	// Variables

    for (InsGraphNode *ins : InsGraph::insVector) {
	// Flow analysis (IN, OUT, DEF, USE)
        set<int> &out = ins->liveOut;
        set<int> &def = ins->def;
        set<int> &use = ins->use;
	// Where OUT is the live set
        set<int> live = out;

        if (ins->instruction->isMoveIns()) {
            set_result.clear();
            set_difference(live.begin(), live.end(), use.begin(), use.end(),
                           inserter(set_result, set_result.begin()));
            live = set_result;

            for (int n : def) {
                moveList[n].insert(ins);
            }
            for (int n : use) {
                moveList[n].insert(ins);
            }

            worklistMoves.insert(ins);
        }

        set_result.clear();
        set_union(live.begin(), live.end(), def.begin(), def.end(),
                  inserter(set_result, set_result.begin()));
        live = set_result;

        for (int d : def) {
            for (int l : live) {
                AddEdge(l, d);
            }
        }
    }
}

void Graph::AddEdge(int u, int v) {
    if (u == v) {
        return;
    }

    pair<int, int> uvPair = make_pair(u, v);
    pair<int, int> vuPair = make_pair(v, u);

    if (adjSet.find(uvPair) != adjSet.end()) {
        return;
    }

    adjSet.insert(uvPair);
    adjSet.insert(vuPair);

    if (precolored.count(u) == false) {
        adjList[u].insert(v);
        degree[u] = degree[u] + 1;
    }
    if (precolored.count(v) == false) {
        adjList[v].insert(u);
        degree[v] = degree[v] + 1;
    }
}

void Graph::MakeWorkList() {
    for (int n : initial) {
        if (degree[n] >= K) {
            spillWorkList.insert(n);
        } else if (MoveRelated(n)) {
            freezeWorkList.insert(n);
        } else {
            simplifyWorkList.insert(n);
        }
    }
}

set<int> Graph::Adjacent(int n) {
    set<int> set_result;
    set<int> adjacent = coalescedNodes;

    for (int m : SelectStack) {
        adjacent.insert(m);
    }

    set_result.clear();
    set_difference(adjList[n].begin(), adjList[n].end(), adjacent.begin(),
                   adjacent.end(), inserter(set_result, set_result.begin()));
    adjacent = set_result;

    return adjacent;
}

set<InsGraphNode *> Graph::NodeMoves(int n) {
    set<InsGraphNode *> set_result;
    set<InsGraphNode *> nodeMoves;

    set_result.clear();
    set_union(activeMoves.begin(), activeMoves.end(), worklistMoves.begin(),
              worklistMoves.end(), inserter(set_result, set_result.begin()));
    nodeMoves = set_result;

    set_result.clear();
    set_intersection(moveList[n].begin(), moveList[n].end(), nodeMoves.begin(),
                     nodeMoves.end(), inserter(set_result, set_result.begin()));
    nodeMoves = set_result;

    return nodeMoves;
}

bool Graph::MoveRelated(int n) { return !NodeMoves(n).empty(); }

void Graph::Simplify() {
    int n = *simplifyWorkList.begin();

    simplifyWorkList.erase(n);

    SelectStack.push_back(n);

    for (int m : Adjacent(n)) {
        DecrementDegree(m);
    }
}

void Graph::DecrementDegree(int m) {
    int d = degree[m];
    degree[m] = d - 1;

    if (d == K) {
        set<int> enable = Adjacent(m);
        enable.insert(m);
        EnableMoves(enable);

        spillWorkList.erase(m);

        if (MoveRelated(m)) {
            freezeWorkList.insert(m);
        } else {
            simplifyWorkList.insert(m);
        }
    }
}

void Graph::EnableMoves(set<int> nodes) {
    for (int n : nodes) {
        for (InsGraphNode *m : NodeMoves(n)) {
            if (activeMoves.count(m)) {
                activeMoves.erase(m);
                worklistMoves.insert(m);
            }
        }
    }
}

void Graph::Coalesce() {
    InsGraphNode *m = *worklistMoves.begin();

    int x = *(m->def.begin());
    int y = *(m->use.begin());

    x = GetAlias(x);
    y = GetAlias(y);

    int u, v;
    if (precolored.count(y)) {
        u = y;
        v = x;
    } else {
        u = x;
        v = y;
    }

    worklistMoves.erase(m);

    set<int> set_result;
    set<int> adjacent;
    set<int> adjacent_u = Adjacent(u);
    set<int> adjacent_v = Adjacent(v);

    set_result.clear();
    set_union(adjacent_u.begin(), adjacent_u.end(), adjacent_v.begin(),
              adjacent_v.end(), inserter(set_result, set_result.begin()));
    adjacent = set_result;

    if (u == v) {
        coalescedMoves.insert(m);
        AddWorkList(u);
    } else if (precolored.count(v) || adjSet.count(make_pair(u, v))) {
        constrainedMoves.insert(m);
        AddWorkList(u);
        AddWorkList(v);
    } else if (precolored.count(u) && AdjacentOK(u, v) ||
               !precolored.count(u) && Conservative(adjacent)) {
        coalescedMoves.insert(m);
        Combine(u, v);
        AddWorkList(u);
    } else {
        activeMoves.insert(m);
    }
}

bool Graph::AdjacentOK(int u, int v) {
    for (int t : Adjacent(v)) {
        if (!OK(t, u)) {
            return false;
        }
    }
    return true;
}

void Graph::AddWorkList(int u) {
    if (!precolored.count(u) && !MoveRelated(u) && degree[u] < K) {
        freezeWorkList.erase(u);
        simplifyWorkList.insert(u);
    }
}

bool Graph::OK(int t, int r) {
    return degree[t] < K || precolored.count(t) ||
           adjSet.count(make_pair(t, r));
}

bool Graph::Conservative(set<int> nodes) {
    int k = 0;
    for (int n : nodes) {
        if (degree[n] >= K) {
            k = k + 1;
        }
    }
    return k < K;
}

int Graph::GetAlias(int n) {
    if (coalescedNodes.count(n)) {
        return GetAlias(alias[n]);
    } else {
        return n;
    }
}

void Graph::Combine(int u, int v) {
    set<InsGraphNode *> set_result;

    if (freezeWorkList.count(v)) {
        freezeWorkList.erase(v);
    } else {
        spillWorkList.erase(v);
    }
    coalescedNodes.insert(v);

    alias[v] = u;

    set_result.clear();
    set_union(moveList[u].begin(), moveList[u].end(), moveList[v].begin(),
              moveList[v].end(), inserter(set_result, set_result.begin()));
    moveList[u] = set_result;

    EnableMoves({v});

    for (int t : Adjacent(v)) {
        AddEdge(t, u);
        DecrementDegree(t);
    }
    if (degree[u] >= K && freezeWorkList.count(u)) {
        freezeWorkList.erase(u);
        spillWorkList.insert(u);
    }
}

void Graph::Freeze() {
    int u = *freezeWorkList.begin();

    freezeWorkList.erase(u);
    simplifyWorkList.insert(u);
    FreezeMoves(u);
}

void Graph::FreezeMoves(int u) {
    for (InsGraphNode *m : worklistMoves) {
        int x = *m->def.begin();
        int y = *m->use.begin();

        int v;
        if (GetAlias(y) == GetAlias(u)) {
            v = GetAlias(x);
        } else {
            v = GetAlias(y);
        }

        activeMoves.erase(m);
        frozenMoves.insert(m);

        if (NodeMoves(v).empty() && degree[v] < K) {
            freezeWorkList.erase(v);
            simplifyWorkList.insert(v);
        }
    }
}

void Graph::SelectSpill() {
    int m = *spillWorkList.begin();

    spillWorkList.erase(m);
    simplifyWorkList.insert(m);
    FreezeMoves(m);
}

void Graph::Precolored() {
    SymTable::Precolored();
    for (int n : precolored) {
        color[n] = SymTable::reg2color[SymTable::index2var[n]];
    }
}

void Graph::AssignColors() {
    Precolored();

    while (SelectStack.size()) {
        int n = SelectStack[SelectStack.size() - 1];
        SelectStack.pop_back();

        set<int> okColors;
        for (int i = 1; i <= K; i++) {
            okColors.insert(i);
        }

        for (int w : adjList[n]) {
            if (coloredNodes.count(GetAlias(w)) ||
                precolored.count(GetAlias(w))) {
                okColors.erase(color[GetAlias(w)]);
            }
        }

        if (okColors.empty()) {
            spilledNodes.insert(n);
        } else {
            coloredNodes.insert(n);
            int c = *okColors.begin();
            color[n] = c;
        }
    }

    for (int n : coalescedNodes) {
        color[n] = color[GetAlias(n)];
    }
}

bool Graph::RewriteProgram() {
    DisplaySet("Spill:", spilledNodes);

	SymTable::SpillVariable(spilledNodes);

	worklist_sequence.clear();
	for (TreeNode *ins : gramma_sequence) {
		set<int> load = ins->GetLoadSymbol();
		set<int> store = ins->GetStoreSymbol();

		for (int n : load) {
			string varia = SymTable::index2var[n];

			TreeNode *loadNode = new StmNode(LOADVL_KIND);
			loadNode->child[0] = new LocvrExpNode(varia);

			worklist_sequence.push_back(loadNode);
		}

		worklist_sequence.push_back(ins);

		for (int n : store) {
			string varia = SymTable::index2var[n];

			TreeNode *loadNode = new StmNode(STORVL_KIND);
			loadNode->child[0] = new LocvrExpNode(varia);

			worklist_sequence.push_back(loadNode);
		}
	}

	return spilledNodes.empty();
}

void Graph::Init() {
    adjSet.clear();
    adjList.clear();
    degree.clear();
	moveList.clear();
	alias.clear();
	color.clear();

	precolored.clear();
	initial.clear();
	simplifyWorkList.clear();
	freezeWorkList.clear();
	spillWorkList.clear();
	spilledNodes.clear();
	coalescedNodes.clear();
	coloredNodes.clear();
	SelectStack.clear();

	coalescedMoves.clear();
	constrainedMoves.clear();
	frozenMoves.clear();
	worklistMoves.clear();
	activeMoves.clear();
}

bool Graph::Main() {
	Init();

    Build();
    MakeWorkList();

    bool repeat = true;
    while (repeat) {
        if (!simplifyWorkList.empty()) {
            Simplify();
        } else if (!worklistMoves.empty()) {
            Coalesce();
        } else if (!freezeWorkList.empty()) {
            Freeze();
        } else if (!spillWorkList.empty()) {
            SelectSpill();
        }

        repeat = false;
        if (!simplifyWorkList.empty()) {
            repeat = true;
        }
        if (!worklistMoves.empty()) {
            repeat = true;
        }
        if (!freezeWorkList.empty()) {
            repeat = true;
        }
        if (!spillWorkList.empty()) {
            repeat = true;
        }
    }

    AssignColors();
    return RewriteProgram();
}
