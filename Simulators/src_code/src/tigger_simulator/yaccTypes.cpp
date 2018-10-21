#include "yaccTypes.h"
#include <cstdlib>

void yyerror(const char *s);

void check_op2i(const char *s)
{
    const int nop = 2;
    static const char *op[nop] = {"+", "<"};
    for (int i = 0; i < nop; ++i)
        if (strcmp(s, op[i]) == 0)
            return;
    yyerror("OP2i required");
}

void check_op2(const char *s)
{
    const int nop = 13;
    static const char *op[nop] = {"+", "-", "*", "/", "%", ">", "<", ">=", "<=", "&&", "||", "!=", "=="};
    for (int i = 0; i < nop; ++i)
        if (strcmp(s, op[i]) == 0)
            return;
    yyerror("OP2 required");
}

void check_op1(const char *s)
{
    const int nop = 4;
    static const char *op[nop] = {"+", "-", "*", "!"};
    for (int i = 0; i < nop; ++i)
        if (strcmp(s, op[i]) == 0)
            return;
    yyerror("OP1 required");
}

void check_rop(const char *s)
{
    const int nop = 8;
    static const char *op[nop] = {">", "<", ">=", "<=", "&&", "||", "!=", "=="};
    for (int i = 0; i < nop; ++i)
        if (strcmp(s, op[i]) == 0)
            return;
    yyerror("logical OP required");
}

void add_func_begin(const std::string &fname, int argNum, int stackSlotNum)
{
    statement_t *p = new stmt_func_begin(fname, argNum, stackSlotNum);
    funcs[fname] = stmts.size();
    stmts.push_back(p);
}

void add_label(int lnum)
{
    labels[lnum] = stmts.size();
    stmts.push_back(new stmt_label(lnum));
}

void add_gvar_int(int xnum, int value)
{
    if (gvar_name.find(xnum) != gvar_name.end())
        yyerror("gvar already exists");
    gvar_name[xnum] = ngvar++;
    gvars.push_back(new int(value));
}

void add_gvar_array(int xnum, int size)
{
    if (gvar_name.find(xnum) != gvar_name.end())
        yyerror("gvar already exists");
    gvar_name[xnum] = ngvar++;
    gvars.push_back((int*)malloc(size));
}

void check_zero_written(int rnum)
{
    if (rnum == 0)
        yyerror("write to x0");
}

void check_gvar(int xnum)
{
    if (gvar_name.find(xnum) == gvar_name.end())
        yyerror("gvar not declared");
}
