#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

struct TreeNode* alloc_treenode(int arg_lineno, int arg_type, char* arg_name)
{
	struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	node->idx = n_treenode++;
	node->lineno = arg_lineno;
	node->type = arg_type;
	node->val = -1;
	node->name = arg_name;
	node->child_idx = -1;
	switch(node->type)
	{
	case TN_ROOT:		node->n_child = N_CHILD_ROOT; break;
	case TN_FUNCDEFN:	node->n_child = N_CHILD_FUNCDEFN; break;
	case TN_FUNCDECL:	node->n_child = N_CHILD_FUNCDECL; break;
	case TN_VARDEFN:	node->n_child = N_CHILD_VARDEFN; break;
	case TN_VARDECL:	node->n_child = N_CHILD_VARDECL; break;
	case TN_STMT_BLOCK:	node->n_child = N_CHILD_STMT_BLOCK; break;
	case TN_STMT_IF:	node->n_child = N_CHILD_STMT_IF; break;
	case TN_STMT_WHILE:	node->n_child = N_CHILD_STMT_WHILE; break;
	case TN_STMT_VARASSN:	node->n_child = N_CHILD_STMT_VARASSN; break;
	case TN_STMT_ARRASSN:	node->n_child = N_CHILD_STMT_ARRASSN; break;
	case TN_STMT_VARDEFN:	node->n_child = N_CHILD_STMT_VARDEFN; break;
	case TN_STMT_RETURN:	node->n_child = N_CHILD_STMT_RETURN; break;
	case TN_EXPR_BIARITH:	node->n_child = N_CHILD_EXPR_BIARITH; break;
	case TN_EXPR_BILOGIC:	node->n_child = N_CHILD_EXPR_BILOGIC; break;
	case TN_EXPR_ARR:	node->n_child = N_CHILD_EXPR_ARR; break;
	case TN_EXPR_INTEGER:	node->n_child = N_CHILD_EXPR_INTEGER; break;
	case TN_EXPR_IDENTIFIER:node->n_child = N_CHILD_EXPR_IDENTIFIER; break;
	case TN_EXPR_UNI:	node->n_child = N_CHILD_EXPR_UNI; break;
	case TN_EXPR_CALL:	node->n_child = N_CHILD_EXPR_CALL; break;
	case TN_TYPE:		node->n_child = N_CHILD_TYPE; break;
	case TN_INTEGER:	node->n_child = N_CHILD_INTEGER; break;
	case TN_IDENTIFIER:	node->n_child = N_CHILD_IDENTIFIER; break;
	default: node->n_child = N_CHILD_INIT; node->type = TN_INIT; break;	
	}
	node->parent = NULL;
	node->sibling_l = NULL;
	node->sibling_r = NULL;
	for (int i = 0; i < node->n_child; i++)
		node->child[i] = NULL;
	return node;
}

void free_treenode(struct TreeNode* arg_node)
{
	if (arg_node->name != NULL)
		free(arg_node->name);
	free(arg_node);
}

void print_treenode(struct TreeNode* arg_node, char* arg_prefix)
{
	char* prefix;
	if (arg_prefix == NULL)
		prefix = strdup("");
	else
		prefix = strdup(arg_prefix);
	switch(arg_node->type)
	{
	case TN_ROOT: printf("%s[*]Root(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_FUNCDEFN: printf("%s[*]FuncDefn(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_FUNCDECL: printf("%s[*]FuncDecl(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_VARDEFN: printf("%s[*]VarDefn(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_VARDECL: printf("%s[*]VarDecl(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_BLOCK: printf("%s[*]StmtBlock(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_IF: printf("%s[*]StmtIf(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_WHILE: printf("%s[*]StmtWhile(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_VARASSN: printf("%s[*]StmtVarAssn(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_ARRASSN: printf("%s[*]StmtArrAssn(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_VARDEFN: printf("%s[*]StmtVarDefn(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_RETURN: printf("%s[*]StmtReturn(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_BIARITH: printf("%s[*]ExprBiArith(%s)(%d) at L%d", prefix, arg_node->name, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_BILOGIC: printf("%s[*]ExprBiLogic(%s)(%d) at L%d", prefix, arg_node->name, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_ARR: printf("%s[*]ExprArr(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_INTEGER: printf("%s[*]ExprInt(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_IDENTIFIER: printf("%s[*]ExprId(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_UNI: printf("%s[*]ExprUni(%s)(%d) at L%d", prefix, arg_node->name, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_CALL: printf("%s[*]ExprCall(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_TYPE: printf("%s[*]Type(%s)(%d) at L%d", prefix, arg_node->name, arg_node->idx, arg_node->lineno); break;
	case TN_INTEGER: printf("%s[*]Int(%d)(%d) at L%d", prefix, arg_node->val, arg_node->idx, arg_node->lineno); break;
	case TN_IDENTIFIER: printf("%s[*]Id(%s)(%d) at L%d", prefix, arg_node->name, arg_node->idx, arg_node->lineno); break;
	case TN_INIT: printf("%s[!]UNKNOWN(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	default: printf("%s[!]UNKNOWN(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	}
	if (arg_node->parent == NULL)
		printf(", P (N)");
	else
		printf(", P (%d)", arg_node->parent->idx);
	if (arg_node->sibling_l == NULL)
		printf(" L (N)");
	else
		printf(" L (%d)", arg_node->sibling_l->idx);
	if (arg_node->sibling_r == NULL)
		printf(" R (N)");
	else
		printf(" R (%d)", arg_node->sibling_r->idx);
	printf(" C = %d", arg_node->n_child);
	printf(" I = %d\n", arg_node->child_idx);
}

void init_tree()
{
	n_treenode = 0;
}

void print_tree(struct TreeNode *arg_node, int depth)
{
	char* prefix;
	char prefix_unit[6] = "    ";
	struct TreeNode *tmp_node;
	if (arg_node == NULL)
		return;
	if (depth == 0)
	{
		print_treenode(arg_node, NULL);
		prefix = (char*)malloc(sizeof(char)*4);
		prefix[0] = '\0';
	}
	else
	{
		prefix = (char*)malloc(sizeof(char)*depth*4+10);
		memset(prefix, 0, sizeof(char)*depth*4+10);
		for (int i = 0; i < depth; i++)
			strcat(prefix, prefix_unit);
		print_treenode(arg_node, prefix);
	}
	for (int i = 0; i < arg_node->n_child; i++)
	{
		printf("%s  child(s) %d of (%d)\n", prefix, i+1, arg_node->idx);
		tmp_node = arg_node->child[i];
		if (tmp_node == NULL)
		{
			printf("%s    NONE\n", prefix);
			continue;
		}
		while (tmp_node != NULL)
		{
			print_tree(tmp_node, depth+1);
			tmp_node = tmp_node->sibling_r;
		}
	}
	free(prefix);
}
