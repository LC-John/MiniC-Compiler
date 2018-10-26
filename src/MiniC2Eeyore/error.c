#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "symtab.h"
#include "tree.h"

void init_ew()
{
	n_ew = 0;
	ew_list = (struct ErrorWarning*)malloc(sizeof(struct ErrorWarning));
	ew_list->idx = -1;
	ew_list->type = EW_INIT;
	ew_list->node = NULL;
	ew_list->sym1 = NULL;
	ew_list->sym2 = NULL;
	ew_list->nxt = NULL;
	ew_list->prv = NULL;
	ew_tail = ew_list;
}

struct ErrorWarning* alloc_ew(int arg_type, struct TreeNode* arg_node,
	struct Symbol* arg_sym1, struct Symbol* arg_sym2)
{
	struct ErrorWarning* ew = (struct ErrorWarning*)malloc(sizeof(struct ErrorWarning));
	ew->idx = n_ew++;
	ew->type = arg_type;
	ew_list->node = NULL;
	ew_list->sym1 = NULL;
	ew_list->sym2 = NULL;
	switch(ew->type)
	{
	case ERR_CONFLICT_VAR:	// the two variable symbols are conflict
	case ERR_CONFLICT_FUNC:	// the function symbol is conflict with the other symbol
		ew->sym1 = arg_sym1; ew->sym2 = arg_sym2;
		break;
	case ERR_WRONG_PARAM:	// calling node's parameters are conflict with the function symbol
		ew->node = arg_node; ew->sym1 = arg_sym1;
		break;
	case ERR_WRONG_ASSN:	// assignment node is type conflict with the variable symbol
	case ERR_WRONG_CALL:	// function calling node is type conflict with the variable symbol
	case ERR_UNDEFINED_VAR:	// use an undefined variable
	case ERR_UNDEFINED_FUNC:	// call an undefined function
	case WARN_MIXED_EXPR:	// mix logical and arithmatic expressions together
	case WARN_NO_RETURN:	// the last statement is not a return
	case WARN_FUNCDECL_IN_BODY:	// declare functions in the function body
		ew->node = arg_node;
		break;
	default:	// Something goes wrong...
		ew->type = EW_INIT;
		break;
	}
	ew->nxt = NULL;
	ew->prv = ew_tail;
	ew_tail->nxt = ew;
	ew_tail = ew;
	return ew;
}

void free_ew(struct ErrorWarning* arg_ew)
{
	arg_ew->prv->nxt = arg_ew->nxt;
	if (arg_ew != ew_tail)
		arg_ew->nxt->prv = arg_ew->prv;
	else
		ew_tail = arg_ew->prv;
	free(arg_ew);
}

void print_ew()
{
	struct ErrorWarning* ew = ew_list->nxt;
	struct TreeNode* tmp_node;
	while(ew != NULL)
	{
		switch(ew->type)
		{
		case ERR_CONFLICT_VAR:
			fprintf(stderr, ">> ERROR@L%d&L%d: conflict variables %s & %s\n", ew->sym1->bornAt, ew->sym2->bornAt, ew->sym1->name, ew->sym2->name);
			exit(-3);
		case ERR_CONFLICT_FUNC:
			fprintf(stderr, ">> ERROR@L%d&L%d: conflict function(s) %s & %s\n", ew->sym1->bornAt, ew->sym2->bornAt, ew->sym1->name, ew->sym2->name);
			exit(-3);
		case ERR_WRONG_ASSN:
			fprintf(stderr, ">> ERROR@L%d: wrong assignment\n", ew->node->lineno);
			exit(-3);
		case ERR_WRONG_CALL:
			fprintf(stderr, ">> ERROR@L%d: wrong function call\n", ew->node->lineno);
			exit(-3);
		case ERR_WRONG_PARAM:
			fprintf(stderr, ">> ERROR@L%d: wrong actual parameters\n", ew->node->lineno);
			exit(-3);
		case ERR_UNDEFINED_VAR:
			fprintf(stderr, ">> ERROR@L%d: undefined variable %s\n", ew->node->lineno, ew->node->name);
			exit(-3);
		case ERR_UNDEFINED_FUNC:
			fprintf(stderr, ">> ERROR@L%d: undefined function %s\n", ew->node->lineno, ew->node->name);
			exit(-3);
		case WARN_MIXED_EXPR:
			fprintf(stderr, ">> WARNING@L%d: mixed expression type\n", ew->node->lineno);
			break;
		case WARN_NO_RETURN:
			fprintf(stderr, ">> WARNING@L%d: missing return\n", ew->node->lineno);
			break;
		case WARN_FUNCDECL_IN_BODY:
			fprintf(stderr, ">> WARNING@L%d: function declaration (%s) in function body (%s)\n", ew->node->lineno, ew->node->child[1]->name, ew->node->parent->child[1]->name);
			break;
		default: ew->type = EW_INIT; break;
		}
		ew = ew->nxt;
	}
}

