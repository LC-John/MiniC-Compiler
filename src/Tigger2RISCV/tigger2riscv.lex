%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "y.tab.h"

void yyerror(char*);
int lineno = 1;
%}

%%

[ \t]+	{ }
[\n]	{ lineno++; return EOL; }


"["	{ return ARR_L; }
"]"	{ return ARR_R; }

"malloc"	{ return MALLOC; }
"if"		{ return IF; }
"goto"		{ return GOTO; }
"call"		{ return CALL; }
"store"		{ return STORE; }
"load"		{ return LOAD; }
"loadaddr"	{ return LOADADDR; }
"return"	{ return RETURN; }
"end"		{ return END; }
":"		{ return COLON; }

"="	{ return ASSIGN; }
"+"	{ yylval.str = strdup(yytext); return OP; }
"-"	{ yylval.str = strdup(yytext); return OP; }
"*"	{ yylval.str = strdup(yytext); return OP; }
"/"	{ yylval.str = strdup(yytext); return OP; }
"%"	{ yylval.str = strdup(yytext); return OP; }
"&&"	{ yylval.str = strdup(yytext); return OP; }
"||"	{ yylval.str = strdup(yytext); return OP; }
"=="	{ yylval.str = strdup(yytext); return OP; }
"!="	{ yylval.str = strdup(yytext); return OP; }
"<"	{ yylval.str = strdup(yytext); return OP; }
">"	{ yylval.str = strdup(yytext); return OP; }
"!"	{ yylval.str = strdup(yytext); return OP; }

"x0"		{ yylval.str = strdup(yytext); return REG; }
"s"[0-9]	{ yylval.str = strdup(yytext); return REG; }
"s1"[0-1]	{ yylval.str = strdup(yytext); return REG; }
"a"[0-7]	{ yylval.str = strdup(yytext); return REG; }
"t"[0-6]	{ yylval.str = strdup(yytext); return REG; }

"l"[0-9]*		{ yylval.str = strdup(yytext); return LABEL; }
"f_"[0-9a-zA-Z]*	{ yylval.str = strdup(yytext); return FUNC; }
"v"[0-9]*		{ yylval.str = strdup(yytext); return VAR; }
[0-9]+			{ yylval.val = atoi(yytext); return INT; }

"//"[^\n]*	{ }

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
