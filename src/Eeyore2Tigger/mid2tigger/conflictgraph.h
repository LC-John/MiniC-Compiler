#ifndef __CONFLICTGRAPH_H__
#define __CONFLICTGRAPH_H__

#include "mid2tigger.tab.h"
#include "flowgraph.h"
#include "symtab.h"
#include "tree.h"
#include "op.h"

// Conflict graph
class Graph {
  public:
    static const int K = 20;

    set<pair<int, int>> adjSet;
    map<int, set<int>> adjList;
    map<int, int> degree;
    map<int, set<InsGraphNode *>> moveList;
    map<int, int> alias;
    map<int, int> color;

    set<int> precolored;
    set<int> initial;
    set<int> simplifyWorkList;
    set<int> freezeWorkList;
    set<int> spillWorkList;
    set<int> spilledNodes;
    set<int> coalescedNodes;
    set<int> coloredNodes;
    vector<int> SelectStack;

    set<InsGraphNode *> coalescedMoves;
    set<InsGraphNode *> constrainedMoves;
    set<InsGraphNode *> frozenMoves;
    set<InsGraphNode *> worklistMoves;
    set<InsGraphNode *> activeMoves;
    void Build();
    void AddEdge(int u, int v);
    void MakeWorkList();
    set<int> Adjacent(int n);
    set<InsGraphNode *> NodeMoves(int n);
    bool MoveRelated(int n);
    void Simplify();
    void DecrementDegree(int m);
    void EnableMoves(set<int> nodes);
    void Coalesce();
    bool AdjacentOK(int u, int v);
    void AddWorkList(int u);
    bool OK(int t, int r);
    bool Conservative(set<int> nodes);
    int GetAlias(int n);
    void Combine(int u, int v);
    void Freeze();
    void FreezeMoves(int u);
    void SelectSpill();
    void Precolored();
    void AssignColors();
    bool RewriteProgram();

    void Init();
    bool Main();
};


#endif
