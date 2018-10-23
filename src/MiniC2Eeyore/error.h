#ifndef __ERROR_H__
#define __ERROR_H__

#include "symtab.h"
#include "tree.h"

#define EW_INIT			0
#define ERR_CONFLICT_VAR	1
#define ERR_CONFLICT_FUNC	2
#define ERR_WRONG_ASSN		3
#define ERR_WRONG_PARAM		4
#define WARN_MIXED_EXPR		100
#define WARN_NO_RETURN		101
#define WARN_FUNCDECL_IN_BODY	102

struct ErrorWarning
{
	int idx;
	int type;
	struct TreeNode* node;
	struct Symbol* sym1;
	struct Symbol* sym2;
	struct ErrorWarning* nxt;
	struct ErrorWarning* prv;
};

int n_ew;
struct ErrorWarnig* ew_list;

void init_ew();
struct ErrorWarning* alloc_ew();

#endif
