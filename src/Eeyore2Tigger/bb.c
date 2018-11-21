#include "bb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct BasicBlock* alloc_bb(struct TreeNode* begin_node, struct TreeNode** end_node)
{
	struct TreeNode* tmp_node;
	struct BasicBlock* bb = (struct BasicBlock*)malloc(sizeof(struct BasicBlock));
	bb->n_stmt = 0;
	for (tmp_node = begin_node; tmp_node != NULL; tmp_node = tmp_node->nxt)
	{
		if (tmp_node->type == TN_VAR)
			continue;
		if (tmp_node->type == TN_EXPR_LABEL && tmp_node != begin_node)
			break;
		bb->n_stmt++;
		if (tmp_node->type == TN_EXPR_IF_GOTO || tmp_node->type == TN_EXPR_GOTO)
		{
			tmp_node = tmp_node->nxt;
			break;
		}
	}
	*end_node = tmp_node;
	bb->live = (struct ListNode**)malloc(sizeof(struct ListNode*) * bb->n_stmt);
	for (int i = 0; i < bb->n_stmt; i++)
		bb->live[i] = NULL;
	bb->begin = begin_node;
	bb->end = *end_node;
	return bb;
}

void free_bb(struct BasicBlock* arg_bb)
{
	for (int i = 0; i < arg_bb->n_stmt; i++)
	{
		struct ListNode *tmp = arg_bb->live[i], *tbd = arg_bb->live[i];
		while(tmp != NULL)
		{
			tbd = tmp;
			tmp = tmp->nxt;
			free(tbd);
		}
	}
	free(arg_bb);
}

