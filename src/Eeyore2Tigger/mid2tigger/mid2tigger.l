%{
#include "mid2tigger.tab.h"
#include "tree.h"

void yyecho() {
	cerr << yytext;
}
%}

delim      [ \t\n]
whitespace {delim}+

digit      [0-9]
integer    {digit}+

letter     [A-Za-z]
identifier {letter}({letter}|{digit})*

regisvar   R_[sat]{integer}
globavar   v{integer}
localvar   L_[Ttpe]{integer}

label      l{integer}
function   f_{identifier}

%%

{whitespace} { }

"if"         { return IF; }
"end"        { return END; }
"goto"       { return GOTO; }
"call"       { return CALL; }
"return"     { return RETURN; }

"push"       { return PUSH; }
"store"      { return STORE; }
"load"       { return LOAD; }
"malloc"     { return MALLOC; }
"loadaddr"   { return LOADADDR; }

{integer}    { return INTEGER; }

{regisvar}   { return REGVAR; }
{globavar}   { return GLOVAR; }
{localvar}   { return LOCVAR; }

{label}      { return LABEL; }
{function}   { return FUNCTION; }

"&&"         { return AND; }
"||"         { return OR; }
"=="         { return EQ; }
"!="         { return NE; }

[\+\-\*\/\%\<\>\=\[\]\:\!] { return *yytext; }

"//"[^\n]*	{ }
.            { }

%%

int yywrap() {
        return 1;
}

void yyerror(const char *msg) {
}
