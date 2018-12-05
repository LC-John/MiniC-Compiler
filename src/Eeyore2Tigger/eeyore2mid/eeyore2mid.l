%{
#include "eeyore2mid.tab.h"
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

label      l{integer}
variable   [Ttp]{integer}
function   f_{identifier}

%%

{whitespace} { }

"if"         { return IF; }
"end"        { return END; }
"var"        { return VAR; }
"goto"       { return GOTO; }
"call"       { return CALL; }
"param"      { return PARAM; }
"return"     { return RETURN; }

{integer}    { return INTEGER; }

{label}      { return LABEL; }
{variable}   { return VARIABLE; }
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
