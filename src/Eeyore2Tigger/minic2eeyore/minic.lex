%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "y.tab.h"

void yyerror(char*);
int lineno = 1;
FILE* cheating_file;
%}

%%

[ \t]+
[\n]	{ fprintf(cheating_file, "\n"); lineno++; }

"int"	{ fprintf(cheating_file, "int "); yylval.name = strdup(yytext); return TYPE; }
"main"	{ fprintf(cheating_file, "main "); yylval.name = strdup(yytext); return MAIN; }
"if"	{ fprintf(cheating_file, "if "); yylval.name = strdup(yytext); return IF; }
"else"	{ fprintf(cheating_file, "else "); yylval.name = strdup(yytext); return ELSE; }
"while"	{ fprintf(cheating_file, "while "); yylval.name = strdup(yytext); return WHILE; }
"return"	{ fprintf(cheating_file, "return "); yylval.name = strdup(yytext); return RETURN; }
[a-zA-Z_]([a-zA-Z0-9_])*	{ fprintf(cheating_file, "%s ", yytext); yylval.name = strdup(yytext); return ID; }
[0-9]+	{ fprintf(cheating_file, "%s ", yytext); yylval.value = atoi(yytext); return NUM; }

"="	{ fprintf(cheating_file, "= "); yylval.name = strdup(yytext); return OP_7; }
"&&"	{ fprintf(cheating_file, "&& "); yylval.name = strdup(yytext); return OP_6; }
"||"	{ fprintf(cheating_file, "|| "); yylval.name = strdup(yytext); return OP_6; }
"=="	{ fprintf(cheating_file, "== "); yylval.name = strdup(yytext); return OP_5; }
"!="	{ fprintf(cheating_file, "!= "); yylval.name = strdup(yytext); return OP_5; }
"<"	{ fprintf(cheating_file, "< "); yylval.name = strdup(yytext); return OP_4; }
">"	{ fprintf(cheating_file, "> "); yylval.name = strdup(yytext); return OP_4; }
"+"	{ fprintf(cheating_file, "+ "); yylval.name = strdup(yytext); return OP_3; }
"-"	{ fprintf(cheating_file, "- "); yylval.name = strdup(yytext); return OP_3; }
"*"	{ fprintf(cheating_file, "* "); yylval.name = strdup(yytext); return OP_2; }
"/"	{ fprintf(cheating_file, "/ "); yylval.name = strdup(yytext); return OP_2; }
"%"	{ fprintf(cheating_file, "%s ", yytext); yylval.name = strdup(yytext); return OP_2; }
"!"	{ fprintf(cheating_file, "!"); yylval.name = strdup(yytext); return OP_1; }

"("	{ fprintf(cheating_file, "( "); yylval.value = lineno; return PRN_L; }
")"	{ fprintf(cheating_file, ") "); yylval.value = lineno; return PRN_R; }
"["	{ fprintf(cheating_file, "[ "); yylval.value = lineno; return ARR_L; }
"]"	{ fprintf(cheating_file, "] "); yylval.value = lineno; return ARR_R; }
"{"	{ fprintf(cheating_file, "{ "); yylval.value = lineno; return BRC_L; }
"}"	{ fprintf(cheating_file, "} "); yylval.value = lineno; return BRC_R; }
","	{ fprintf(cheating_file, ", "); yylval.value = lineno; return COMMA; }
";"	{ fprintf(cheating_file, "; "); yylval.value = lineno; return EOL; }

"//"[^\n]*	{ fprintf(cheating_file, "%s", yytext); }

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
