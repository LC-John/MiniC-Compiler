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

void print_treenode(struct TreeNode* arg_node, char* arg_prefix, FILE* f)
{
	char* prefix;
	if (arg_prefix == NULL)
		prefix = strdup("");
	else
		prefix = strdup(arg_prefix);
	switch(arg_node->type)
	{
	case TN_ROOT: fprintf(f, "%s[*]Root(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_FUNCDEFN: fprintf(f, "%s[*]FuncDefn(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_FUNCDECL: fprintf(f, "%s[*]FuncDecl(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_VARDEFN: fprintf(f, "%s[*]VarDefn(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_VARDECL: fprintf(f, "%s[*]VarDecl(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_BLOCK: fprintf(f, "%s[*]StmtBlock(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_IF: fprintf(f, "%s[*]StmtIf(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_WHILE: fprintf(f, "%s[*]StmtWhile(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_VARASSN: fprintf(f, "%s[*]StmtVarAssn(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_ARRASSN: fprintf(f, "%s[*]StmtArrAssn(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_VARDEFN: fprintf(f, "%s[*]StmtVarDefn(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_STMT_RETURN: fprintf(f, "%s[*]StmtReturn(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_BIARITH: fprintf(f, "%s[*]ExprBiArith(%s)(%d) at L%d", prefix, arg_node->name, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_BILOGIC: fprintf(f, "%s[*]ExprBiLogic(%s)(%d) at L%d", prefix, arg_node->name, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_ARR: fprintf(f, "%s[*]ExprArr(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_INTEGER: fprintf(f, "%s[*]ExprInt(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_IDENTIFIER: fprintf(f, "%s[*]ExprId(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_UNI: fprintf(f, "%s[*]ExprUni(%s)(%d) at L%d", prefix, arg_node->name, arg_node->idx, arg_node->lineno); break;
	case TN_EXPR_CALL: fprintf(f, "%s[*]ExprCall(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	case TN_TYPE: fprintf(f, "%s[*]Type(%s)(%d) at L%d", prefix, arg_node->name, arg_node->idx, arg_node->lineno); break;
	case TN_INTEGER: fprintf(f, "%s[*]Int(%d)(%d) at L%d", prefix, arg_node->val, arg_node->idx, arg_node->lineno); break;
	case TN_IDENTIFIER: fprintf(f, "%s[*]Id(%s)(%d) at L%d", prefix, arg_node->name, arg_node->idx, arg_node->lineno); break;
	case TN_INIT: fprintf(f, "%s[!]UNKNOWN(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	default: fprintf(f, "%s[!]UNKNOWN(%d) at L%d", prefix, arg_node->idx, arg_node->lineno); break;
	}
	if (arg_node->parent == NULL)
		fprintf(f, ", P (N)");
	else
		fprintf(f, ", P (%d)", arg_node->parent->idx);
	if (arg_node->sibling_l == NULL)
		fprintf(f, " L (N)");
	else
		fprintf(f, " L (%d)", arg_node->sibling_l->idx);
	if (arg_node->sibling_r == NULL)
		fprintf(f, " R (N)");
	else
		fprintf(f, " R (%d)", arg_node->sibling_r->idx);
	fprintf(f, " C = %d", arg_node->n_child);
	fprintf(f, " I = %d\n", arg_node->child_idx);
}

void init_tree()
{
	n_treenode = 0;
}

void print_tree(struct TreeNode *arg_node, int depth, FILE* f)
{
	char* prefix;
	char prefix_unit[6] = "    ";
	struct TreeNode *tmp_node;
	if (arg_node == NULL)
		return;
	if (depth == 0)
	{
		print_treenode(arg_node, NULL, f);
		prefix = (char*)malloc(sizeof(char)*4);
		prefix[0] = '\0';
	}
	else
	{
		prefix = (char*)malloc(sizeof(char)*depth*4+10);
		memset(prefix, 0, sizeof(char)*depth*4+10);
		for (int i = 0; i < depth; i++)
			strcat(prefix, prefix_unit);
		print_treenode(arg_node, prefix, f);
	}
	for (int i = 0; i < arg_node->n_child; i++)
	{
		fprintf(f, "%s  child(s) %d of (%d)\n", prefix, i+1, arg_node->idx);
		tmp_node = arg_node->child[i];
		if (tmp_node == NULL)
		{
			fprintf(f, "%s    NONE\n", prefix);
			continue;
		}
		while (tmp_node != NULL)
		{
			print_tree(tmp_node, depth+1, f);
			tmp_node = tmp_node->sibling_r;
		}
	}
	free(prefix);
}
