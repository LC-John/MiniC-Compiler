%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tree.h"
#include "symtab.h"

int yylex(void);
void yyerror(char*);

extern FILE* yyin;
extern int lineno;
struct TreeNode* root;
%}

%union {
	int value;
	char* name;
	struct TreeNode* node;
};

%token <name> MAIN IF ELSE WHILE RETURN
%token <value> PRN_R ARR_L ARR_R BRC_R COMMA EOL PRN_L BRC_L
%token <value> NUM
%token <name> ID TYPE

%type <node> Goal BeforeMain MainFunc FuncDefn FuncDecl ParamDeclList
%type <node> VarDefn VarDecl FuncDeclStmtList StmtList Stmt Expr ParamList
%type <node> Type Integer Identifier

%right <name> OP_7
%left <name> OP_6
%left <name> OP_5
%left <name> OP_4
%left <name> OP_3
%left <name> OP_2
%right <name> OP_1

%%

Goal	: BeforeMain MainFunc {
		struct TreeNode* tmp_node;
		$$ = alloc_treenode(lineno, TN_ROOT, NULL);
		tmp_node = $1;
		while(tmp_node != NULL && tmp_node->sibling_l != NULL)
		{
			tmp_node->parent = $$; tmp_node->child_idx = 0;
			tmp_node = tmp_node->sibling_l;
		}
		$$->child[0] = tmp_node;
		if (tmp_node != NULL)
		{
			tmp_node->parent = $$;
			tmp_node->child_idx = 0;
		}
		$$->child[1] = $2; $2->parent = $$; $2->child_idx = 1;
		root = $$;
		set_death(0, lineno);
	}
	;

BeforeMain	: BeforeMain VarDefn {
		if ($1 != NULL)
			$1->sibling_r = $2;
		$2->sibling_l = $1;
		$$ = $2;
	}
	| BeforeMain FuncDefn {
		if ($1 != NULL)
			$1->sibling_r = $2;
		$2->sibling_l = $1;
		$$ = $2;
	}
	| BeforeMain FuncDecl {
		if ($1 != NULL)
			$1->sibling_r = $2;
		$2->sibling_l = $1;
		$$ = $2;
	}
	|  { $$ = NULL; }
	;

