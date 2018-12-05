#ifndef __FLOWGRAPH_H__
#define __FLOWGRAPH_H__

#include "tree.h"
#include "op.h"

class InsGraphNode {
  public:
    TreeNode *instruction;

    set<InsGraphNode *> pred;
    set<InsGraphNode *> succ;

    set<int> def;
    set<int> use;
    set<int> liveIn;
    set<int> tempIn;
    set<int> liveOut;
    set<int> tempOut;
};

class InsGraph {
  public:
    static map<TreeNode *, InsGraphNode *> ins2Node;
    static vector<InsGraphNode *> insVector;

    static void InsertGraphNode(TreeNode *u);
    static void AddEdge(TreeNode *u, TreeNode *v);
    static InsGraphNode *LookupInsGraphNode(TreeNode *u);
    static void LivenessAnalysis();
};

#endif
