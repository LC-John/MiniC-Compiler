%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int yylex(void);
void yyerror(char*);

extern FILE* yyin;
extern FILE* yyout;
extern int lineno;
struct TreeNode* root;
char *infile_path, *outfile_path;
FILE* cheating_file;
%}

%union {
	int val;
	char* str;
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
		if ($6 == NULL)
			alloc_ew(WARN_NO_RETURN, $$, NULL, NULL);
		else
		{
			for (tmp_node = $6; tmp_node->sibling_r != NULL;
				tmp_node = tmp_node->sibling_r);
			if (tmp_node->type != TN_STMT_RETURN)
				alloc_ew(WARN_NO_RETURN, $$, NULL, NULL);
		}
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
		if ($6 == NULL)
			alloc_ew(WARN_NO_RETURN, $$, NULL, NULL);
		else
		{
			for (tmp_node = $6; tmp_node->sibling_r != NULL;
				tmp_node = tmp_node->sibling_r);
			if (tmp_node->type != TN_STMT_RETURN)
				alloc_ew(WARN_NO_RETURN, $$, NULL, NULL);
		}
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
		if ($7 == NULL)
			alloc_ew(WARN_NO_RETURN, $$, NULL, NULL);
		else
		{
			for (tmp_node = $7; tmp_node->sibling_r != NULL;
				tmp_node = tmp_node->sibling_r);
			if (tmp_node->type != TN_STMT_RETURN)
				alloc_ew(WARN_NO_RETURN, $$, NULL, NULL);
		}
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
		alloc_ew(WARN_FUNCDECL_IN_BODY, $2, NULL, NULL);
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
		if ($3->type != TN_EXPR_BILOGIC
			&& !($3->type == TN_EXPR_UNI && strcmp($3->name, "!") == 0))
		{
			alloc_ew(ERR_WRONG_EXPR, $3, NULL, NULL);
			print_ew();
		}
	}
	| IF PRN_L Expr PRN_R Stmt ELSE Stmt {
		$$ = alloc_treenode(lineno, TN_STMT_IF, NULL);
		$$->child[0] = $3; $3->parent = $$; $3->child_idx = 0;
		$$->child[1] = $5; $5->parent = $$; $5->child_idx = 1;
		$$->child[2] = $7; $7->parent = $$; $7->child_idx = 2;
		set_death($2, $7->lineno-1);
		set_death($7->lineno, lineno);
		if ($3->type != TN_EXPR_BILOGIC
			&& !($3->type == TN_EXPR_UNI && strcmp($3->name, "!") == 0))
		{
			alloc_ew(ERR_WRONG_EXPR, $3, NULL, NULL);
			print_ew();
		}
	}
	| WHILE PRN_L Expr PRN_R Stmt {
		$$ = alloc_treenode(lineno, TN_STMT_WHILE, NULL);
		$$->child[0] = $3; $3->parent = $$; $3->child_idx = 0;
		$$->child[1] = $5; $5->parent = $$; $5->child_idx = 1;
		set_death($2, lineno);
		if ($3->type != TN_EXPR_BILOGIC
			&& !($3->type == TN_EXPR_UNI && strcmp($3->name, "!") == 0))
		{
			alloc_ew(ERR_WRONG_EXPR, $3, NULL, NULL);
			print_ew();
		}
	}
	| Identifier OP_7 Expr EOL {
		$$ = alloc_treenode(lineno, TN_STMT_VARASSN, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
		if ($3->type == TN_EXPR_BILOGIC
			|| ($3->type == TN_EXPR_UNI && strcmp($3->name, "!") == 0))
			alloc_ew(WARN_MIXED_EXPR, $3, NULL, NULL);
		if (find_var(ST_INT, $1) == 0)
			print_ew();
	}
	| Identifier ARR_L Expr ARR_R OP_7 Expr EOL {
		$$ = alloc_treenode(lineno, TN_STMT_ARRASSN, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
		$$->child[2] = $6; $6->parent = $$; $6->child_idx = 2;
		if ($3->type == TN_EXPR_BILOGIC
			|| ($3->type == TN_EXPR_UNI && strcmp($3->name, "!") == 0))
			alloc_ew(WARN_MIXED_EXPR, $3, NULL, NULL);
		if ($6->type == TN_EXPR_BILOGIC
			|| ($6->type == TN_EXPR_UNI && strcmp($6->name, "!") == 0))
			alloc_ew(WARN_MIXED_EXPR, $6, NULL, NULL);
		if (find_var(ST_ARR, $1) == 0)
			print_ew();
	}
	| VarDefn {
		$$ = alloc_treenode(lineno, TN_STMT_VARDEFN, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
	}
	| RETURN Expr EOL {
		$$ = alloc_treenode(lineno, TN_STMT_RETURN, NULL);
		$$->child[0] = $2; $2->parent = $$; $2->child_idx = 0;
		if ($2->type == TN_EXPR_BILOGIC
			|| ($2->type == TN_EXPR_UNI && strcmp($2->name, "!") == 0))
			alloc_ew(WARN_MIXED_EXPR, $2, NULL, NULL);
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
		if (($1->type != TN_EXPR_BILOGIC && $1->type != TN_EXPR_UNI
				&& ($1->type == TN_EXPR_UNI && strcmp($1->name, "!") != 0))
			|| ($3->type != TN_EXPR_BILOGIC && $3->type != TN_EXPR_UNI
				&& ($3->type == TN_EXPR_UNI && strcmp($3->name, "!") != 0)))
			alloc_ew(WARN_MIXED_EXPR, $$, NULL, NULL);
	}
	| Expr OP_5 Expr {
		$$ = alloc_treenode(lineno, TN_EXPR_BILOGIC, strdup($2));
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
		if ($1->type == TN_EXPR_BILOGIC
				|| ($1->type == TN_EXPR_UNI && strcmp($1->name, "!") == 0)
			|| $3->type == TN_EXPR_BILOGIC
				|| ($3->type == TN_EXPR_UNI && strcmp($3->name, "!") == 0))
			alloc_ew(WARN_MIXED_EXPR, $$, NULL, NULL);
	}
	| Expr OP_4 Expr {
		$$ = alloc_treenode(lineno, TN_EXPR_BILOGIC, strdup($2));
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
		if ($1->type == TN_EXPR_BILOGIC
				|| ($1->type == TN_EXPR_UNI && strcmp($1->name, "!") == 0)
			|| $3->type == TN_EXPR_BILOGIC
				|| ($3->type == TN_EXPR_UNI && strcmp($3->name, "!") == 0))
			alloc_ew(WARN_MIXED_EXPR, $$, NULL, NULL);
	}
	| Expr OP_3 Expr {
		$$ = alloc_treenode(lineno, TN_EXPR_BIARITH, strdup($2));
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
		if ($1->type == TN_EXPR_BILOGIC
				|| ($1->type == TN_EXPR_UNI && strcmp($1->name, "!") == 0)
			|| $3->type == TN_EXPR_BILOGIC
				|| ($3->type == TN_EXPR_UNI && strcmp($3->name, "!") == 0))
			alloc_ew(WARN_MIXED_EXPR, $$, NULL, NULL);
	}
	| Expr OP_2 Expr {
		$$ = alloc_treenode(lineno, TN_EXPR_BIARITH, strdup($2));
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
		if ($1->type == TN_EXPR_BILOGIC
				|| ($1->type == TN_EXPR_UNI && strcmp($1->name, "!") == 0)
			|| $3->type == TN_EXPR_BILOGIC
				|| ($3->type == TN_EXPR_UNI && strcmp($3->name, "!") == 0))
			alloc_ew(WARN_MIXED_EXPR, $$, NULL, NULL);
	}
	| Identifier ARR_L Expr ARR_R {
		$$ = alloc_treenode(lineno, TN_EXPR_ARR, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		$$->child[1] = $3; $3->parent = $$; $3->child_idx = 1;
		if ($3->type == TN_EXPR_BILOGIC
				|| ($3->type == TN_EXPR_UNI && strcmp($3->name, "!") == 0))
			alloc_ew(WARN_MIXED_EXPR, $3, NULL, NULL);
		if (find_var(ST_ARR, $1))
			print_ew();
	}
	| Integer {
		$$ = alloc_treenode(lineno, TN_EXPR_INTEGER, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
	}
	| Identifier {
		$$ = alloc_treenode(lineno, TN_EXPR_IDENTIFIER, NULL);
		$$->child[0] = $1; $1->parent = $$; $1->child_idx = 0;
		if (find_var(ST_INT, $1) == 0)
			print_ew();
	}
	| OP_3 Expr {
		$$ = alloc_treenode(lineno, TN_EXPR_UNI, strdup($1));
		$$->child[0] = $2; $2->parent = $$; $2->child_idx = 0;
		if ($2->type == TN_EXPR_BILOGIC
			|| ($2->type == TN_EXPR_UNI && strcmp($2->name, "!") == 0))
			alloc_ew(WARN_MIXED_EXPR, $$, NULL, NULL);
	}
	| OP_1 Expr {
		$$ = alloc_treenode(lineno, TN_EXPR_UNI, strdup($1));
		$$->child[0] = $2; $2->parent = $$; $2->child_idx = 0;
		if ($2->type != TN_EXPR_BILOGIC && $2->type != TN_EXPR_UNI
			&& ($2->type == TN_EXPR_UNI && strcmp($2->name, "!") != 0))
			alloc_ew(WARN_MIXED_EXPR, $$, NULL, NULL);
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
	fprintf(stderr, ">> ERROR@L%d: %s\n", lineno, s);
	exit(-3);
}

int main(int argc, char** argv)
{
	cheating_file = stderr;
	infile_path = NULL;
	outfile_path = NULL;
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
		if (strcmp(argv[i], "--cheatingfile") == 0 || strcmp(argv[i], "--cheating") == 0
			|| strcmp(argv[i], "-C") == 0)
		{
			if (i + 1 >= argc)
			{
				printf("No cheating file\n");
				return -1;
			}
			cheating_file = fopen(argv[i+1], "w");
			if (cheating_file == NULL)
			{
				printf("Cannot open file: %s\nPlease check if it is valid\n",
					argv[i+1]);
				return -1;
			}
			i++;
			continue;
		}
		printf("Unknown option: %s\n", argv[i]);
		return -2;
	}
	init_tree();
	init_symtab();
	init_ew();
	init_trans();
	yyparse();
	find_wrong_call(root);
	find_conflict();
	print_ew();
	minic2eeyore(root, "");
	for (int i = 2; i < argc; i++)
	{
		if (strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "--tree") == 0)
		{
			if (infile_path != NULL)
				printf("\nMiniC parse tree of %s\n", infile_path);
			else
				printf("\nMiniC parse tree\n");
			print_tree(root, 0, stdout);
		}
		if (strcmp(argv[i], "-S") == 0 || strcmp(argv[i], "--symtab") == 0)
		{
			if (infile_path != NULL)
				printf("\nSymbol table of %s\n", infile_path);
			else
				printf("\nSymbol table\n");
			print_symtab(stdout);
		}
	}
	fclose(yyin);
	fclose(yyout);
	return 0;
}
