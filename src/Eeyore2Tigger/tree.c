#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

void init_tree()
{
	n_treenode = 0;
}

struct TreeNode* alloc_treenode(int arg_type, char* arg_str, int arg_val)
{
	struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	node->idx = n_treenode++;
	node->type = arg_type;
	node->str = NULL;
	if (arg_str != NULL)
		node->str = strdup(arg_str);
	node->val = arg_val;
	switch(node->type)
	{
	case TN_ROOT:	node->n_child = 1; break;	// [FuncVarList]
	case TN_FUNC:	node->n_child = 1; break;	// [ExprList], str=id, val=n_param
	case TN_VAR:	node->n_child = 0; break;	// [], str=id, val=arr_size (if val<0, then it is not an array)
	case TN_EXPR_BI_LOGIC:	node->n_child = 2; break;	// [RVal1, RVal2], str=target_id, val=op_type
	case TN_EXPR_BI_ARITH:	node->n_child = 2; break;	// [RVal1, RVal2], str=target_id, val=op_type
	case TN_EXPR_UNI_LOGIC:	node->n_child = 1; break;	// [RVal], str=target_id, val=op_type
	case TN_EXPR_UNI_ARITH:	node->n_child = 1; break;	// [RVal], str=target_id, val=op_type
	case TN_EXPR_ASSN:	node->n_child = 3; break;	// [TgtArrIdx, SrcId, SrcArrIdx], str=target_id (if any idx<0, then the corresponding var is not an array)
	case TN_EXPR_IF_GOTO:	node->n_child = 2; break;	// [RVal1, RVal2], str=target_label, val=op_type
	case TN_EXPR_GOTO:	node->n_child = 0; break;	// [], str=target_label
	case TN_EXPR_LABEL:	node->n_child = 0; break;	// [], str=id
	case TN_EXPR_PARAM:	node->n_child = 1; break;	// [RVal]
	case TN_EXPR_CALL:	node->n_child = 1; break;	// [FuncID], str=target_id
	case TN_EXPR_RETURN:	node->n_child = 1; break;	// [RVal]
	case TN_NUM:	node->n_child = 0; break;	// [], val=num_value
	case TN_ID:	node->n_child = 0; break;	// [], str=id
	default:
		node->n_child = 0;
		node->type = TN_INIT;
		printf("unknown tree node...\n");
		break;
	}
	node->parent = NULL;
	for (int i = 0; i < MAX_N_CHILD; i++)
		node->child[i] = NULL;
	node->nxt = NULL;
	node->prv = NULL;
	return node;
}

void free_treenode(struct TreeNode* arg_node)
{
	if (arg_node->str != NULL)
		free(arg_node->str);
	free(arg_node);
}

