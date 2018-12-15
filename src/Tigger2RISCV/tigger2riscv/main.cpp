extern "C" {
	#include "y.tab.h"
}

#include <cstdio>

extern FILE* yyin;
extern FILE* yyout;

int main(int argc, char** argv)
{
	yyparse();
	return 0;
}
