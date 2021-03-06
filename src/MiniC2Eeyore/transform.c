#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "transform.h"
#include "tree.h"
#include "symtab.h"

extern FILE* yyout;
extern char* infile_path;

void init_trans()
{
	T_idx = 0;
	t_idx = 0;
	p_idx = 0;
	l_idx = 0;
}

int minic2eeyore(struct TreeNode* arg_node, char* arg_prefix)
{
	char* prefix;
	struct TreeNode* tmp_node;
	struct Symbol* tmp_sym;
	int tmp, tmp_l, tmp_r, l_true, l_false, l_merge, l_cond;

	if (arg_node == NULL)
		return -1;
	prefix = (char*)malloc(sizeof(char)*(strlen(arg_prefix)+10));
	strcpy(prefix, arg_prefix);
	strcat(prefix, "\t");
	switch(arg_node->type)
	{
	case TN_ROOT:
		fprintf(yyout, "// Eeyore code\n");
		if (infile_path != NULL)
			fprintf(yyout, "//     MiniC source: %s\n", infile_path);
		else
			fprintf(yyout, "//     MiniC source: stdin\n");
		fprintf(yyout, "//     Author: Zhang Huangzhao\n");
		fprintf(yyout, "//\n");
		fprintf(yyout, "// View https://github.com/LC-John/MiniC-Compiler for detail\n\n\n");
		for (tmp_node = arg_node->child[0]; tmp_node != NULL; tmp_node = tmp_node->sibling_r)
			minic2eeyore(tmp_node, arg_prefix);
		minic2eeyore(arg_node->child[1], arg_prefix);
		free(prefix);
		return -1;
	case TN_FUNCDEFN:
		fprintf(yyout, "\n");
		p_idx = 0;
		for (tmp_node = arg_node->child[2], tmp = 0;
			tmp_node != NULL; tmp_node = tmp_node->sibling_r, tmp++)
		{
			fprintf(yyout, "%s// [PARAM] ", arg_prefix);
			minic2eeyore(tmp_node, prefix);
		}
		fprintf(yyout, "%sf_%s [%d]", arg_prefix, arg_node->child[1]->name, tmp);
		fprintf(yyout, "\t// [FUNC] %s @ Line %d\n", arg_node->child[1]->name, arg_node->lineno);
		p_idx = 0;
		for (tmp_node = arg_node->child[3]; tmp_node != NULL; tmp_node = tmp_node->sibling_r)
			minic2eeyore(tmp_node, prefix);
		fprintf(yyout, "%send f_%s\n\n", arg_prefix, arg_node->child[1]->name);
	case TN_FUNCDECL: free(prefix); return -1;
	case TN_VARDEFN:
		if (arg_node->child[2] == NULL)
		{
			fprintf(yyout, "%svar T%d", arg_prefix, T_idx);
			tmp_sym = get_sym(arg_node->lineno, arg_node->child[1]->name);
		}
		else
		{
			fprintf(yyout, "%svar %d T%d", arg_prefix,
				arg_node->child[2]->val*4, T_idx);
			tmp_sym = get_sym(arg_node->lineno, arg_node->child[1]->name);
		}
		fprintf(yyout, "\t// [VAR] %s @ Line %d\n", arg_node->child[1]->name, arg_node->lineno);
		tmp_sym->eeyore_var_idx = T_idx++;
		tmp_sym->eeyore_var_type = 'T';
		free(prefix);
		return -1;
	case TN_VARDECL:
		tmp_sym = get_sym(arg_node->lineno, arg_node->child[1]->name);
		tmp_sym->eeyore_var_idx = p_idx++;
		tmp_sym->eeyore_var_type = 'p';
		fprintf(yyout, "%c%d = %s @ Line %d\n", tmp_sym->eeyore_var_type, tmp_sym->eeyore_var_idx,
			arg_node->child[1]->name, arg_node->lineno);
		free(prefix);
		return -1;
	case TN_STMT_BLOCK:
		fprintf(yyout, "%s// [BLK] BLOCK @ Line %d\n", arg_prefix, arg_node->lineno);
		for (tmp_node = arg_node->child[0]; tmp_node != NULL; tmp_node = tmp_node->sibling_r)
			minic2eeyore(tmp_node, arg_prefix);
		free(prefix);
		return -1;
	case TN_STMT_IF:
		l_true = l_idx++;
		l_merge = l_idx++;
		l_false = l_idx++;
		tmp_l = minic2eeyore(arg_node->child[0], arg_prefix);
		fprintf(yyout, "%sif t%d != 0 goto l%d", arg_prefix, tmp_l, l_true);
		fprintf(yyout, "\t// [BLK] IF @ Line %d\n", arg_node->lineno);
		fprintf(yyout, "%sgoto l%d\n", arg_prefix, l_false);
		fprintf(yyout, "l%d:\n", l_true);
		for (tmp_node = arg_node->child[1];
			tmp_node != NULL; tmp_node = tmp_node->sibling_r)
			minic2eeyore(tmp_node, prefix);
		fprintf(yyout, "%sgoto l%d\n", prefix, l_merge);
		fprintf(yyout, "l%d:\n", l_false);
		for (tmp_node = arg_node->child[2];
			tmp_node != NULL; tmp_node = tmp_node->sibling_r)
			minic2eeyore(tmp_node, prefix);
		fprintf(yyout, "l%d:\n", l_merge);
		free(prefix);
		return -1;
	case TN_STMT_WHILE:
		l_cond = l_idx++;
		l_true = l_idx++;
		l_merge = l_idx++;
		fprintf(yyout, "l%d:\n", l_cond);
		tmp_l = minic2eeyore(arg_node->child[0], arg_prefix);
		fprintf(yyout, "%sif t%d != 0 goto l%d", arg_prefix, tmp_l, l_true);
		fprintf(yyout, "\t// [BLK] WHILE @ Line %d\n", arg_node->lineno);
		fprintf(yyout, "%sgoto l%d\n", arg_prefix, l_merge);
		fprintf(yyout, "l%d:\n", l_true);
		for (tmp_node = arg_node->child[1];
			tmp_node != NULL; tmp_node = tmp_node->sibling_r)
			minic2eeyore(tmp_node, prefix);
		fprintf(yyout, "%sgoto l%d\n", prefix, l_cond);
		fprintf(yyout, "l%d:\n", l_merge);
		free(prefix);
		return -1;
	case TN_STMT_VARASSN:
		tmp_l = minic2eeyore(arg_node->child[1], arg_prefix);
		tmp_sym = get_sym(arg_node->child[0]->lineno, arg_node->child[0]->name);
		fprintf(yyout, "%s%c%d = t%d", arg_prefix,
			tmp_sym->eeyore_var_type, tmp_sym->eeyore_var_idx, tmp_l);
		fprintf(yyout, "\t// [STMT] VAR ASSN @ Line %d\n", arg_node->lineno);
		free(prefix);
		return -1;
	case TN_STMT_ARRASSN:
		tmp_l = minic2eeyore(arg_node->child[1], arg_prefix);
		tmp_r = minic2eeyore(arg_node->child[2], arg_prefix);
		tmp = t_idx++;
		fprintf(yyout, "%svar t%d\n", arg_prefix, tmp);
		fprintf(yyout, "%st%d = t%d * 4\n", arg_prefix, tmp, tmp_l);
		tmp_sym = get_sym(arg_node->child[0]->lineno, arg_node->child[0]->name);
		fprintf(yyout, "%s%c%d [t%d] = t%d", arg_prefix,
			tmp_sym->eeyore_var_type, tmp_sym->eeyore_var_idx, tmp, tmp_r);
		fprintf(yyout, "\t// [STMT] ARR ASSN @ Line %d\n", arg_node->lineno);
		free(prefix);
		return -1;
	case TN_STMT_VARDEFN:
		minic2eeyore(arg_node->child[0], arg_prefix);
		free(prefix);
		return -1;
	case TN_STMT_RETURN:
		tmp_l = minic2eeyore(arg_node->child[0], arg_prefix);
		fprintf(yyout, "%sreturn t%d", arg_prefix, tmp_l);
		fprintf(yyout, "\t// [STMT] RET @ Line %d\n", arg_node->lineno);
		free(prefix);
		return -1;
	case TN_EXPR_BIARITH:
	case TN_EXPR_BILOGIC:
		tmp_l = minic2eeyore(arg_node->child[0], arg_prefix);
		tmp_r = minic2eeyore(arg_node->child[1], arg_prefix);
		tmp = t_idx++;
		fprintf(yyout, "%svar t%d\n", arg_prefix, tmp);
		fprintf(yyout, "%st%d = t%d %s t%d", arg_prefix, tmp, tmp_l, arg_node->name, tmp_r);
		fprintf(yyout, "\t// [EXPR] BI OP %s @ Line %d\n", arg_node->name, arg_node->lineno);
		free(prefix);
		return tmp;
	case TN_EXPR_ARR:
		tmp_sym = get_sym(arg_node->child[0]->lineno, arg_node->child[0]->name);
		tmp_l = minic2eeyore(arg_node->child[1], arg_prefix);
		tmp_r = t_idx++;
		fprintf(yyout, "%svar t%d\n", arg_prefix, tmp_r);
		fprintf(yyout, "%st%d = t%d * 4\n", arg_prefix, tmp_r, tmp_l);
		tmp = t_idx++;
		fprintf(yyout, "%svar t%d\n", arg_prefix, tmp);
		fprintf(yyout, "%st%d = %c%d [t%d]", arg_prefix, tmp,
			tmp_sym->eeyore_var_type, tmp_sym->eeyore_var_idx, tmp_r);
		fprintf(yyout, "\t// [EXPR] ARR @ Line %d\n", arg_node->lineno);
		free(prefix);
		return tmp;
	case TN_EXPR_INTEGER:
		tmp = t_idx++;
		fprintf(yyout, "%svar t%d\n", arg_prefix, tmp);
		fprintf(yyout, "%st%d = %d", arg_prefix, tmp, arg_node->child[0]->val);
		fprintf(yyout, "\t// [EXPR] NUM @ Line %d\n", arg_node->lineno);
		free(prefix);
		return tmp;
	case TN_EXPR_IDENTIFIER:
		tmp_sym = get_sym(arg_node->child[0]->lineno, arg_node->child[0]->name);
		tmp = t_idx++;
		fprintf(yyout, "%svar t%d\n", arg_prefix, tmp);
		fprintf(yyout, "%st%d = %c%d", arg_prefix, tmp,
			tmp_sym->eeyore_var_type, tmp_sym->eeyore_var_idx);
		fprintf(yyout, "\t// [EXPR] VAR @ Line %d\n", arg_node->lineno);
		free(prefix);
		return tmp;
	case TN_EXPR_UNI:
		tmp_r = minic2eeyore(arg_node->child[0], arg_prefix);
		tmp = t_idx++;
		fprintf(yyout, "%svar t%d\n", arg_prefix, tmp);
		fprintf(yyout, "%st%d = %s t%d", arg_prefix, tmp, arg_node->name, tmp_r);
		fprintf(yyout, "\t// [EXPR] UNI OP %s @ Line %d\n", arg_node->name, arg_node->lineno);
		free(prefix);
		return tmp;
	case TN_EXPR_CALL:
		tmp = t_idx++;
		fprintf(yyout, "%svar t%d\n", arg_prefix, tmp);
		for (tmp_node = arg_node->child[1]; tmp_node != NULL; tmp_node = tmp_node->sibling_r)
		{
			tmp_sym = get_sym(tmp_node->lineno, tmp_node->name);
			fprintf(yyout, "%sparam %c%d\n", arg_prefix,
				tmp_sym->eeyore_var_type, tmp_sym->eeyore_var_idx);
		}
		fprintf(yyout, "%st%d = call f_%s", arg_prefix, tmp, arg_node->child[0]->name);
		fprintf(yyout, "\t// [EXPR] CALL %s @ Line %d\n", arg_node->child[0]->name, arg_node->lineno);
		free(prefix);
		return tmp;
	case TN_TYPE:
	case TN_INTEGER:
	case TN_IDENTIFIER: free(prefix); return -1;
	case TN_INIT:
	default:
		fprintf(stderr, ">> ERROR: Unknown parse tree node\n");
		fprintf(stderr, "   Please use \"-T\" or \"--tree\" option to check the parse tree\n");
		exit(-3);
	}
}
