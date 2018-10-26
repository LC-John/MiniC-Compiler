%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "y.tab.h"

void yyerror(char*);
int lineno = 1;
%}

%%

[ \t]+
[\n]	{ lineno++; }

"int"	{ yylval.name = strdup(yytext); return TYPE; }
"main"	{ yylval.name = strdup(yytext); return MAIN; }
"if"	{ yylval.name = strdup(yytext); return IF; }
"else"	{ yylval.name = strdup(yytext); return ELSE; }
"while"	{ yylval.name = strdup(yytext); return WHILE; }
"return"	{ yylval.name = strdup(yytext); return RETURN; }
[a-zA-Z_]([a-zA-Z0-9_])*	{ yylval.name = strdup(yytext); return ID; }
[0-9]+	{ yylval.value = atoi(yytext); return NUM; }

"="	{ yylval.name = strdup(yytext); return OP_7; }
"&&"	{ yylval.name = strdup(yytext); return OP_6; }
"||"	{ yylval.name = strdup(yytext); return OP_6; }
"=="	{ yylval.name = strdup(yytext); return OP_5; }
"!="	{ yylval.name = strdup(yytext); return OP_5; }
"<"	{ yylval.name = strdup(yytext); return OP_4; }
">"	{ yylval.name = strdup(yytext); return OP_4; }
"+"	{ yylval.name = strdup(yytext); return OP_3; }
"-"	{ yylval.name = strdup(yytext); return OP_3; }
"*"	{ yylval.name = strdup(yytext); return OP_2; }
"/"	{ yylval.name = strdup(yytext); return OP_2; }
"%"	{ yylval.name = strdup(yytext); return OP_2; }
"!"	{ yylval.name = strdup(yytext); return OP_1; }

"("	{ yylval.value = lineno; return PRN_L; }
")"	{ yylval.value = lineno; return PRN_R; }
"["	{ yylval.value = lineno; return ARR_L; }
"]"	{ yylval.value = lineno; return ARR_R; }
"{"	{ yylval.value = lineno; return BRC_L; }
"}"	{ yylval.value = lineno; return BRC_R; }
","	{ yylval.value = lineno; return COMMA; }
";"	{ yylval.value = lineno; return EOL; }

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
