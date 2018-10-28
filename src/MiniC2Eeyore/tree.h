#ifndef __TREE_H__
#define __TREE_H__

#include <stdio.h>

#define TN_MAX_CHILD_NUMBER	5

#define TN_INIT			0
#define TN_ROOT			1
#define TN_FUNCDEFN		3
#define TN_FUNCDECL		4
#define TN_VARDEFN		6
#define TN_VARDECL		7
#define TN_STMT_BLOCK		100
#define TN_STMT_IF		101
#define TN_STMT_WHILE		102
#define TN_STMT_VARASSN		103
#define TN_STMT_ARRASSN		104
#define TN_STMT_VARDEFN		105
#define TN_STMT_RETURN		106
#define TN_EXPR_BIARITH		1001
#define TN_EXPR_BILOGIC		1002
#define TN_EXPR_ARR		1003
#define TN_EXPR_INTEGER		1004
#define TN_EXPR_IDENTIFIER	1005
#define TN_EXPR_UNI		1006
#define TN_EXPR_CALL		1007
#define TN_TYPE			501
#define TN_INTEGER		502
#define TN_IDENTIFIER		503

#define N_CHILD_INIT			0
#define N_CHILD_ROOT			2
#define N_CHILD_FUNCDEFN		4
#define N_CHILD_FUNCDECL		3
#define N_CHILD_VARDEFN			3
#define N_CHILD_VARDECL			3
#define N_CHILD_STMT_BLOCK		1
#define N_CHILD_STMT_IF			3
#define N_CHILD_STMT_WHILE		2
#define N_CHILD_STMT_VARASSN		2
#define N_CHILD_STMT_ARRASSN		3
#define N_CHILD_STMT_VARDEFN		1
#define N_CHILD_STMT_RETURN		1
#define N_CHILD_EXPR_BIARITH		2
#define N_CHILD_EXPR_BILOGIC		2
#define N_CHILD_EXPR_ARR		2
#define N_CHILD_EXPR_INTEGER		1
#define N_CHILD_EXPR_IDENTIFIER		1
#define N_CHILD_EXPR_UNI		1
#define N_CHILD_EXPR_CALL		2
#define N_CHILD_TYPE			0
#define N_CHILD_INTEGER			0
#define N_CHILD_IDENTIFIER		0

int n_treenode;

struct TreeNode
{
	int idx;
	int lineno;
	int type;
	int val;
	char* name;
	int n_child;
	int child_idx;
	struct TreeNode* parent;
	struct TreeNode* child[TN_MAX_CHILD_NUMBER];
	struct TreeNode* sibling_l;
	struct TreeNode* sibling_r;
};

struct TreeNode* alloc_treenode(int, int, char*);
void free_treenode(struct TreeNode*);
void print_treenode(struct TreeNode*, char*, FILE*);

void init_tree();
void print_tree(struct TreeNode*, int, FILE*);

#endif