void print_tree(struct TreeNode* arg_node, int arg_depth, FILE* arg_file)
{
	char* prefix = (char*)malloc(sizeof(char)*1000);
	memset(prefix, 0, sizeof(char)*1000);
	if (arg_node == NULL)
		return;
	for (int i = 0; i < arg_depth; i++)
		strcat(prefix, "  ");
	switch(arg_node->type)
	{
	case TN_ROOT:	fprintf(arg_file, "%sRoot@L%d\n", prefix, arg_node->lineno); break;
	case TN_FUNC:	fprintf(arg_file, "%sFunc@L%d, %s(%d)\n", prefix, arg_node->lineno, arg_node->str, arg_node->val); break;
	case TN_VAR:
		if (arg_node->val < 0)
			fprintf(arg_file, "%sVar@L%d, %s\n", prefix, arg_node->lineno, arg_node->str);
		else
			fprintf(arg_file, "%sVar@L%d, %s[%d]\n", prefix, arg_node->lineno, arg_node->str, arg_node->val);
		break;
	case TN_EXPR_BI_LOGIC:
		fprintf(arg_file, "%sBiLogicOp@L%d, to %s, ", prefix, arg_node->lineno, arg_node->str);
		switch (arg_node->val)
		{
		case OP_AND:	fprintf(arg_file, "AND\n"); break;
		case OP_OR:	fprintf(arg_file, "OR\n"); break;
		case OP_EQ:	fprintf(arg_file, "EQ\n"); break;
		case OP_NE:	fprintf(arg_file, "NE\n"); break;
		case OP_GT:	fprintf(arg_file, "GT\n"); break;
		case OP_LT:	fprintf(arg_file, "LT\n"); break;
		default:	fprintf(arg_file, "<UNK>\n"); break;
		}
		break;
	case TN_EXPR_BI_ARITH:
		fprintf(arg_file, "%sBiArithOp@L%d, to %s, ", prefix, arg_node->lineno, arg_node->str);
		switch (arg_node->val)
		{
		case OP_ADD:	fprintf(arg_file, "ADD\n"); break;
		case OP_SUB:	fprintf(arg_file, "SUB\n"); break;
		case OP_MUL:	fprintf(arg_file, "MUL\n"); break;
		case OP_DIV:	fprintf(arg_file, "DIV\n"); break;
		case OP_MOD:	fprintf(arg_file, "MOD\n"); break;
		default:	fprintf(arg_file, "<UNK>\n"); break;
		}
		break;
	case TN_EXPR_UNI_LOGIC:
		fprintf(arg_file, "%sUniLogicOp@L%d, to %s, ", prefix, arg_node->lineno, arg_node->str);
		switch (arg_node->val)
		{
		case OP_NOT:	fprintf(arg_file, "NOT\n"); break;
		default:	fprintf(arg_file, "<UNK>\n"); break;
		}
		break;
	case TN_EXPR_UNI_ARITH:
		fprintf(arg_file, "%sUniArithOp@L%d, to %s, ", prefix, arg_node->lineno, arg_node->str);
		switch (arg_node->val)
		{
		case OP_POS:	fprintf(arg_file, "POS\n"); break;
		case OP_NEG:	fprintf(arg_file, "NEG\n"); break;
		default:	fprintf(arg_file, "<UNK>\n"); break;
		}
		break;
	case TN_EXPR_ASSN:
		if (arg_node->val < 0)
			fprintf(arg_file, "%sAssnOp@L%d, to %s\n", prefix, arg_node->lineno, arg_node->str);
		else
			fprintf(arg_file, "%sAssnOp@L%d, to %s[%d]\n", prefix, arg_node->lineno, arg_node->str, arg_node->val);
		break;
	case TN_EXPR_IF_GOTO:
		fprintf(arg_file, "%sIfGoto@L%d, to %s, ", prefix, arg_node->lineno, arg_node->str);
		switch (arg_node->val)
		{
		case OP_AND:	fprintf(arg_file, "AND\n"); break;
		case OP_OR:	fprintf(arg_file, "OR\n"); break;
		case OP_EQ:	fprintf(arg_file, "EQ\n"); break;
		case OP_NE:	fprintf(arg_file, "NE\n"); break;
		case OP_GT:	fprintf(arg_file, "GT\n"); break;
		case OP_LT:	fprintf(arg_file, "LT\n"); break;
		default:	fprintf(arg_file, "<UNK>\n"); break;
		}
		break;
	case TN_EXPR_GOTO:	fprintf(arg_file, "%sGoto@L%d, to %s\n", prefix, arg_node->lineno, arg_node->str); break;
	case TN_EXPR_LABEL:	fprintf(arg_file, "Label@L%d, %s\n", arg_node->lineno, arg_node->str); break;
	case TN_EXPR_PARAM:	fprintf(arg_file, "%sParam@L%d\n", prefix, arg_node->lineno); break;
	case TN_EXPR_CALL:	fprintf(arg_file, "%sFuncCall@L%d, to %s\n", prefix, arg_node->lineno, arg_node->str); break;
	case TN_EXPR_RETURN:	fprintf(arg_file, "%sReturn@L%d\n", prefix, arg_node->lineno); break;
	case TN_NUM:	fprintf(arg_file, "%sNumber@L%d, %d\n", prefix, arg_node->lineno, arg_node->val); break;
	case TN_ID:	fprintf(arg_file, "%sID@L%d, %s\n", prefix, arg_node->lineno, arg_node->str); break;
	default:	fprintf(arg_file, "%s<UNK>@L%d\n", prefix, arg_node->lineno); break;
	}
	if (arg_node->type == TN_EXPR_ASSN)
		for (int i = 1; i < arg_node->n_child; i++)
			print_tree(arg_node->child[i], arg_depth+1, arg_file);
	else
		for (int i = 0; i < arg_node->n_child; i++)
			print_tree(arg_node->child[i], arg_depth+1, arg_file);
	if (arg_node->nxt != NULL)
		print_tree(arg_node->nxt, arg_depth, arg_file);
	free(prefix);
}
