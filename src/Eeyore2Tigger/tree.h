#ifndef __TREE_H__
#define __TREE_H__

#include <stdio.h>

#define MAX_N_CHILD	5

#define TN_INIT			0
#define TN_ROOT			1
#define TN_FUNC			2
#define TN_VAR			3
#define TN_EXPR_BI_LOGIC	100
#define TN_EXPR_BI_ARITH	101
#define TN_EXPR_UNI_LOGIC	102
#define TN_EXPR_UNI_ARITH	103
#define TN_EXPR_ASSN		104
#define TN_EXPR_IF_GOTO		105
#define TN_EXPR_GOTO		106
#define TN_EXPR_LABEL		107
#define TN_EXPR_PARAM		108
#define TN_EXPR_CALL		109
#define TN_EXPR_RETURN		110
#define TN_NUM			1000
#define TN_ID			1001

#define OP_ASSN	0
#define OP_AND	1
#define OP_OR	2
#define OP_EQ	3
#define OP_NE	4
#define OP_GT	5
#define OP_LT	6
#define OP_ADD	100
#define OP_SUB	101
#define OP_MUL	102
#define OP_DIV	103
#define OP_MOD	104
#define OP_NOT	1000
#define OP_POS	3000
#define OP_NEG	3001

struct TreeNode
{
	int idx;
	int lineno;
	int type;
	char* str;
	int val;
	int n_child;
	struct TreeNode* parent;
	struct TreeNode* child[MAX_N_CHILD];
	struct TreeNode* nxt;
	struct TreeNode* prv;
};

int n_treenode;

void init_tree();
struct TreeNode* alloc_treenode(int, char*, int);	// (NodeType, NodeStr, NodeVal)
void free_treenode(struct TreeNode*);	// (Node2BFreed)

void print_tree(struct TreeNode*, int, FILE*);	// (RootNodeOfTree2BPrinted, CurrentDepth, OutputFile)

#endif
