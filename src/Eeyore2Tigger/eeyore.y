%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tree.h"

int yylex(void);
void yyerror(char*);

extern FILE* yyin;
extern FILE* yyout;
extern int lineno;
extern char* yytext;
%}

%union {
	int val;
	char* str;
	struct TreeNode* node;
};

%token <str>	EOL  VAR  END  IF  GOTO  PARAM  CALL  RETURN
%token <val>	ID_TMP  ID_PARAM  ID_NATIVE  ID_LABEL  NUM
%token <str>	ID_FUNC
%token <str>	ASSIGN  OP_BI_LOGIC  OP_BI_ARITH  OP_UNI
%token <str>	ARR_L  ARR_R  COLON

%type <node>	Goal  FuncVarDefnList
%type <node>	FuncDefn  VarDefn  ExprList
%type <node>	Expr  RVal
%type <node>	Integer  Label  Func  Var

%%

Goal	: FuncVarDefnList
	;

FuncVarDefnList	: 
	| EOL FuncVarDefnList
	| VarDefn EOL FuncVarDefnList
	| FuncDefn FuncVarDefnList
	;

FuncDefn	: Func ARR_L Integer ARR_R EOL ExprList END Func
	;

ExprList	:
	| EOL ExprList
	| VarDefn EOL ExprList
	| Expr EOL ExprList
	;

Expr	: Var ASSIGN RVal OP_BI_LOGIC RVal
	| Var ASSIGN RVal OP_BI_ARITH RVal
	| Var ASSIGN OP_BI_ARITH RVal
	| Var ASSIGN OP_UNI RVal
	| Var ASSIGN RVal
	| Var ARR_L RVal ARR_R ASSIGN RVal
	| Var ASSIGN Var ARR_L RVal ARR_R
	| IF RVal OP_BI_LOGIC RVal GOTO Label
	| GOTO Label
	| Label COLON
	| PARAM RVal
	| Var ASSIGN CALL Func
	| RETURN RVal
	;

RVal	: Var
	| Integer
	;

VarDefn	: VAR Var
	| VAR Integer Var
	;

Integer	: NUM
	;

Label	: ID_LABEL
	;

Func	: ID_FUNC
	;

Var	: ID_TMP
	| ID_PARAM
	| ID_NATIVE
	;

%%

void yyerror(char* s)
{
	fprintf(stderr, ">> ERROR@L%d: %s\n", lineno, s);
	exit(-3);
}

int main(int argc, char** argv)
{
	char *infile_path = NULL, *outfile_path = NULL;
	lineno = 1;
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "--tree") == 0)
			continue;
		if (strcmp(argv[i], "-S") == 0 || strcmp(argv[i], "--symtab") == 0)
			continue;
		if (strcmp(argv[i], "--infile") == 0 || strcmp(argv[i], "--input") == 0
			|| strcmp(argv[i], "-I") == 0)
		{
			if (i + 1 >= argc)
			{
				printf("No input file\n");
				return -1;
			}
			yyin = fopen(argv[i+1], "r");
			if (yyin == NULL)
			{
				printf("Cannot open file: %s\nPlease check if it is valid\n",
					argv[i+1]);
				return -1;
			}
			i++;
			infile_path = argv[i];
			continue;
		}
		if (strcmp(argv[i], "--outfile") == 0 || strcmp(argv[i], "--output") == 0
			|| strcmp(argv[i], "-O") == 0)
		{
			if (i + 1 >= argc)
			{
				printf("No output file\n");
				return -1;
			}
			yyout = fopen(argv[i+1], "w");
			if (yyout == NULL)
			{
				printf("Cannot open file: %s\nPlease check if it is valid\n",
					argv[i+1]);
				return -1;
			}
			i++;
			outfile_path = argv[i];
			continue;
		}
		printf("Unknown option: %s\n", argv[i]);
		return -2;
	}

	yyparse();

	if (yyin != stdin)
		fclose(yyin);
	if (yyout != stdout)
		fclose(yyout);
	return 0;
}
