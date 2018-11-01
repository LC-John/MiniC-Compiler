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

[ \t]+
[\n]	{ lineno++; }

"var"		{ yylval.str = strdup(yytext); return VAR; }
"end"		{ yylval.str = strdup(yytext); return END; }
"if"		{ yylval.str = strdup(yytext); return IF; }
"goto"		{ yylval.str = strdup(yytext); return GOTO; }
"param"		{ yylval.str = strdup(yytext); return PARAM; }
"call"		{ yylval.str = strdup(yytext); return CALL; }
"return"	{ yylval.str = strdup(yytext); return RETURN; }

[t][0-9]+			{ yylval.val = atoi(yytext+1); return ID_TEMP; }
[p][0-9]+			{ yylval.val = atoi(yytext+1); return ID_PARAM; }
[T][0-9]+			{ yylval.val = atoi(yytext+1); return ID_NATIVE; }
[0-9]+				{ yylval.val = atoi(yytext); return NUM; }
[a-zA-Z_]([a-zA-Z0-9_])*	{ yylval.str = strdup(yytext); return ID_OTHER; }

"="	{ yylval.str = strdup(yytext); return ASSIGN; }
"&&"	{ yylval.str = strdup(yytext); return OP_BI; }
"||"	{ yylval.str = strdup(yytext); return OP_BI; }
"=="	{ yylval.str = strdup(yytext); return OP_BI; }
"!="	{ yylval.str = strdup(yytext); return OP_BI; }
"<"	{ yylval.str = strdup(yytext); return OP_BI; }
">"	{ yylval.str = strdup(yytext); return OP_BI; }
"+"	{ yylval.str = strdup(yytext); return OP_BI; }
"-"	{ yylval.str = strdup(yytext); return OP_BI; }
"*"	{ yylval.str = strdup(yytext); return OP_BI; }
"/"	{ yylval.str = strdup(yytext); return OP_BI; }
"%"	{ yylval.str = strdup(yytext); return OP_BI; }
"!"	{ yylval.str = strdup(yytext); return OP_UNI; }

"("	{ yylval.val = lineno; return PRN_L; }
")"	{ yylval.val = lineno; return PRN_R; }
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
