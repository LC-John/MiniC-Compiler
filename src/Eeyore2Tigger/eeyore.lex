%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
#include "tree.h"

void yyerror(char*);
int lineno;
FILE* cheating_file;
%}

%%

[ \t]+		{ ; }
[\n]	{ lineno++; yylval.str = strdup(yytext); return EOL; }

"var"		{ yylval.str = strdup(yytext); return VAR; }
"end"		{ yylval.str = strdup(yytext); return END; }
"if"		{ yylval.str = strdup(yytext); return IF; }
"goto"		{ yylval.str = strdup(yytext); return GOTO; }
"param"		{ yylval.str = strdup(yytext); return PARAM; }
"call"		{ yylval.str = strdup(yytext); return CALL; }
"return"	{ yylval.str = strdup(yytext); return RETURN; }

[t][0-9]+		{ yylval.str = strdup(yytext); return ID_TMP; }
[p][0-9]+		{ yylval.str = strdup(yytext); return ID_PARAM; }
[T][0-9]+		{ yylval.str = strdup(yytext); return ID_NATIVE; }
[l][0-9]+		{ yylval.str = strdup(yytext); return ID_LABEL; }
[f][_][0-9a-zA-Z]+	{ yylval.str = strdup(yytext+2); return ID_FUNC; }
[0-9]+			{ yylval.val = atoi(yytext); return NUM; }

"="	{ yylval.val = OP_ASSN; return ASSIGN; }

"&&"	{ yylval.val = OP_AND; return OP_BI_LOGIC; }
"||"	{ yylval.val = OP_OR; return OP_BI_LOGIC; }
"=="	{ yylval.val = OP_EQ; return OP_BI_LOGIC; }
"!="	{ yylval.val = OP_NE; return OP_BI_LOGIC; }
"<"	{ yylval.val = OP_LT; return OP_BI_LOGIC; }
">"	{ yylval.val = OP_GT; return OP_BI_LOGIC; }

"+"	{ yylval.val = OP_ADD; return OP_BI_ARITH; }
"-"	{ yylval.val = OP_SUB; return OP_BI_ARITH; }
"*"	{ yylval.val = OP_MUL; return OP_BI_ARITH; }
"/"	{ yylval.val = OP_DIV; return OP_BI_ARITH; }
"%"	{ yylval.val = OP_MOD; return OP_BI_ARITH; }

"!"	{ yylval.val = OP_NOT; return OP_UNI; }

"["	{ yylval.val = lineno; return ARR_L; }
"]"	{ yylval.val = lineno; return ARR_R; }
":"	{ yylval.val = lineno; return COLON; }

"//"[^\n]*	{ ; }

. {
	char msg[100] = "unrecognized input ";
	strcat(msg, yytext);
	yyerror(msg);
}

%%

int yywrap()
{
	return 1;
}
