%{
#include "op.h"
#include "tree.h"

extern char *yytext;
extern int yylex (void);
extern void yyerror(const char *);

#define YYSTYPE TreeNode*

TreeNode *gramma_root;
%}

%token INTEGER
%token AND OR EQ NE
%token LABEL VARIABLE FUNCTION
%token IF END VAR CALL GOTO PARAM RETURN

%%

gramma_fin   : gramma_gra {
				$$ = $1;
				gramma_root = $$;
			 }
			 ;

gramma_gra   : gramma_gra vardef_stm  {
				$$ = new StmNode(SEQUEN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $2;
				$$->child[1]->SetGlobal();
			 }
			 | gramma_gra fundef_stm  {
				$$ = new StmNode(SEQUEN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $2;
				$$->child[1]->SetGlobal();
			 }
			 | {
				$$ = NULL;
			 }
			 ;

vardef_stm   : VAR variid_stm {
				$$ = new StmNode(VARDEF_KIND);
				$$->child[0] = $2;
			 }
			 | VAR intege_stm variid_stm {
				$$ = new StmNode(ARRDEF_KIND);
				$$->child[0] = $2;
				$$->child[1] = $3;
			 }
			 ;

fundef_stm   : funcid_stm '[' intege_stm ']' sequen_stm END funcid_stm {
				$$ = new StmNode(FUNDEF_KIND);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->child[2] = $5;
			 }
			 ;

sequen_stm   : sequen_stm expres_stm {
				$$ = new StmNode(SEQUEN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $2;
			 }
			 | sequen_stm vardef_stm {
				$$ = new StmNode(SEQUEN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $2;
			 }
			 | {
				$$ = NULL;
			 }
			 ;

rvalue_stm   : variid_stm {
				$$ = $1;
			 }
			 | intege_stm {
				$$ = $1;
			 }
			 ;

expres_stm   : variid_stm '=' rvalue_stm '+' rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_ADD);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' rvalue_stm '-' rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_SUB);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' rvalue_stm '*' rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_MUL);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' rvalue_stm '/' rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_DIV);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' rvalue_stm '%' rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_MOD);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' rvalue_stm '>' rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_GT);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' rvalue_stm '<' rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_LT);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' rvalue_stm AND rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_AND);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' rvalue_stm OR  rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_OR);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' rvalue_stm EQ  rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_EQ);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' rvalue_stm NE  rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_NEQ);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '='            '-' rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper1ExpNode(OP_NEG);
				$$->child[1]->child[0] = $4;
			 }
			 | variid_stm '='            '!' rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper1ExpNode(OP_NOT);
				$$->child[1]->child[0] = $4;
			 }
			 | variid_stm '='                rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $3;
			 }
			 | variid_stm '=' CALL           funcid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new CallfExpNode($4->GetName());
				$$->child[1]->child[0] = $4;
			 }
			 | variid_stm '[' rvalue_stm ']' '=' rvalue_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = new ArrayExpNode($1->GetName());
				$$->child[0]->child[0] = $3;
				$$->child[1] = $6;
			 }
			 | variid_stm '=' variid_stm '[' rvalue_stm ']'{
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new ArrayExpNode($3->GetName());
				$$->child[1]->child[0] = $5;
			 }
			 |                              GOTO labeid_stm {
				$$ = new StmNode(GOTODO_KIND);
				$$->child[0] = $2;
			 }
			 | IF rvalue_stm '>' rvalue_stm GOTO labeid_stm {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_GT);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }
			 | IF rvalue_stm '<' rvalue_stm GOTO labeid_stm {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_LT);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }
			 | IF rvalue_stm EQ  rvalue_stm GOTO labeid_stm {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_EQ);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }

			 | IF rvalue_stm NE  rvalue_stm GOTO labeid_stm {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_NEQ);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }

			 | PARAM      rvalue_stm {
				$$ = new StmNode(PARAME_KIND);
				$$->child[0] = $2;
			 }
			 | RETURN     rvalue_stm {
				$$ = new StmNode(RETURN_KIND);
				$$->child[0] = $2;
			 }
			 | labeid_stm ':' {
				$$ = new StmNode(LABELT_KIND);
				$$->child[0] = $1;
			 }
			 ;

variid_stm   : VARIABLE {
				$$ = new VariaExpNode(string("L_") + yytext);
			 }
			 ;

labeid_stm   : LABEL {
				$$ = new LabelExpNode(yytext);
			 }
			 ;

funcid_stm   : FUNCTION {
				$$ = new FunctExpNode(yytext);
			 }
			 ;

intege_stm   : INTEGER {
				$$ = new IntegExpNode(yytext);
			 }
			 ;
