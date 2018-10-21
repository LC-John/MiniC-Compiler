%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "yaccTypes.h"
int yylex(void);
extern int yylineno;
%}

%code requires {
void yyerror(const char *s);
#define REGNUM 28
extern const char *str_reg[REGNUM];
}

%union {
    char *vstr;
    int vint;
}

%token <vint> INT_CONSTANT GVAR LABEL REGISTER
%token <vstr> FUNCTION
%token END IF GOTO CALL LOAD STORE MALLOC LOADADDR RETURN
%token GE LE AND OR NE EQ

%type <vint> integer
%type <vstr> operator

%%

start: block
     |
     ;

block: function_declare
     | global_var_declare
     | block function_declare
     | block global_var_declare
     ;

function_declare: FUNCTION '[' INT_CONSTANT ']' '[' INT_CONSTANT ']' {
                        add_func_begin($1, $3, $6);
                    } expression_list END FUNCTION {
                        if (strcmp($1, $11) != 0)
                            yyerror("function declare name not match");
                        stmts.push_back(new stmt_func_end($1));
                    }
                ;

integer: INT_CONSTANT   {$$=$1;}
       | '-' INT_CONSTANT {$$=-$2;}

global_var_declare: GVAR '=' MALLOC INT_CONSTANT { add_gvar_array($1, $4); }
                  | GVAR '=' integer   { add_gvar_int($1, $3); }
                  ;

expression_list: 
               | expression_list expression
               ;

operator: '+' {$$=strdup("+");}
        | '-' {$$=strdup("-");}
        | '*' {$$=strdup("*");}
        | '/' {$$=strdup("/");}
        | '%' {$$=strdup("%");}
        | '>' {$$=strdup(">");}
        | '<' {$$=strdup("<");}
        | '!' {$$=strdup("!");}
        | LE {$$=strdup("<=");}
        | GE {$$=strdup(">=");}
        | AND {$$=strdup("&&");}
        | OR {$$=strdup("||");}
        | NE {$$=strdup("!=");}
        | EQ {$$=strdup("==");}
        ;

expression: REGISTER '=' integer   {check_zero_written($1); stmts.push_back(new stmt_assign_const($1, $3));}
          | REGISTER '=' REGISTER operator REGISTER     {check_zero_written($1); check_op2($4); stmts.push_back(new stmt_assign_op2($1, $3, $4, $5));}
          | REGISTER '=' REGISTER operator integer {check_zero_written($1); check_op2i($4); stmts.push_back(new stmt_assign_op2i($1, $3, $4, $5));}
          | REGISTER '=' operator REGISTER  {check_zero_written($1); check_op1($3); stmts.push_back(new stmt_assign_op1($1, $3, $4));}
          | REGISTER '=' REGISTER   {check_zero_written($1); stmts.push_back(new stmt_assign_move($1, $3));}
          | REGISTER '[' INT_CONSTANT ']' '=' REGISTER  {check_zero_written($1); stmts.push_back(new stmt_assign_lidx($1, $3, $6));}
          | REGISTER '=' REGISTER '[' INT_CONSTANT ']'  {check_zero_written($1); stmts.push_back(new stmt_assign_ridx($1, $3, $5));}
          | IF REGISTER operator REGISTER GOTO LABEL    {check_op2($3); stmts.push_back(new stmt_if_goto($2, $3, $4, $6));}
          | GOTO LABEL  {stmts.push_back(new stmt_goto($2));}
          | LABEL ':'   {add_label($1);}
          | CALL FUNCTION   {stmts.push_back(new stmt_call($2));}
          | STORE REGISTER INT_CONSTANT {stmts.push_back(new stmt_store_local($2, $3));}
          /*| STORE REGISTER GVAR {check_gvar($3); stmts.push_back(new stmt_store_global($2, gvar_name[$3]));}*/
          | LOAD INT_CONSTANT REGISTER  {check_zero_written($3); stmts.push_back(new stmt_load_local($2, $3));}
          | LOAD GVAR REGISTER  {check_gvar($2); check_zero_written($3); stmts.push_back(new stmt_load_global(gvar_name[$2], $3));}
          | LOADADDR INT_CONSTANT REGISTER {check_zero_written($3); stmts.push_back(new stmt_loadaddr_local($2, $3));}
          | LOADADDR GVAR REGISTER {check_gvar($2); check_zero_written($3); stmts.push_back(new stmt_loadaddr_global(gvar_name[$2], $3));}
          | RETURN {stmts.push_back(new stmt_return());}
          /*| REGISTER '=' MALLOC INT_CONSTANT {if ($4 % 4 != 0 || $4 == 0) yyerror("what do you mean by this mallocing size?"); stmts.push_back(new stmt_malloc($1, $4));}*/
          ;

%%

void yyerror(const char *s)
{
    printf("line %d: %s\n", yylineno, s);
    exit(1);
}