int find_conflict()
{
	if (symtab->nxt == NULL)
		return 0;
	if (symtab->nxt->nxt == NULL)
		return 0;
	for (struct Symbol* i = symtab->nxt->nxt; i != NULL; i = i->nxt)
		for (struct Symbol* j = symtab->nxt; j != NULL && j != i; j = j->nxt)
			if (strcmp(i->name, j->name) == 0)
			{
				if (i->dieAt == j->dieAt
					&& (i->type == ST_INT || i->type == ST_ARR)
					&& (j->type == ST_INT || j->type == ST_ARR))
				{
					alloc_ew(ERR_CONFLICT_VAR, NULL, i, j);
					return 1;
				}
				else if (i->type == ST_FUNC || j->type == ST_FUNC)
				{
					alloc_ew(ERR_CONFLICT_FUNC, NULL, i, j);
					return 1;
				}
			}
	return 0;
}

int find_var(int arg_type, struct TreeNode* arg_node)
{
	struct Symbol* sym = get_sym(arg_node->lineno, arg_node->name);
	if (sym == NULL)
	{
		alloc_ew(ERR_UNDEFINED_VAR, arg_node, NULL, NULL);
		return 0;
	}
	else if (sym->type != arg_type)
	{
		alloc_ew(ERR_WRONG_ASSN, arg_node, NULL, NULL);
		return 0;
	}
	else
		return 1;
}

int find_func(struct TreeNode* arg_node)
{
	struct Symbol* sym = get_sym(arg_node->child[0]->lineno, arg_node->child[0]->name);
	struct TreeNode *formal, *actual;
	if (sym == NULL)
	{
		alloc_ew(ERR_UNDEFINED_FUNC, arg_node->child[0], NULL, NULL);
		return 0;
	}
	else if (sym->type != ST_FUNC)
	{
		alloc_ew(ERR_WRONG_CALL, arg_node->child[0], NULL, NULL);
		return 0;
	}
	for (formal = sym->node->child[2], actual = arg_node->child[1];
		formal != NULL && actual != NULL;
		formal = formal->sibling_r, actual = actual->sibling_r)
	{
		struct Symbol *tmp = get_sym(actual->lineno, actual->name);
		if (tmp == NULL)
		{
			alloc_ew(ERR_WRONG_PARAM, arg_node, sym, NULL);
			return 0;		
		}
		if ((formal->child[2] == NULL && tmp->type != ST_INT)
			|| (formal->child[2] != NULL && tmp->type != ST_ARR))
		{
			alloc_ew(ERR_WRONG_PARAM, arg_node, sym, NULL);
			return 0;
		}
	}
	if (formal != NULL || actual != NULL)
	{
		alloc_ew(ERR_WRONG_PARAM, arg_node, sym, NULL);
		return 0;
	}
	return 1;
}

void find_wrong_call(struct TreeNode* arg_node)
{
	if (arg_node == NULL)
		return;
	if (arg_node->type == TN_EXPR_CALL && find_func(arg_node) == 0)
		print_ew();
	find_wrong_call(arg_node->sibling_r);
	for (int i = 0; i < arg_node->n_child; i++)
		find_wrong_call(arg_node->sibling_r);
}
