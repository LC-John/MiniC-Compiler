%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "y.tab.h"

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

[t][0-9]+		{ yylval.val = atoi(yytext+1); return ID_TMP; }
[p][0-9]+		{ yylval.val = atoi(yytext+1); return ID_PARAM; }
[T][0-9]+		{ yylval.val = atoi(yytext+1); return ID_NATIVE; }
[l][0-9]+		{ yylval.val = atoi(yytext+1); return ID_LABEL; }
[f][_][0-9a-zA-Z]+	{ yylval.str = strdup(yytext); return ID_FUNC; }
[0-9]+			{ yylval.val = atoi(yytext); return NUM; }

"="	{ yylval.str = strdup(yytext); return ASSIGN; }
"&&"	{ yylval.str = strdup(yytext); return OP_BI_LOGIC; }
"||"	{ yylval.str = strdup(yytext); return OP_BI_LOGIC; }
"=="	{ yylval.str = strdup(yytext); return OP_BI_LOGIC; }
"!="	{ yylval.str = strdup(yytext); return OP_BI_LOGIC; }
"<"	{ yylval.str = strdup(yytext); return OP_BI_LOGIC; }
">"	{ yylval.str = strdup(yytext); return OP_BI_LOGIC; }
"+"	{ yylval.str = strdup(yytext); return OP_BI_LOGIC; }
"-"	{ yylval.str = strdup(yytext); return OP_BI_ARITH; }
"*"	{ yylval.str = strdup(yytext); return OP_BI_ARITH; }
"/"	{ yylval.str = strdup(yytext); return OP_BI_ARITH; }
"%"	{ yylval.str = strdup(yytext); return OP_BI_ARITH; }
"!"	{ yylval.str = strdup(yytext); return OP_UNI; }

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
