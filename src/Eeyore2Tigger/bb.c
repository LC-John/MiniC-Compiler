#include "bb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_bb()
{
	n_bb = 0;
}

struct BasicBlock* alloc_bb(struct TreeNode* begin_node, struct TreeNode** end_node)
{
	struct TreeNode* tmp_node;
	struct BasicBlock* bb = (struct BasicBlock*)malloc(sizeof(struct BasicBlock));
	bb->idx = n_bb++;
	bb->n_stmt = 0;
	bb->str = NULL;
	for (tmp_node = begin_node; tmp_node != NULL; tmp_node = tmp_node->nxt)
	{
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
	bb->live_chain = (struct ListNode**)malloc(sizeof(struct ListNode*) * (bb->n_stmt+1));
	for (int i = 0; i <= bb->n_stmt; i++)
		bb->live_chain[i] = NULL;
	bb->begin = begin_node;
	bb->end = *end_node;
	bb->nxt[0] = NULL;
	bb->nxt[1] = NULL;
	bb->prv = NULL;
	return bb;
}

void free_bb(struct BasicBlock* arg_bb)
{
	if (arg_bb->str != NULL)
		free(arg_bb->str);
	for (int i = 0; i < arg_bb->n_stmt; i++)
	{
		struct ListNode *tmp = arg_bb->live_chain[i], *tbd = arg_bb->live_chain[i];
		while(tmp != NULL)
		{
			tbd = tmp;
			tmp = tmp->nxt;
			free(tbd);
		}
	}
	for (int i = 0; i < arg_bb->n_stmt; i++)
	{
		for (int j = 0; j < arg_bb->n_live[i]; j++)
			if (arg_bb->live[i][j] != NULL)
				free(arg_bb->live[i][j]);
		for (int j = 0; j < REG_N; j++)
			if (arg_bb->reg2id[i][j] != NULL)
				free(arg_bb->reg2id[i][j]);
		free(arg_bb->live[i]);
		free(arg_bb->die[i]);
		free(arg_bb->id2reg[i]);
		free(arg_bb->reg2id[i]);
	}
	free(arg_bb->live_chain);
	free(arg_bb->n_live);
	free(arg_bb->live);
	free(arg_bb->die);
	free(arg_bb->id2reg);
	free(arg_bb->reg2id);
	free(arg_bb);
}

struct ListNode** tree2bbs(struct TreeNode* root, int* arg_n_func)
{
	int n_func = 0, idx = 0;
	struct ListNode** funcs;
	struct TreeNode* make_the_compiler_happy;
	for (struct TreeNode* node = root->child[0]; node != NULL; node = node->nxt)
	{
		if (node->type != TN_FUNC)
			continue;
		n_func++;
	}
	*arg_n_func = n_func;
	funcs = (struct ListNode**)malloc(sizeof(struct ListNode*)*n_func);
	for (int i = 0; i < n_func; i++)
	{
		funcs[i] = (struct ListNode*)malloc(sizeof(struct ListNode));
		funcs[i]->obj = alloc_bb(NULL, &make_the_compiler_happy);
		funcs[i]->prv = NULL;
	}
	for (struct TreeNode* node = root->child[0]; node != NULL; node = node->nxt)
	{
		struct TreeNode** split = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
		struct ListNode* bb_container;
		struct ListNode* last_bb_container;
		struct ListNode *bb_entry, *bb_exit;
		if (node->type != TN_FUNC)
			continue;
		last_bb_container = funcs[idx++];
		*split = node->child[0];
		((struct BasicBlock*)(last_bb_container->obj))->str = strdup(node->str);
		do
		{
			bb_container = (struct ListNode*)malloc(sizeof(struct ListNode));
			bb_container->obj = alloc_bb(*split, split);
			last_bb_container->nxt = bb_container;
			bb_container->prv = last_bb_container;
			last_bb_container = bb_container;
		} while (*split != NULL);
		bb_exit = (struct ListNode*)malloc(sizeof(struct ListNode));
		bb_exit->obj = alloc_bb(NULL, &make_the_compiler_happy);
		((struct BasicBlock*)(bb_exit->obj))->str = strdup("RETURN");
		last_bb_container->nxt = bb_exit;
		bb_exit->prv = last_bb_container;
		bb_exit->nxt = NULL;
	}
	for (int i = 0; i < n_func; i++)
	{
		struct ListNode* bb_container = funcs[i];
		struct ListNode* bb_container_nxt = funcs[i]->nxt;
		struct BasicBlock* bb = (struct BasicBlock*)(bb_container->obj);
		struct BasicBlock* bb_nxt = (struct BasicBlock*)(bb_container_nxt->obj);
		struct ListNode* end_bb_container = funcs[i];
		struct BasicBlock* end_bb;
		while(end_bb_container->nxt != NULL)
			end_bb_container = end_bb_container->nxt;
		end_bb = (struct BasicBlock*)(end_bb_container->obj);
		bb->nxt[0] = (struct BasicBlock*)(bb_container->nxt->obj);
		if (bb_nxt->prv == NULL)
		{
			bb_nxt->prv = (struct ListNode*)malloc(sizeof(struct ListNode));
			bb_nxt->prv->obj = bb;
			bb_nxt->prv->nxt = bb_nxt->prv->prv = NULL;
		}
		else
		{
			struct ListNode* tmp_lnode = (struct ListNode*)malloc(sizeof(struct ListNode));
			tmp_lnode->obj = bb; tmp_lnode->prv = NULL;
			bb_nxt->prv->prv = tmp_lnode;
			tmp_lnode->nxt = bb_nxt->prv;
			bb_nxt->prv = tmp_lnode;
		}
		bb_container = bb_container->nxt;
		while(bb_container->nxt != NULL)
		{
			struct TreeNode* tmp_end = NULL;
			bb = (struct BasicBlock*)(bb_container->obj);
			bb_nxt = NULL;
			// RETURN, link to exit BB
			for (struct TreeNode* tnode = bb->begin; tnode != bb->end; tnode = tnode->nxt)
				if (tnode->type == TN_EXPR_RETURN)
					tmp_end = tnode->nxt;
				else if (tmp_end != NULL)
					bb->n_stmt--;
			if (tmp_end != NULL)
			{
				bb->end = tmp_end;
				bb_nxt = end_bb;
				if (bb_nxt != NULL)
					bb->nxt[0] = bb_nxt;
				if (bb_nxt != NULL &&bb_nxt->prv == NULL)
				{
					bb_nxt->prv = (struct ListNode*)malloc(sizeof(struct ListNode));
					bb_nxt->prv->obj = bb;
					bb_nxt->prv->nxt = bb_nxt->prv->prv = NULL;
				}
				else if (bb_nxt != NULL)
				{
					struct ListNode* tmp_lnode = (struct ListNode*)malloc(sizeof(struct ListNode));
					tmp_lnode->obj = bb; tmp_lnode->prv = NULL;
					bb_nxt->prv->prv = tmp_lnode;
					tmp_lnode->nxt = bb_nxt->prv;
					bb_nxt->prv = tmp_lnode;
				}
			}
			if (bb->live_chain == NULL)
				bb->live_chain = (struct ListNode**)malloc(sizeof(struct ListNode*)*(bb->n_stmt+1));
			tmp_end = bb->begin;
			while (tmp_end->nxt != bb->end)
				tmp_end = tmp_end->nxt;
			// (IF) GOTO, link to target BB
			if (tmp_end->type == TN_EXPR_GOTO || tmp_end->type == TN_EXPR_IF_GOTO)
			{
				bb_nxt = NULL;
				for (bb_container_nxt = funcs[i]->nxt; bb_container_nxt != NULL && bb_container_nxt->nxt != NULL; bb_container_nxt = bb_container_nxt->nxt)
				{
					struct TreeNode* tmp_tnode = ((struct BasicBlock*)(bb_container_nxt->obj))->begin;
					if (tmp_tnode->type == TN_EXPR_LABEL && strcmp(tmp_tnode->str, tmp_end->str) == 0)
					{
						bb_nxt = ((struct BasicBlock*)(bb_container_nxt->obj));
						break;
					}
				}
				if (bb_nxt == NULL)
				{
					fprintf(stderr, "Cannot find label %s", tmp_end->str);
					for (int i = 0; i < n_func; i++)
					{
						struct ListNode* lnode = funcs[i];
						while(lnode != NULL)
						{
							print_bb(lnode->obj, stdout);
							fprintf(stdout, "\n");
							lnode = lnode->nxt;
						}
						fprintf(stdout, "\n");
					}
					exit(-1);
				}
				bb->nxt[0] = bb_nxt;
				if (bb_nxt->prv == NULL)
				{
					bb_nxt->prv = (struct ListNode*)malloc(sizeof(struct ListNode));
					bb_nxt->prv->obj = bb;
					bb_nxt->prv->nxt = bb_nxt->prv->prv = NULL;
				}
				else
				{
					struct ListNode* tmp_lnode = (struct ListNode*)malloc(sizeof(struct ListNode));
					tmp_lnode->obj = bb; tmp_lnode->prv = NULL;
					bb_nxt->prv->prv = tmp_lnode;
					tmp_lnode->nxt = bb_nxt->prv;
					bb_nxt->prv = tmp_lnode;
				}
			}
			// IF GOTO, link to next BB
			if (tmp_end->type == TN_EXPR_IF_GOTO)
			{
				bb_container_nxt = bb_container->nxt;
				bb_nxt = (struct BasicBlock*)(bb_container_nxt->obj);
				bb->nxt[1] = bb_nxt;
				if (bb_nxt != NULL &&bb_nxt->prv == NULL)
				{
					bb_nxt->prv = (struct ListNode*)malloc(sizeof(struct ListNode));
					bb_nxt->prv->obj = bb;
					bb_nxt->prv->nxt = bb_nxt->prv->prv = NULL;
				}
				else if (bb_nxt != NULL)
				{
					struct ListNode* tmp_lnode = (struct ListNode*)malloc(sizeof(struct ListNode));
					tmp_lnode->obj = bb; tmp_lnode->prv = NULL;
					bb_nxt->prv->prv = tmp_lnode;
					tmp_lnode->nxt = bb_nxt->prv;
					bb_nxt->prv = tmp_lnode;
				}
			}
			// Link others to next BB
			if (bb->nxt[0] == NULL)
			{
				bb_container_nxt = bb_container->nxt;
				bb_nxt = (struct BasicBlock*)(bb_container_nxt->obj);
				bb->nxt[0] = bb_nxt;
				if (bb_nxt != NULL &&bb_nxt->prv == NULL)
				{
					bb_nxt->prv = (struct ListNode*)malloc(sizeof(struct ListNode));
					bb_nxt->prv->obj = bb;
					bb_nxt->prv->nxt = bb_nxt->prv->prv = NULL;
				}
				else if (bb_nxt != NULL)
				{
					struct ListNode* tmp_lnode = (struct ListNode*)malloc(sizeof(struct ListNode));
					tmp_lnode->obj = bb; tmp_lnode->prv = NULL;
					bb_nxt->prv->prv = tmp_lnode;
					tmp_lnode->nxt = bb_nxt->prv;
					bb_nxt->prv = tmp_lnode;
				}
			}
			bb_container = bb_container->nxt;
		}
	}
	return funcs;
}

int var_life_within_bb(struct BasicBlock* arg_bb_container, struct ListNode* arg_live_chain)
{
	int ret = 0;
	struct BasicBlock* bb = arg_bb_container;
	struct TreeNode* stmt = bb->begin;
	struct ListNode *live_chain = arg_live_chain, *tmp;
	while(stmt != NULL && stmt->nxt != bb->end)
		stmt = stmt->nxt;
	bb->live_chain[bb->n_stmt] = merge_str_lists(bb->live_chain[bb->n_stmt], arg_live_chain);
	for (int i = bb->n_stmt-1; i >= 0; i--, stmt = stmt->prv)
	{
		struct ListNode* old = copy_str_list(bb->live_chain[i]);
		bb->live_chain[i] = merge_str_lists(bb->live_chain[i], bb->live_chain[i+1]);
		switch (stmt->type)
		{
		case TN_VAR:
			tmp = find_str_list(bb->live_chain[i], stmt->str);
			if (tmp != NULL)
				bb->live_chain[i] = delete_node_from_list(tmp, bb->live_chain[i]);
			break;
		case TN_EXPR_BI_LOGIC:
		case TN_EXPR_BI_ARITH:
		case TN_EXPR_IF_GOTO:	// stmt->str for IF_GOTO is the label, which will never appear in the live_chain var lists
			tmp = find_str_list(bb->live_chain[i], stmt->str);
			if (tmp != NULL)
				bb->live_chain[i] = delete_node_from_list(tmp, bb->live_chain[i]);
			if (stmt->child[0]->type == TN_ID)
			{
				tmp = find_str_list(bb->live_chain[i], stmt->child[0]->str);
				if (tmp == NULL)
					bb->live_chain[i] = insert_str_node_into_list(bb->live_chain[i], stmt->child[0]->str);
			}
			if (stmt->child[1]->type == TN_ID)
			{
				tmp = find_str_list(bb->live_chain[i], stmt->child[1]->str);
				if (tmp == NULL)
					bb->live_chain[i] = insert_str_node_into_list(bb->live_chain[i], stmt->child[1]->str);
			}
			break;
		case TN_EXPR_UNI_LOGIC:
		case TN_EXPR_UNI_ARITH:
			tmp = find_str_list(bb->live_chain[i], stmt->str);
			if (tmp != NULL)
				bb->live_chain[i] = delete_node_from_list(tmp, bb->live_chain[i]);
			if (stmt->child[0]->type == TN_ID)
			{
				tmp = find_str_list(bb->live_chain[i], stmt->child[0]->str);
				if (tmp == NULL)
					bb->live_chain[i] = insert_str_node_into_list(bb->live_chain[i], stmt->child[0]->str);
			}
			break;
		case TN_EXPR_ASSN:
			tmp = find_str_list(bb->live_chain[i], stmt->str);
			if (tmp != NULL)
				bb->live_chain[i] = delete_node_from_list(tmp, bb->live_chain[i]);
			if (stmt->child[1] != NULL && stmt->child[1]->type == TN_ID)
			{
				tmp = find_str_list(bb->live_chain[i], stmt->child[1]->str);
				if (tmp == NULL)
					bb->live_chain[i] = insert_str_node_into_list(bb->live_chain[i], stmt->child[1]->str);
			}
			if (stmt->child[0] != NULL && stmt->child[0]->type == TN_ID)
			{
				tmp = find_str_list(bb->live_chain[i], stmt->child[0]->str);
				if (tmp == NULL)
					bb->live_chain[i] = insert_str_node_into_list(bb->live_chain[i], stmt->child[0]->str);
			}
			if (stmt->child[2] != NULL && stmt->child[2]->type == TN_ID)
			{
				tmp = find_str_list(bb->live_chain[i], stmt->child[2]->str);
				if (tmp == NULL)
					bb->live_chain[i] = insert_str_node_into_list(bb->live_chain[i], stmt->child[2]->str);
			}
			break;
		case TN_EXPR_CALL:
			tmp = find_str_list(bb->live_chain[i], stmt->str);
			if (tmp != NULL)
				bb->live_chain[i] = delete_node_from_list(tmp, bb->live_chain[i]);
			break;
		case TN_EXPR_PARAM:
		case TN_EXPR_RETURN:
			if (stmt->child[0]->type == TN_ID)
			{
				tmp = find_str_list(bb->live_chain[i], stmt->child[0]->str);
				if (tmp == NULL)
					bb->live_chain[i] = insert_str_node_into_list(bb->live_chain[i], stmt->child[0]->str);
			}
			break;
		case TN_EXPR_GOTO:
		case TN_EXPR_LABEL:
		default:	break;
		}
		if (cmp_str_lists(old, bb->live_chain[i]) != 0)
		{
			ret++;
		}
		while(old != NULL)
		{
			struct ListNode* tmp = old;
			if (tmp->obj != NULL)
				free(tmp->obj);
			free(tmp);
			old = old->nxt;
		}
	}
	return ret;
}

int var_life_between_bbs(struct ListNode* arg_bb_container)
{
	int ret = 0;
	int **flag_matrix, begin_idx;
	struct BasicBlock* bb;
	struct ListNode* bb_container;
	bb = (struct BasicBlock*)(arg_bb_container->obj);
	begin_idx = bb->idx;
	while (arg_bb_container->nxt != NULL)
	{
		bb = (struct BasicBlock*)(arg_bb_container->obj);
		arg_bb_container = arg_bb_container->nxt;
	}
	bb = (struct BasicBlock*)(arg_bb_container->obj);
	bb_container = bb->prv;
	flag_matrix = (int**)malloc(sizeof(int*)*(bb->idx+10));
	for (int i = 0; i < bb->idx+10; i++)
	{
		flag_matrix[i] = (int*)malloc(sizeof(int)*(bb->idx+10));
		memset(flag_matrix[i], 0, sizeof(int)*(bb->idx+10));
	}
	while (bb_container != NULL)
	{
		struct BasicBlock* tmp = (struct BasicBlock*)(bb_container->obj);
		if (flag_matrix[tmp->idx][bb->idx] > 0)
		{
			bb_container = bb_container->nxt;
			continue;
		}
		ret += var_life_bb2bb(tmp, bb, flag_matrix);
		bb_container = bb_container->nxt;
	}
	for (int i = 0; i < bb->idx+10; i++)
		free(flag_matrix[i]);
	free(flag_matrix);
	return ret;
}

int var_life_bb2bb(struct BasicBlock* bb1, struct BasicBlock* bb2, int** flag_matrix)
{
	//printf ("%d\t%d\n", bb1->idx, bb2->idx);
	if (bb1 == NULL || bb2 == NULL)
		return 0;
	int ret = var_life_within_bb(bb1, bb2->live_chain[0]);
	struct ListNode* bb3_container = bb1->prv;
	flag_matrix[bb1->idx][bb2->idx] = 1;
	while (bb3_container != NULL)
	{
		struct BasicBlock* tmp = (struct BasicBlock*)(bb3_container->obj);
		if (flag_matrix[tmp->idx][bb1->idx] > 0)
		{
			bb3_container = bb3_container->nxt;
			continue;
		}
		ret += var_life_bb2bb(tmp, bb1, flag_matrix);
		bb3_container = bb3_container->nxt;
	}
	return ret;
}

void get_die_within_bb(struct BasicBlock* arg_bb)
{
	arg_bb->die = (int**)malloc(sizeof(int*) * (arg_bb->n_stmt+1));
	arg_bb->live = (char***)malloc(sizeof(char**) * (arg_bb->n_stmt+1));
	arg_bb->n_live = (int*)malloc(sizeof(int) * (arg_bb->n_stmt+1));
	for (int i = arg_bb->n_stmt; i >= 0; i--)
	{
		struct ListNode* live_node = arg_bb->live_chain[i];
		int idx;
		arg_bb->n_live[i] = 0;
		while(live_node != NULL)
		{
			arg_bb->n_live[i]++;
			live_node = live_node->nxt;
		}
		arg_bb->die[i] = (int*)malloc(sizeof(int)*arg_bb->n_live[i]);
		arg_bb->live[i] = (char**)malloc(sizeof(char*)*arg_bb->n_live[i]);
		for(idx = 0, live_node = arg_bb->live_chain[i]; live_node != NULL && idx < arg_bb->n_live[i]; live_node = live_node->nxt, idx++)
		{
			arg_bb->live[i][idx] = strdup((char*)(live_node->obj));
			if (i == arg_bb->n_stmt)
				arg_bb->die[i][idx] = LV_LIVE_TILL_END;
			else
			{
				int tmp = i;
				for (int j = 0; j < arg_bb->n_live[i+1]; j++)
					if (strcmp(arg_bb->live[i][idx], arg_bb->live[i+1][j]) == 0)
					{
						tmp = arg_bb->die[i+1][j];
						continue;
					}
				arg_bb->die[i][idx] = tmp;
			}
		}
	}
}

void print_bb(struct BasicBlock* arg_bb, FILE* arg_file)
{
	struct TreeNode* node = arg_bb->begin;
	struct ListNode* from;
	if (arg_bb->str == NULL)
		fprintf(arg_file, "BB %d\t", arg_bb->idx);
	else
		fprintf(arg_file, "BB %d (%s)\t", arg_bb->idx, arg_bb->str);
	fprintf(arg_file, "stmt# = %d\t", arg_bb->n_stmt);
	if (arg_bb->nxt[0] != NULL)
	{
		fprintf(arg_file, "to BB %d", arg_bb->nxt[0]->idx);
		if (arg_bb->nxt[1] != NULL)
			fprintf(arg_file, ", %d", arg_bb->nxt[1]->idx);
		fprintf(arg_file, "\t");
		if (arg_bb->prv != NULL)
		{
			fprintf(arg_file, "from BB %d", ((struct BasicBlock*)(arg_bb->prv->obj))->idx);
			from = arg_bb->prv->nxt;
			while (from != NULL)
			{
				fprintf(arg_file, ", %d", ((struct BasicBlock*)(from->obj))->idx);
				from = from->nxt;
			}
		}
	}
	fprintf(arg_file, "\n");
	for (int i = 0; i < arg_bb->n_stmt && node != arg_bb->end; i++, node = node->nxt)
	{
		switch(node->type)
		{
		case TN_VAR:
			fprintf(arg_file, "%d\t", i);
			fprintf(arg_file, "var %s ", node->str);
			if (node->val > 0)
				fprintf(arg_file, "[%d] ", node->val);
			break;
		case TN_EXPR_BI_LOGIC:
		case TN_EXPR_BI_ARITH:
			fprintf(arg_file, "%d\t", i);
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
			fprintf(arg_file, "%d\t", i);
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
			fprintf(arg_file, "%d\t", i);
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
			fprintf(arg_file, "%d\t", i);
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
			case TN_NUM:		fprintf(arg_file, "%d ", node->child[1]->val); break;
			case TN_ID:		fprintf(arg_file, "%s ", node->child[1]->str); break;
			default:	fprintf(arg_file, "<UNK> "); break;
			}
			fprintf(arg_file, ") goto %s ", node->str);
			break;
		case TN_EXPR_GOTO:	
			fprintf(arg_file, "%d\t", i);
			fprintf(arg_file, "goto %s ", node->str); break;
		case TN_EXPR_LABEL:	
			fprintf(arg_file, "%d\t", i);
			fprintf(arg_file, "label %s ", node->str); break;
		case TN_EXPR_PARAM:
			fprintf(arg_file, "%d\t", i);
			fprintf(arg_file, "param ");
			switch (node->child[0]->type)
			{
			case TN_NUM:		fprintf(arg_file, "%d ", node->child[0]->val); break;
			case TN_ID:		fprintf(arg_file, "%s ", node->child[0]->str); break;
			default:	fprintf(arg_file, "<UNK> "); break;
			}
			break;
		case TN_EXPR_CALL:	
			fprintf(arg_file, "%d\t", i);
			fprintf(arg_file, "%s = call %s ", node->str, node->child[0]->str); break;
		case TN_EXPR_RETURN:
			fprintf(arg_file, "%d\t", i);
			fprintf(arg_file, "return ");
			switch (node->child[0]->type)
			{
			case TN_NUM:		fprintf(arg_file, "%d ", node->child[0]->val); break;
			case TN_ID:		fprintf(arg_file, "%s ", node->child[0]->str); break;
			default:	fprintf(arg_file, "<UNK> "); break;
			}
			break;
		default:	
			fprintf(arg_file, "%d\t", i);
			fprintf(arg_file, "{UNK STMT} "); break;
		}
		if (arg_bb->live_chain == NULL)
		{
			fprintf(arg_file, "\t//{}\n");
			continue;
		}
		fprintf(arg_file, "\t// {");
		for (int k = 0; k < arg_bb->n_live[i]; k++)
		{
			if (arg_bb->id2reg[i][k] < 0)
				fprintf(arg_file, " %s(UNK) ", arg_bb->live[i][k]);
			else if (arg_bb->id2reg[i][k] < REG_N)
				fprintf(arg_file, " %s(REG%s) ", arg_bb->live[i][k], registers[arg_bb->id2reg[i][k]]);
			else if (arg_bb->id2reg[i][k] == REG_GLOBAL)
				fprintf(arg_file, " %s(GLB) ", arg_bb->live[i][k]);
			else
				fprintf(arg_file, " %s(ST%d) ", arg_bb->live[i][k], arg_bb->id2reg[i][k]-REG_STACK);
		}
		fprintf(arg_file, "}\n");
	}
	fprintf(arg_file, "\t// {");
	for (int k = 0; k < arg_bb->n_live[arg_bb->n_stmt]; k++)
	{
		if (arg_bb->id2reg[arg_bb->n_stmt][k] < 0)
			fprintf(arg_file, " %s(UNK) ", arg_bb->live[arg_bb->n_stmt][k]);
		else if (arg_bb->id2reg[arg_bb->n_stmt][k] < REG_N)
			fprintf(arg_file, " %s(REG%s) ", arg_bb->live[arg_bb->n_stmt][k], registers[arg_bb->id2reg[arg_bb->n_stmt][k]]);
		else if (arg_bb->id2reg[arg_bb->n_stmt][k] == REG_GLOBAL)
			fprintf(arg_file, " %s(GLB) ", arg_bb->live[arg_bb->n_stmt][k]);
		else
			fprintf(arg_file, " %s(ST%d) ", arg_bb->live[arg_bb->n_stmt][k], arg_bb->id2reg[arg_bb->n_stmt][k]-REG_STACK);
	}
	fprintf(arg_file, "}\n");
}
