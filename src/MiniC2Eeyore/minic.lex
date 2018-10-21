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
[\n]+	{ lineno++; }

"int"	{ yylval.name = strdup(yytext); return TYPE; }
"main"	{ yylval.name = strdup(yytext); return MAIN; }
"if"	{ yylval.name = strdup(yytext); return IF; }
"else"	{ yylval.name = strdup(yytext); return ELSE; }
"while"	{ yylval.name = strdup(yytext); return WHILE; }
"return"			{ yylval.name = strdup(yytext); return RETURN; }
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

"("	{ return PRN_L; }
")"	{ return PRN_R; }
"["	{ return ARR_L; }
"]"	{ return ARR_R; }
"{"	{ return BRC_L; }
"}"	{ return BRC_R; }
","	{ return COMMA; }
";"	{ return EOL; }

. {
	yyerror("ERROR: Unrecognized input!");
}

%%

int yywrap()
{
	return 1;
}
