#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regalloc.h"

void init_reg()
{
	registers[0] = strdup("t0");	// Caller-saved
	registers[1] = strdup("t1");
	registers[2] = strdup("t2");
	registers[3] = strdup("t3");
	registers[4] = strdup("t4");
	registers[5] = strdup("t5");
	registers[6] = strdup("t6");
	registers[7] = strdup("a0");	// Function parameters & returns, caller-saved
	registers[8] = strdup("a1");
	registers[9] = strdup("a2");
	registers[10] = strdup("a3");
	registers[11] = strdup("a4");
	registers[12] = strdup("a5");
	registers[13] = strdup("a6");
	registers[14] = strdup("a7");
	registers[15] = strdup("s0");	// Callee-saved
	registers[16] = strdup("s1");
	registers[17] = strdup("s2");
	registers[18] = strdup("s3");
	registers[19] = strdup("s4");
	registers[20] = strdup("s5");
	registers[21] = strdup("s6");
	registers[22] = strdup("s7");
	registers[23] = strdup("s8");
	registers[24] = strdup("s9");
	registers[25] = strdup("s10");
	registers[26] = strdup("s11");
}

int find_reg(int n_live, int* die, int* id2reg, char** reg2id)
{
	int idx = -1, oldest = -1;
	for (int i = 0; i < REG_N; i++)
		if (reg2id[i] == NULL)
			return i;
	for (int i = 0; i < n_live; i++)
	{
		if (id2reg[i] >= 0 && id2reg[i] < REG_STACK && die[i] < 0)
			return id2reg[i];
		if (id2reg[i] >= 0 && id2reg[i] < REG_STACK && die[i] > oldest)
		{
			idx = i;
			oldest = die[i];
		}
	}
	return id2reg[idx];
}