MainFunc	: Type MAIN PRN_L PRN_R BRC_L FuncDeclStmtList BRC_R {
		struct TreeNode* tmp_node = alloc_treenode($1->lineno, TN_IDENTIFIER, strdup("main"));
		$$ = alloc_treenode(lineno, TN_FUNCDEFN, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = tmp_node; tmp_node->parent = $$; tmp_node->child_idx = 1;
		$$->child[2] = NULL;
		tmp_node = $6;
		while(tmp_node != NULL && tmp_node->sibling_l != NULL)
		{
			tmp_node->parent = $$; tmp_node->child_idx = 3;
			tmp_node = tmp_node->sibling_l;
		}
		$$->child[3] = tmp_node;
		if (tmp_node != NULL)
		{
			tmp_node->parent = $$;
			tmp_node->child_idx = 3;
		}
		set_death($3, lineno);
		alloc_symbol($1->lineno, ST_FUNC, "main", $$);
	}
	;

FuncDefn	: Type Identifier PRN_L PRN_R BRC_L FuncDeclStmtList BRC_R {
		struct TreeNode* tmp_node;
		$$ = alloc_treenode($1->lineno, TN_FUNCDEFN, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $2; $2->parent = $$; $2->child_idx = 1;
		$$->child[2] = NULL;
		tmp_node = $6;
		while(tmp_node != NULL && tmp_node->sibling_l != NULL)
		{
			tmp_node->parent = $$; tmp_node->child_idx = 3;
			tmp_node = tmp_node->sibling_l;
		}
		$$->child[3] = tmp_node;
		if (tmp_node != NULL)
		{
			tmp_node->parent = $$;
			tmp_node->child_idx = 3;
		}
		set_death($3, lineno);
		alloc_symbol($1->lineno, ST_FUNC, $2->name, $$);
	}
	| Type Identifier PRN_L ParamDeclList PRN_R BRC_L FuncDeclStmtList BRC_R {
		struct TreeNode* tmp_node;
		$$ = alloc_treenode($1->lineno, TN_FUNCDEFN, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $2; $2->parent = $$; $2->child_idx = 1;
		tmp_node = $4;
		while(tmp_node->sibling_l != NULL)
		{
			tmp_node->parent = $$; tmp_node->child_idx = 2;
			tmp_node = tmp_node->sibling_l;
		}
		$$->child[2] = tmp_node; tmp_node->parent = $$; tmp_node->child_idx = 2;
		tmp_node = $7;
		while(tmp_node != NULL && tmp_node->sibling_l != NULL)
		{
			tmp_node->parent = $$; tmp_node->child_idx = 3;
			tmp_node = tmp_node->sibling_l;
		}
		$$->child[3] = tmp_node;
		if (tmp_node != NULL)
		{
			tmp_node->parent = $$;
			tmp_node->child_idx = 3;
		}
		set_death($3, lineno);
		alloc_symbol($1->lineno, ST_FUNC, $2->name, $$);
	}
	;

FuncDecl	: Type Identifier PRN_L PRN_R EOL {
		$$ = alloc_treenode(lineno, TN_FUNCDECL, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $2; $2->parent = $$; $2->child_idx = 1;
		$$->child[2] = NULL;
		if (strcmp($1->name, "int") == 0
		    && (strcmp($2->name, "getint") == 0 || strcmp($2->name, "getchar") == 0))
			alloc_symbol($1->lineno, ST_FUNC, $2->name, $$);
	}
	| Type Identifier PRN_L ParamDeclList PRN_R EOL {
		struct TreeNode* tmp_node;
		$$ = alloc_treenode(lineno, TN_FUNCDECL, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $2; $2->parent = $$; $2->child_idx = 1;
		tmp_node = $4;
		while(tmp_node->sibling_l != NULL)
		{
			tmp_node->parent = $$; tmp_node->child_idx = 2;
			tmp_node = tmp_node->sibling_l;
		}
		$$->child[2] = tmp_node; tmp_node->parent = $$; tmp_node->child_idx = 2;
		if (strcmp($1->name, "int") == 0
		    && (strcmp($2->name, "putint") == 0 || strcmp($2->name, "putchar") == 0)
		    && (strcmp($4->child[0]->name, "int") == 0 && $4->child[2] == NULL)
		    && $4->sibling_r == NULL)
		{
			set_death($3, lineno);
			alloc_symbol($1->lineno, ST_FUNC, $2->name, $$);
		}
		else
			purge_var($3, lineno);
	}
	;

ParamDeclList	: VarDecl	{ $$ = $1; }
	| ParamDeclList COMMA VarDecl {
		$1->sibling_r = $3;
		$3->sibling_l = $1;
		$$ = $3;
	}
	;

FuncDeclStmtList	: FuncDeclStmtList Stmt	{
		if ($1 != NULL)
			$1->sibling_r = $2;
		$2->sibling_l = $1;
		$$ = $2;
	}
	| FuncDeclStmtList FuncDecl {
		if ($1 != NULL)
			$1->sibling_r = $2;
		$2->sibling_l = $1;
		$$ = $2;
	}
	|  { $$ = NULL; }
	;

VarDefn	: Type Identifier EOL {
		$$ = alloc_treenode(lineno, TN_VARDEFN, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $2; $2->parent = $$; $2->child_idx = 1;
		$$->child[2] = NULL;
		alloc_symbol($1->lineno, ST_INT, $2->name, $$);
	}
	| Type Identifier ARR_L Integer ARR_R EOL {
		$$ = alloc_treenode(lineno, TN_VARDEFN, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $2; $2->parent = $$; $2->child_idx = 1;
		$$->child[2] = $4; $4->parent = $$; $4->child_idx = 2;
		alloc_symbol($1->lineno, ST_ARR, $2->name, $$);
	}
	;

VarDecl	: Type Identifier {
		$$ = alloc_treenode(lineno, TN_VARDECL, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $2; $2->parent = $$; $2->child_idx = 1;
		$$->child[2] = NULL;
		alloc_symbol($1->lineno, ST_INT, $2->name, $$);
	}
	| Type Identifier ARR_L Integer ARR_R {
		$$ = alloc_treenode(lineno, TN_VARDECL, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $2; $2->parent = $$; $2->child_idx = 1;
		$$->child[2] = $4; $4->parent = $$; $4->child_idx = 2;
		alloc_symbol($1->lineno, ST_ARR, $2->name, $$);
	}
	;

Stmt	: BRC_L StmtList BRC_R {
		struct TreeNode* tmp_node;
		$$ = alloc_treenode(lineno, TN_STMT_BLOCK, NULL);
		tmp_node = $2;
		while(tmp_node != NULL && tmp_node->sibling_l != NULL)
		{
			tmp_node->parent = $$; tmp_node->child_idx = 1;
			tmp_node = tmp_node->sibling_l;
		}
		$$->child[0] = tmp_node;
		if (tmp_node != NULL)
		{
			tmp_node->parent = $$;
			tmp_node->child_idx = 0;
		}
		set_death($1, lineno);
	}
	| IF PRN_L Expr PRN_R Stmt {
		$$ = alloc_treenode(lineno, TN_STMT_IF, NULL);
		$$->child[0] = $3; $3->parent = $$; $3->child_idx = 0;
		$$->child[1] = $5; $5->parent = $$; $5->child_idx = 1;
		$$->child[2] = NULL;
		set_death($2, lineno);
	}
	| IF PRN_L Expr PRN_R Stmt ELSE Stmt {
		$$ = alloc_treenode(lineno, TN_STMT_IF, NULL);
		$$->child[0] = $3; $3->parent = $$; $3->child_idx = 0;
		$$->child[1] = $5; $5->parent = $$; $5->child_idx = 1;
		$$->child[2] = $7; $7->parent = $$; $7->child_idx = 2;
		set_death($2, $7->lineno-1);
		set_death($7->lineno, lineno);
	}
	| WHILE PRN_L Expr PRN_R Stmt {
		$$ = alloc_treenode(lineno, TN_STMT_WHILE, NULL);
		$$->child[0] = $3; $3->parent = $$; $3->child_idx = 0;
		$$->child[1] = $5; $5->parent = $$; $5->child_idx = 1;
		set_death($2, lineno);
	}
	| Identifier OP_7 Expr EOL {
		$$ = alloc_treenode(lineno, TN_STMT_VARASSN, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
	}
	| Identifier ARR_L Expr ARR_R OP_7 Expr EOL {
		$$ = alloc_treenode(lineno, TN_STMT_ARRASSN, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
		$$->child[2] = $6; $6->parent = $$; $6->child_idx = 2;
	}
	| VarDefn {
		$$ = alloc_treenode(lineno, TN_STMT_VARDEFN, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
	}
	| RETURN Expr EOL {
		$$ = alloc_treenode(lineno, TN_STMT_RETURN, NULL);
		$$->child[0] = $2; $2->parent = $$; $2->child_idx = 0;
	}
	;

StmtList	: StmtList Stmt	{
		if ($1 != NULL)
			$1->sibling_r = $2;
		$2->sibling_l = $1;
		$$ = $2;
	}
	|  { $$ = NULL; }
	;

Expr	: Expr OP_6 Expr {
		$$ = alloc_treenode(lineno, TN_EXPR_BILOGIC, strdup($2));
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
	}
	| Expr OP_5 Expr {
		$$ = alloc_treenode(lineno, TN_EXPR_BILOGIC, strdup($2));
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
	}
	| Expr OP_4 Expr {
		$$ = alloc_treenode(lineno, TN_EXPR_BILOGIC, strdup($2));
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
	}
	| Expr OP_3 Expr {
		$$ = alloc_treenode(lineno, TN_EXPR_BIARITH, strdup($2));
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
	}
	| Expr OP_2 Expr {
		$$ = alloc_treenode(lineno, TN_EXPR_BIARITH, strdup($2));
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
	}
	| Expr ARR_L Expr ARR_R {
		$$ = alloc_treenode(lineno, TN_EXPR_ARR, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
	}
	| Integer {
		$$ = alloc_treenode(lineno, TN_EXPR_INTEGER, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
	}
	| Identifier {
		$$ = alloc_treenode(lineno, TN_EXPR_IDENTIFIER, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
	}
	| OP_3 Expr {
		$$ = alloc_treenode(lineno, TN_EXPR_UNI, strdup($1));
		$$->child[0] = $2; $2->parent = $$; $2->child_idx = 0;
	}
	| OP_1 Expr {
		$$ = alloc_treenode(lineno, TN_EXPR_UNI, strdup($1));
		$$->child[0] = $2; $2->parent = $$; $2->child_idx = 0;
	}
	| Identifier PRN_L PRN_R {
		$$ = alloc_treenode(lineno, TN_EXPR_CALL, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = NULL;
	}
	| Identifier PRN_L ParamList PRN_R {
		struct TreeNode *tmp_node;
		$$ = alloc_treenode(lineno, TN_EXPR_CALL, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		tmp_node = $3;
		while(tmp_node->sibling_l != NULL)
		{
			tmp_node->parent = $$; tmp_node->child_idx = 1;
			tmp_node = tmp_node->sibling_l;
		}
		$$->child[1] = tmp_node; tmp_node->parent = $$; tmp_node->child_idx = 1;
	}
	| PRN_L Expr PRN_R { $$ = $2; }
	;

ParamList	: Identifier { $$ = $1; }
	| ParamList COMMA Identifier {
		$1->sibling_r = $3;
		$3->sibling_l = $1;
		$$ = $3;
	}
	;

Type	: TYPE { $$ = alloc_treenode(lineno, TN_TYPE, strdup($1)); }
	;

Integer	: NUM {
		$$ = alloc_treenode(lineno, TN_INTEGER, NULL);
		$$->val = $1;
	}
	;

Identifier	: ID { $$ = alloc_treenode(lineno, TN_IDENTIFIER, strdup($1)); }
	;

%%

void yyerror(char* s)
{
	fprintf(stderr, ">> ERR@L%d: %s\n", lineno, s);
}

int main(int argc, char** argv)
{
	if (argc < 2)
		return -1;
	yyin = fopen(argv[1], "r");
	if (yyin == NULL)
	{
		printf("Cannot open file: %s\nPlease check if it is valid\n", argv[1]);
		return -1;
	}
	for (int i = 2; i < argc; i++)
	{
		if (strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "--tree") == 0)
			continue;
		if (strcmp(argv[i], "-S") == 0 || strcmp(argv[i], "--symtab") == 0)
			continue;
		printf("Unknown option: %s", argv[i]);
		return -2;
	}
	init_tree();
	init_symtab();
	yyparse();
	for (int i = 2; i < argc; i++)
	{
		if (strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "--tree") == 0)
		{
			printf("\nMiniC parse tree of %s\n", argv[1]);
			print_tree(root, 0);
		}
		if (strcmp(argv[i], "-S") == 0 || strcmp(argv[i], "--symtab") == 0)
		{
			printf("\nSymbol table of %s\n", argv[1]);
			print_symtab();
		}
	}
	return 0;
}
