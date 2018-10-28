#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "symtab.h"

struct Symbol* alloc_symbol(int arg_line, int arg_type, char* arg_name, struct TreeNode* arg_node)
{
	char* name;
	struct Symbol* sym = (struct Symbol*)malloc(sizeof(struct Symbol));
	sym->idx = n_symbol++;
	sym->type = arg_type;
	if (arg_name == NULL)
		name = strdup("");
	else
		name = strdup(arg_name);
	sym->name = name;
	sym->eeyore_var_idx = -1;
	sym->eeyore_var_type = 'E';
	switch(sym->type)
	{
	case ST_INT:
	case ST_ARR:
	case ST_FUNC: sym->bornAt = arg_line; sym->dieAt = -1; break;
	default: sym->type = ST_INIT; break;
	}
	sym->node = arg_node;
	sym->nxt = NULL;
	if (symtab != NULL)
	{
		sym->prv = tail;
		tail->nxt = sym;
	}
	else
		sym->prv = NULL;
	tail = sym;
	return sym;
}

void free_symbol(struct Symbol* arg_sym)
{
	if (arg_sym == symtab)
		return;
	if (arg_sym->name != NULL)
		free(arg_sym->name);
	arg_sym->prv->nxt = arg_sym->nxt;
	if (arg_sym->nxt != NULL)
		arg_sym->nxt->prv = arg_sym->prv;
	else
		tail = arg_sym->prv;
	free(arg_sym);
}

void init_symtab()
{
	n_symbol = -1;
	symtab = alloc_symbol(-1, ST_INIT, NULL, NULL);
	tail = symtab;
}

struct Symbol* get_sym(int arg_lineno, char* arg_name)
{
	struct Symbol* sym = symtab->nxt, *res = NULL;
	while(sym != NULL)
	{
		if (strcmp(sym->name, arg_name) == 0
			&& arg_lineno >= sym->bornAt
			&& (arg_lineno <= sym->dieAt || sym->dieAt == -1))
		{
			if (res == NULL)
				res = sym;
			else if (res->bornAt < sym->bornAt)
				res = sym;
		}
		sym = sym->nxt;
	}
	return res;
}

void set_death(int arg_born, int arg_die)
{
	struct Symbol* sym = symtab->nxt;
	while(sym != NULL)
	{
		if (sym->bornAt >= arg_born && sym->bornAt <= arg_die
		    && sym->dieAt < 0)
			sym->dieAt = arg_die;
		sym = sym->nxt;
	}
}

void purge_var(int arg_born, int arg_die)
{
	struct Symbol* sym = symtab->nxt;
	while(sym != NULL)
	{
		if (sym->bornAt >= arg_born && sym->bornAt <= arg_die
		    && sym->dieAt < 0)
			free_symbol(sym);
		sym = sym->nxt;
	}
}

void print_symtab(FILE* f)
{
	struct Symbol* sym = symtab->nxt;
	while(sym != NULL)
	{
		switch(sym->type)
		{
		case ST_INT: fprintf(f, "%d\t[INT] \t%-12s\tL%d~L%d\t%c%d\n",
			sym->idx, sym->name, sym->bornAt, sym->dieAt,
			sym->eeyore_var_type, sym->eeyore_var_idx); break;
		case ST_ARR: fprintf(f, "%d\t[ARR] \t%-12s\tL%d~L%d\t%c%d\n",
			sym->idx, sym->name, sym->bornAt, sym->dieAt,
			sym->eeyore_var_type, sym->eeyore_var_idx); break;
		case ST_FUNC: fprintf(f, "%d\t[FUNC]\t%-12s\tL%d~L%d\n",
			sym->idx, sym->name, sym->bornAt, sym->dieAt); break;
		case ST_INIT:
		default: fprintf(f, "%d\t{ERR}  \t%-12s\tL%d~L%d\n",
			sym->idx, sym->name, sym->bornAt, sym->dieAt); break;
		}
		sym = sym->nxt;
	}
}
