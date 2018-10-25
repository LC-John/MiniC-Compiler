#ifndef __ERROR_H__
#define __ERROR_H__

#include "symtab.h"
#include "tree.h"

#define EW_INIT			0
#define ERR_CONFLICT_VAR	1
#define ERR_CONFLICT_FUNC	2
#define ERR_WRONG_ASSN		3
#define ERR_WRONG_PARAM		4
#define ERR_UNDEFINED_VAR	5
#define ERR_UNDEFINED_FUNC	6
#define ERR_WRONG_CALL		7
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
struct ErrorWarning *ew_list;
struct ErrorWarning *ew_tail;

void init_ew();
struct ErrorWarning* alloc_ew(int, struct TreeNode*, struct Symbol*, struct Symbol*);
void free_ew(struct ErrorWarning*);
void print_ew();

int find_conflict();
int find_var(int, struct TreeNode*);
int find_func(struct TreeNode*);

#endif
