#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"

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
	case ERR_CONFLICT_VAR: break;
	case ERR_CONFLICT_FUNC: break;
	case ERR_WRONG_ASSN: break;
	case ERR_WRONG_PARAM: break;
	case WARN_MIXED_EXPR: break;
	case WARN_NO_RETURN: break;
	case WARN_FUNCDECL_IN_BODY: break;
	default: ew->type = EW_INIT; break;
	}
	return ew;
}