void print_bb(struct BasicBlock* arg_bb, FILE* arg_file)
{
	struct TreeNode* node = arg_bb->begin;
	struct ListNode* live_val;
	fprintf(arg_file, "stmt num = %d\n", arg_bb->n_stmt);
	for (int i = 0; i < arg_bb->n_stmt && node != arg_bb->end; i++, node = node->nxt)
	{
		switch(node->type)
		{
		case TN_VAR: i--; continue;
		case TN_EXPR_BI_LOGIC:
		case TN_EXPR_BI_ARITH:
			fprintf(arg_file, "%s = ", node->str);
			switch (node->child[0]->type)
			{
			case TN_NUM:		fprintf(arg_file, "%d ", node->child[0]->val); break;
			case TN_ID:		fprintf(arg_file, "%s ", node->child[0]->str); break;
			default:	fprintf(arg_file, "<UNK> "); break;
			}
			switch (node->val)
			{
			case OP_AND:	fprintf(arg_file, "&& "); break;
			case OP_OR:	fprintf(arg_file, "|| "); break;
			case OP_EQ:	fprintf(arg_file, "== "); break;
			case OP_NE:	fprintf(arg_file, "!= "); break;
			case OP_GT:	fprintf(arg_file, "> "); break;
			case OP_LT:	fprintf(arg_file, "< "); break;
			case OP_ADD:	fprintf(arg_file, "+ "); break;
			case OP_SUB:	fprintf(arg_file, "- "); break;
			case OP_MUL:	fprintf(arg_file, "* "); break;
			case OP_DIV:	fprintf(arg_file, "/ "); break;
			case OP_MOD:	fprintf(arg_file, "%% "); break;
			default:	fprintf(arg_file, "<UNK> "); break;
			}
			switch (node->child[1]->type)
			{
			case TN_NUM:		fprintf(arg_file, "%d ", node->child[1]->val); break;
			case TN_ID:		fprintf(arg_file, "%s ", node->child[1]->str); break;
			default:	fprintf(arg_file, "<UNK> "); break;
			}
			break;
		case TN_EXPR_UNI_LOGIC:
		case TN_EXPR_UNI_ARITH:
			fprintf(arg_file, "%s = ", node->str);
			switch (node->val)
			{
			case OP_NOT:	fprintf(arg_file, "! "); break;
			case OP_POS:	fprintf(arg_file, "+ "); break;
			case OP_NEG:	fprintf(arg_file, "- "); break;
			default:	fprintf(arg_file, "<UNK> "); break;
			}
			switch (node->child[0]->type)
			{
			case TN_NUM:		fprintf(arg_file, "%d ", node->child[0]->val); break;
			case TN_ID:		fprintf(arg_file, "%s ", node->child[0]->str); break;
			default:	fprintf(arg_file, "<UNK> "); break;
			}
			break;
		case TN_EXPR_ASSN:
			fprintf(arg_file, "%s", node->str);
			if (node->child[0] != NULL)
				switch (node->child[0]->type)
				{
				case TN_NUM:		fprintf(arg_file, "[%d]", node->child[0]->val); break;
				case TN_ID:		fprintf(arg_file, "[%s]", node->child[0]->str); break;
				default:	fprintf(arg_file, "[<UNK>]"); break;
				}
			fprintf(arg_file, " = ");
			switch (node->child[1]->type)
			{
			case TN_NUM:		fprintf(arg_file, "%d", node->child[1]->val); break;
			case TN_ID:		fprintf(arg_file, "%s", node->child[1]->str); break;
			default:	fprintf(arg_file, "<UNK>"); break;
			}
			if (node->child[2] != NULL)
				switch (node->child[2]->type)
				{
				case TN_NUM:		fprintf(arg_file, "[%d]", node->child[2]->val); break;
				case TN_ID:		fprintf(arg_file, "[%s]", node->child[2]->str); break;
				default:	fprintf(arg_file, "[<UNK>]"); break;
				}
			fprintf(arg_file, " ");
			break;
		case TN_EXPR_IF_GOTO:
			fprintf(arg_file, "if (");
			switch (node->child[0]->type)
			{
			case TN_NUM:		fprintf(arg_file, "%d ", node->child[0]->val); break;
			case TN_ID:		fprintf(arg_file, "%s ", node->child[0]->str); break;
			default:	fprintf(arg_file, "<UNK> "); break;
			}
			switch (node->val)
			{
			case OP_AND:	fprintf(arg_file, "&& "); break;
			case OP_OR:	fprintf(arg_file, "|| "); break;
			case OP_EQ:	fprintf(arg_file, "== "); break;
			case OP_NE:	fprintf(arg_file, "!= "); break;
			case OP_GT:	fprintf(arg_file, "> "); break;
			case OP_LT:	fprintf(arg_file, "< "); break;
			default:	fprintf(arg_file, "<UNK> "); break;
			}
			switch (node->child[1]->type)
			{
			case TN_NUM:		fprintf(arg_file, "%d ", node->child[0]->val); break;
			case TN_ID:		fprintf(arg_file, "%s ", node->child[0]->str); break;
			default:	fprintf(arg_file, "<UNK> "); break;
			}
			fprintf(arg_file, ") goto %s ", node->str);
			break;
		case TN_EXPR_GOTO:	fprintf(arg_file, "goto %s ", node->str); break;
		case TN_EXPR_LABEL:	fprintf(arg_file, "label %s ", node->str); break;
		case TN_EXPR_PARAM:
			fprintf(arg_file, "param ");
			switch (node->child[0]->type)
			{
			case TN_NUM:		fprintf(arg_file, "%d ", node->child[0]->val); break;
			case TN_ID:		fprintf(arg_file, "%s ", node->child[0]->str); break;
			default:	fprintf(arg_file, "<UNK> "); break;
			}
			break;
		case TN_EXPR_CALL:	fprintf(arg_file, "%s = call %s ", node->str, node->child[0]->str); break;
		case TN_EXPR_RETURN:
			fprintf(arg_file, "return ");
			switch (node->child[0]->type)
			{
			case TN_NUM:		fprintf(arg_file, "%d ", node->child[0]->val); break;
			case TN_ID:		fprintf(arg_file, "%s ", node->child[0]->str); break;
			default:	fprintf(arg_file, "<UNK> "); break;
			}
			break;
		default:	fprintf(arg_file, "{UNK STMT} "); break;
		}
		live_val = arg_bb->live[i];
		fprintf(arg_file, "\t//{");
		while(live_val != NULL)
		{
			fprintf(arg_file, " %s ", (char*)(live_val->obj));
			live_val = live_val->nxt;
		}
		fprintf(arg_file, "}\n");
	}
}
