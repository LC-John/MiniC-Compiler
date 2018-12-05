#include "flowgraph.h"

map<TreeNode *, InsGraphNode *> InsGraph::ins2Node;
vector<InsGraphNode *> InsGraph::insVector;

void InsGraph::AddEdge(TreeNode *u, TreeNode *v) {
    ins2Node[u]->succ.insert(ins2Node[v]);
    ins2Node[v]->pred.insert(ins2Node[u]);
}

void InsGraph::InsertGraphNode(TreeNode *u) {
    if (ins2Node.find(u) == ins2Node.end()) {
        ins2Node[u] = new InsGraphNode();
        ins2Node[u]->instruction = u;
        insVector.push_back(ins2Node[u]);
    }
}

InsGraphNode *InsGraph::LookupInsGraphNode(TreeNode *u) {
    if (ins2Node.find(u) == ins2Node.end()) {
        return nullptr;
    }
    return ins2Node[u];
}

void InsGraph::LivenessAnalysis() {
    bool repeat = true;

    while (repeat) {
        repeat = false;

        for (InsGraphNode *insNode : insVector) {
            set<int> set_result;
            set<int> tempIn = insNode->liveIn;
            set<int> tempOut = insNode->liveOut;

            set<int> &in = insNode->liveIn;
            set<int> &out = insNode->liveOut;
            set<int> &def = insNode->def;
            set<int> &use = insNode->use;

	    // [IN] = ([OUT] / [DEF]) U [USE]
            set_result.clear();
            set_difference(out.begin(), out.end(), def.begin(), def.end(),
                           inserter(set_result, set_result.begin()));
	    in = set_result;
	    set_result.clear();
            set_union(use.begin(), use.end(), in.begin(), in.end(),
                           inserter(set_result, set_result.begin()));
			in = set_result;

            out.clear();
            for (InsGraphNode *succ : insNode->succ) {
				set_result.clear();
                set_union(succ->liveIn.begin(), succ->liveIn.end(), out.begin(),
                          out.end(), inserter(set_result, set_result.begin()));
				out = set_result;
            }

	    // Fixed point
            if (!equal(in.begin(), in.end(), tempIn.begin(), tempIn.end())) {
                repeat = true;
            }
            if (!equal(out.begin(), out.end(), tempOut.begin(),
                       tempOut.end())) {
                repeat = true;
            }
        }
    }
}