int reg_alloc(struct BasicBlock* arg_bb, int arg_stack_size, int *reg_alloced)
{
	int stack_size = arg_stack_size;
	int idx = 0;
	struct TreeNode* stmt;
	if (arg_bb == NULL)
		return arg_stack_size;
	if (arg_bb->str != NULL && strcmp(arg_bb->str, "RETURN") == 0)
		return arg_stack_size;
	if (arg_bb->str != NULL && strcmp(arg_bb->str, "RETURN") == 0)
		return arg_stack_size;
	if (arg_bb->reg2id != NULL || arg_bb->id2reg != NULL)
		return arg_stack_size;
	arg_bb->id2reg = (int**)malloc(sizeof(int*) * (arg_bb->n_stmt+1));
	arg_bb->reg2id = (char***)malloc(sizeof(char**) * (arg_bb->n_stmt+1));
	for (idx = 0; idx <= arg_bb->n_stmt; idx++)
	{
		arg_bb->id2reg[idx] = (int*)malloc(sizeof(int) * arg_bb->n_live[idx]);
		arg_bb->reg2id[idx] = (char**)malloc(sizeof(char*) * REG_N);
		memset(arg_bb->id2reg[idx], -1, sizeof(int) * arg_bb->n_live[idx]);
		memset(arg_bb->reg2id[idx], 0, sizeof(char*) * REG_N);
		for (int i = 0; i < arg_bb->n_live[idx]; i++)
			if (arg_bb->live[idx][i][0] == 'T')
				arg_bb->id2reg[idx][i] = REG_GLOBAL;
	}
	for (idx = 1, stmt = arg_bb->begin; idx <= arg_bb->n_stmt && stmt != arg_bb->end; idx++, stmt = stmt->nxt)
	{
		switch (stmt->type)
		{
		case TN_EXPR_ASSN:
			if (stmt->child[2] != NULL && stmt->child[2]->type == TN_ID)
			{
				for (int i = 0; i < arg_bb->n_live[idx-1]; i++)
					if (strcmp(stmt->child[2]->str, arg_bb->live[idx-1][i]) == 0)
					{
						if (arg_bb->id2reg[idx-1][i] < 0 || arg_bb->id2reg[idx-1][i] >= REG_N)
						{
							int tmp = find_reg(arg_bb->n_live[idx-1], arg_bb->die[idx-1], arg_bb->id2reg[idx-1], arg_bb->reg2id[idx-1]);
							for (int j = 0; j < arg_bb->n_live[idx-1]; j++)
								if (arg_bb->id2reg[idx-1][j] == tmp)
								{
									if (arg_bb->live[idx-1][j][0] == 'T')
										arg_bb->id2reg[idx-1][j] = REG_GLOBAL;
									else
									{
										arg_bb->id2reg[idx-1][j] = REG_STACK+stack_size;
										stack_size++;
									}
									free(arg_bb->reg2id[idx-1][tmp]);
									break;
								}
							arg_bb->id2reg[idx-1][i] = tmp;
							arg_bb->reg2id[idx-1][tmp] = strdup(arg_bb->live[idx-1][i]);
							reg_alloced[tmp] = 1;
						}
						break;
					}
			}
		case TN_EXPR_BI_LOGIC:
		case TN_EXPR_BI_ARITH:
		case TN_EXPR_IF_GOTO:
			if (stmt->child[1] != NULL && stmt->child[1]->type == TN_ID)
			{
				for (int i = 0; i < arg_bb->n_live[idx-1]; i++)
					if (strcmp(stmt->child[1]->str, arg_bb->live[idx-1][i]) == 0)
					{
						if (arg_bb->id2reg[idx-1][i] < 0 || arg_bb->id2reg[idx-1][i] >= REG_N)
						{
							int tmp = find_reg(arg_bb->n_live[idx-1], arg_bb->die[idx-1], arg_bb->id2reg[idx-1], arg_bb->reg2id[idx-1]);
							for (int j = 0; j < arg_bb->n_live[idx-1]; j++)
								if (arg_bb->id2reg[idx-1][j] == tmp)
								{
									if (arg_bb->live[idx-1][j][0] == 'T')
										arg_bb->id2reg[idx-1][j] = REG_GLOBAL;
									else
									{
										arg_bb->id2reg[idx-1][j] = REG_STACK+stack_size;
										stack_size++;
									}
									free(arg_bb->reg2id[idx-1][tmp]);
									break;
								}
							arg_bb->id2reg[idx-1][i] = tmp;
							arg_bb->reg2id[idx-1][tmp] = strdup(arg_bb->live[idx-1][i]);
							reg_alloced[tmp] = 1;
						}
						break;
					}
			}
		case TN_EXPR_UNI_LOGIC:
		case TN_EXPR_UNI_ARITH:
		case TN_EXPR_PARAM:
		case TN_EXPR_CALL:
		case TN_EXPR_RETURN:
			if (stmt->child[0] != NULL && stmt->child[0]->type == TN_ID)
			{
				for (int i = 0; i < arg_bb->n_live[idx-1]; i++)
					if (strcmp(stmt->child[0]->str, arg_bb->live[idx-1][i]) == 0)
					{
						if (arg_bb->id2reg[idx-1][i] < 0 || arg_bb->id2reg[idx-1][i] >= REG_N)
						{
							int tmp = find_reg(arg_bb->n_live[idx-1], arg_bb->die[idx-1], arg_bb->id2reg[idx-1], arg_bb->reg2id[idx-1]);
							for (int j = 0; j < arg_bb->n_live[idx-1]; j++)
								if (arg_bb->id2reg[idx-1][j] == tmp)
								{
									if (arg_bb->live[idx-1][j][0] == 'T')
										arg_bb->id2reg[idx-1][j] = REG_GLOBAL;
									else
									{
										arg_bb->id2reg[idx-1][j] = REG_STACK+stack_size;
										stack_size++;
									}
									free(arg_bb->reg2id[idx-1][tmp]);
									break;
								}
							arg_bb->id2reg[idx-1][i] = tmp;
							arg_bb->reg2id[idx-1][tmp] = strdup(arg_bb->live[idx-1][i]);
							reg_alloced[tmp] = 1;
						}
						break;
					}
			}
			break;
		case TN_VAR:
		case TN_EXPR_GOTO:
		case TN_EXPR_LABEL:
		default: break;
		}
		for (int i = 0; i < arg_bb->n_live[idx]; i++)
		for (int j = 0; j < arg_bb->n_live[idx-1]; j++)
			if (strcmp(arg_bb->live[idx][i], arg_bb->live[idx-1][j]) == 0)
			{
				arg_bb->id2reg[idx][i] = arg_bb->id2reg[idx-1][j];
				if (arg_bb->id2reg[idx][i] < REG_N)
					arg_bb->reg2id[idx][arg_bb->id2reg[idx][i]] = strdup(arg_bb->live[idx][i]);
				break;
			}
		switch (stmt->type)
		{
		case TN_EXPR_ASSN:
		case TN_EXPR_BI_LOGIC:
		case TN_EXPR_BI_ARITH:
		case TN_EXPR_UNI_LOGIC:
		case TN_EXPR_UNI_ARITH:
		case TN_EXPR_CALL:
			for (int i = 0; i < arg_bb->n_live[idx]; i++)
				if (strcmp(stmt->str, arg_bb->live[idx][i]) == 0)
				{
					if (arg_bb->id2reg[idx][i] < 0 || arg_bb->id2reg[idx][i] >= REG_N)
					{
						int tmp = find_reg(arg_bb->n_live[idx], arg_bb->die[idx], arg_bb->id2reg[idx], arg_bb->reg2id[idx]);
						int j;
						for (j = 0; j < arg_bb->n_live[idx]; j++)
							if (arg_bb->id2reg[idx][j] == tmp)
								break;
						if (j < arg_bb->n_live[idx] && (arg_bb->die[idx][j] > arg_bb->die[idx][i] || arg_bb->die[idx][j] < 0))
						{
							if (arg_bb->live[idx][j][0] == 'T')
								arg_bb->id2reg[idx][j] = REG_GLOBAL;
							else
							{
								arg_bb->id2reg[idx][j] = REG_STACK+stack_size;
								stack_size++;
							}
							arg_bb->id2reg[idx][i] = tmp;
							arg_bb->reg2id[idx][tmp] = strdup(arg_bb->live[idx-1][i]);
							reg_alloced[tmp] = 1;
						}
						else if (j < arg_bb->n_live[idx])
						{
							if (arg_bb->live[idx][i][0] == 'T')
								arg_bb->id2reg[idx][i] = REG_GLOBAL;
							else
							{
								arg_bb->id2reg[idx][i] = REG_STACK+stack_size;
								stack_size++;
							}
						}
						else
						{
							arg_bb->id2reg[idx][i] = tmp;
							arg_bb->reg2id[idx][tmp] = strdup(arg_bb->live[idx][i]);
							reg_alloced[tmp] = 1;
						}
					}
					break;
				}
		}
	}
	return stack_size;
}
