#ifndef __TREE_H__
#define __TREE_H__

#define MAX_N_CHILD	10

#define TN_ROOT
#define TN_FUNC
#define TN_VAR
#define TN_EXPR_BI_LOGIC
#define TN_EXPR_BI_ARITH
#define TN_EXPR_UNI_LOGIC
#define TN_EXPR_UNI_ARITH
#define TN_EXPR_ASSN_VAR2VAR
#define TN_EXPR_ASSN_VAR2ARR
#define TN_EXPR_ASSN_ARR2VAR
#define TN_EXPR_IF_GOTO
#define TN_EXPR_GOTO
#define TN_EXPR_LABEL
#define TN_EXPR_PARAM
#define TN_EXPR_CALL
#define TN_EXPR_RETURN
#define TN_NUM
#define TN_LABEL
#define TN_ID

struct TreeNode
{
	int idx;
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
struct TreeNOde* alloc_treenode(int, char*, int);

#endif
