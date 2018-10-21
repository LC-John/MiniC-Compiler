%{
#include <cstdio>
#include <iostream>
#include "typedef.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
using namespace std;

int yylex(void);
extern int yylineno;
void yyerror(const char*);

extern vector<_store> relocated; 
bool isGlobal = true;
extern vector<ins> com_ins;
extern unordered_map<string, unsigned> label_table;
extern vector<int> global_ins;
extern unordered_map<string, unsigned> farg;
extern unordered_map<unsigned, unordered_map<int, int>> f_symbol;
extern unordered_map<unsigned, vector<pair<int ,int>>> f_arr;
inline void checkGlobal(unsigned long i);
set<int> symbol;

unordered_map<int, int> * t_sp;
vector<pair<int, int>> * t_arrp;
%}

%union {
    char *vstr;
    int vint;
}

%token END 0
%token EOL
%token VAR
%token IF
%token GOTO
%token PARAM
%token CALL
%token RETURN
%token ENDT
%token <vint>NUM
%token <vint>SYMBOL
%token <vstr>LABEL
%token <vstr>FUNCTION
%token <vint>OP
%token <vint>LOGIOP

%type <vint>RightValue
%type <vint>OP2

%%
Program
	:	/* Empty */
	|	Program Statement FunctionDecl 
	|	Program FunctionDecl 
	|	Program Statement END
;
FunctionDecl
	:	FunctionName Statement FunctionEnd
;

FunctionName
	:	FUNCTION '['NUM ']' EOL	{
		isGlobal = false;
		com_ins[yylineno - 1] = ins(iNOOP);
        if(label_table.find($1) != label_table.end()){
            cerr << "Redefination of symbol: " << $1 << ". One of defination in line " << yylineno << ".\n";
            exit(-1);
        }
		label_table[$1] = yylineno - 1;
        f_symbol[yylineno - 1] = unordered_map<int, int>();
        t_sp = &f_symbol[yylineno - 1];
        f_arr[yylineno - 1] = vector<pair<int, int>>();
        t_arrp = &f_arr[yylineno - 1];
        farg[$1] = ($3 >> 2);
	}
;
FunctionEnd
	:	ENDT FUNCTION EOL 	{
		isGlobal = true;
		com_ins[yylineno - 1] = ins(iNOOP);
	}
;
Statement
	:	Expression
	|	Statement Expression 
;

RightValue
	:	SYMBOL	{$$ = $1;}
	|	NUM	{$$ = $1;}
;

OP2
	:	OP	{$$ = $1;}
	|	LOGIOP	{$$ = $1;}
;

Expression
	:	SYMBOL '=' RightValue OP2 RightValue EOL  {
			checkGlobal(yylineno - 1);
			com_ins[yylineno - 1] = ins(iOP2, $1, $3, $4, $5);
		}
	|	SYMBOL '=' OP RightValue EOL  {
			checkGlobal(yylineno - 1);
			com_ins[yylineno - 1] = ins(iOP1, $1, $3, $4);
		}
	|	SYMBOL '=' RightValue EOL  {
			checkGlobal(yylineno - 1);
			com_ins[yylineno - 1] = ins(iASS, $1, $3);
		}
	|	SYMBOL '[' RightValue ']' '=' RightValue EOL  {
			checkGlobal(yylineno - 1);
			com_ins[yylineno - 1] = ins(iARRSET, $1, $3, $6);
		}
	|	SYMBOL '=' SYMBOL '[' RightValue ']' EOL  {
			checkGlobal(yylineno - 1);
			com_ins[yylineno - 1] = ins(iARRGET, $1, $3, $5);
		}
	|	IF RightValue LOGIOP RightValue GOTO LABEL EOL {
            relocated.emplace_back(yylineno - 1, $6, 3);
			com_ins[yylineno - 1] = ins(iIF, $2, $3, $4, 0);
		}  
	|	GOTO LABEL EOL  {
            relocated.emplace_back(yylineno - 1, $2, 0);
			com_ins[yylineno - 1] = ins(iGOTO, 0);
		}
	|	LABEL ':' EOL  {
			com_ins[yylineno - 1] = ins(iNOOP);
            if(label_table.find($1) != label_table.end()){
                cerr << "Redefination of symbol: " << $1 << ". One of defination in line " << yylineno << ".\n";
                exit(-1);
            }
			label_table[$1] = yylineno - 1;
		}
	|	PARAM RightValue EOL {
			com_ins[yylineno - 1] = ins(iPARAM, $2);
		}  
	|	CALL FUNCTION EOL {
            relocated.emplace_back(yylineno - 1, $2, 0);
			com_ins[yylineno - 1] = ins(iCALLVOID, 0, 0);
		} 
	|	SYMBOL '=' CALL FUNCTION EOL {
            relocated.emplace_back(yylineno - 1, $4, 1);
			com_ins[yylineno - 1] = ins(iCALL, $1, 0, 0);
		}
	|	RETURN RightValue EOL  {
			com_ins[yylineno - 1] = ins(iRETURN, $2);
		}
	|	RETURN EOL {
			com_ins[yylineno - 1] = ins(iRETURN);
		}
	|	VAR SYMBOL EOL {
			checkGlobal(yylineno - 1);
            if(symbol.find($2) != symbol.end()){
                cerr << "Redefination of symbol: " << $2 << ". One of defination in line " << yylineno << ".\n";
                exit(-1);
            }
            symbol.insert($2);
            if(!isGlobal){
                t_sp->emplace($2, 0); 
            }
            else{
                f_symbol[0][$2] = 0;
            }
			com_ins[yylineno - 1] = ins(iNOOP);
		}
	|	VAR NUM SYMBOL EOL {
			checkGlobal(yylineno - 1);
            if(symbol.find($3) != symbol.end()){
                cerr << "Redefination of symbol: " << $3 << ". One of defination in line " << yylineno << ".\n";
                exit(-1);
            }
            symbol.insert($3);
            if(!isGlobal){
                t_arrp->emplace_back($3, $2 >> 2); 
            }
            else{
                f_arr[0].emplace_back($3, $2 >> 2);
            }
			com_ins[yylineno - 1] = ins(iNOOP);
		}
	|	EOL	{
			com_ins[yylineno - 1] = ins(iNOOP);
		}
;
%%
void yyerror(const char *s) {
	printf("%s\n", s);
}
inline void checkGlobal(unsigned long i){
	if(isGlobal)
		global_ins.push_back(i);
}
