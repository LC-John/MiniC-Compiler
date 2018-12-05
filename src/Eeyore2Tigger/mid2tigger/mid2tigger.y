%{
#include "op.h"
#include "tree.h"

extern char *yytext;
extern int yylex (void);
extern void yyerror(const char *);

#define YYSTYPE TreeNode*

TreeNode *gramma_root;
vector<TreeNode *> gramma_sequence;
vector<TreeNode *> worklist_sequence;
%}

%token INTEGER
%token AND OR EQ NE
%token REGVAR GLOVAR LOCVAR LABEL FUNCTION
%token IF END CALL GOTO RETURN
%token MALLOC PUSH STORE LOAD LOADADDR

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
			 }
			 | gramma_gra fundef_stm  {
				$$ = new StmNode(SEQUEN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $2;
			 }
			 | {
				$$ = NULL;
			 }
			 ;

vardef_stm   : glovar_stm '=' intege_stm {
				$$ = new StmNode(VARDEF_KIND);
				$$->child[0] = $1;
			 }
			 | glovar_stm '=' MALLOC intege_stm {
				$$ = new StmNode(ARRDEF_KIND);
				$$->child[0] = $1;
				$$->child[1] = $4;
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
				gramma_sequence.push_back($$->child[1]);
				worklist_sequence.push_back($$->child[1]);
			 }
			 | {
				$$ = NULL;
			 }
			 ;

variid_stm   : regvar_stm {
				$$ = $1;
			 }
			 | locvar_stm {
				$$ = $1;
			 }
			 | intege_stm {
				$$ = $1;
			 }
			 ;

expres_stm   : variid_stm '=' variid_stm '+' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_ADD);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm '-' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_MIN);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm '*' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_MUL);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm '/' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_DIV);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm '%' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_MOD);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm '>' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_GRT);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm '<' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_LET);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm AND variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_AND);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm OR  variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_ORT);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm EQ  variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_EQT);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm NE  variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_NET);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '='            '-' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper1ExpNode(OP_NEG);
				$$->child[1]->child[0] = $4;
			 }
			 | variid_stm '='            '!' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper1ExpNode(OP_NOT);
				$$->child[1]->child[0] = $4;
			 }
			 | variid_stm '='                variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $3;
			 }
			 | variid_stm '[' variid_stm ']' '=' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = new ArrayExpNode($1->GetName());
				$$->child[0]->child[0] = $3;
				$$->child[1] = $6;
			 }
			 | variid_stm '=' variid_stm '[' variid_stm ']'{
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new ArrayExpNode($3->GetName());
				$$->child[1]->child[0] = $5;
			 }
			 |                              GOTO labeid_stm {
				$$ = new StmNode(GOTODO_KIND);
				$$->child[0] = $2;
			 }
			 | IF variid_stm '>' variid_stm GOTO labeid_stm {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_GRT);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }
			 | IF variid_stm '<' variid_stm GOTO labeid_stm {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_LET);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }
			 | IF variid_stm EQ  variid_stm GOTO labeid_stm {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_EQT);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }
			 | IF variid_stm NE  variid_stm GOTO labeid_stm {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_NET);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }
			 | labeid_stm ':' {
				$$ = new StmNode(LABELT_KIND);
				$$->child[0] = $1;
			 }
			 | CALL funcid_stm {
				$$ = new StmNode(CALLFU_KIND);
				$$->child[0] = $2;
			 }
			 | RETURN {
				$$ = new StmNode(RETURN_KIND);
			 }
			 | PUSH variid_stm intege_stm {
				$$ = new StmNode(PUSHVR_KIND);
				$$->child[0] = $2;
				$$->child[1] = $3;
			 } 
			 | STORE variid_stm {
				$$ = new StmNode(STORVL_KIND);
				$$->child[0] = $2;
			 }
			 | LOAD variid_stm {
				$$ = new StmNode(LOADVL_KIND);
				$$->child[0] = $2;
			 }
			 | LOADADDR variid_stm {
				$$ = new StmNode(LOADAL_KIND);
				$$->child[0] = $2;
			 }
			 | LOADADDR glovar_stm variid_stm {
				$$ = new StmNode(LOADAG_KIND);
				$$->child[0] = $2;
				$$->child[1] = $3;
			 }
			 ;

regvar_stm   : REGVAR {
				$$ = new RegvrExpNode(yytext);
				SymTable::InsertPrecolored(yytext);
			 }
			 ;

glovar_stm   : GLOVAR {
				$$ = new GlovrExpNode(yytext);
			 }
			 ;

locvar_stm   : LOCVAR {
				$$ = new LocvrExpNode(yytext);
				SymTable::InsertInitial(yytext);
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
