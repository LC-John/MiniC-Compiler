%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stk = 0;
int yylex(void);
void yyerror(char*);
extern FILE* yyin;
extern FILE* yyout;
extern int lineno;
%}

%union {
	int val;
	char* str;
};

%token <str>	EOL	ARR_L	ARR_R	VAR
%token <str>	MALLOC	IF	GOTO	CALL
%token <str>	STORE	LOAD	LOADADDR
%token <str>	RETURN	END	COLON	ASSIGN
%token <str>	OP	REG	LABEL	FUNC
%token <val>	INT

%%

goal	: goal func_decl
	| goal global_var_decl
	| goal global_arr_decl
	| goal EOL { }
	| { }
	;

global_var_decl	: VAR ASSIGN INT EOL
	;

global_arr_decl	: VAR ASSIGN MALLOC INT EOL
	;

func_decl	: func_begin func_body func_end	{ }
	;

func_begin	: FUNC ARR_L INT ARR_R ARR_L INT ARR_R EOL	{
		stk = ($6 / 4 + 1) * 16;
		fprintf(yyout, "\t.text\t;; %s[%d][%d] @L%d\n", $1, $3, $6, lineno);
		fprintf(yyout, "\t.align 2\n");
		fprintf(yyout, "\t.global %s\n", $1+2);
		fprintf(yyout, "\t.type %s, @function\n", $1+2);
		fprintf(yyout, "%s:\n", $1+2);
		fprintf(yyout, "\tadd sp, sp, %d\n", -stk);
		fprintf(yyout, "\tsw ra, %d(sp)\n", stk-4);
	}
	| func_begin EOL	{ }
	;

func_end	: END FUNC EOL	{
		fprintf(yyout, "\t.size %s, .-%s\t;; end %s @L%d\n", $2+2, $2+2, $2, lineno);
	}
	;

func_body	: func_body REG ASSIGN REG OP REG EOL	{	// rd = rs1 op rs2
		switch($5[0])
		{
		case '+':	
			fprintf(yyout, "\t\tadd %s, %s, %s\t;; %s = %s + %s @L%d\n",
					$2, $4, $6, $2, $4, $6, lineno);
				break;
		case '-':
			fprintf(yyout, "\t\tsub %s, %s, %s\t;; %s = %s - %s @L%d\n",
					$2, $4, $6, $2, $4, $6, lineno);
			break;
		case '*':
			fprintf(yyout, "\t\tmul %s, %s, %s\t;; %s = %s * %s @L%d\n",
					$2, $4, $6, $2, $4, $6, lineno);
			break;
		case '/':
			fprintf(yyout, "\t\tdiv %s, %s, %s\t;; %s = %s / %s @L%d\n",
					$2, $4, $6, $2, $4, $6, lineno);
			break;
		case '%':
			fprintf(yyout, "\t\trem %s, %s, %s\t;; %s = %s %% %s @L%d\n",
					$2, $4, $6, $2, $4, $6, lineno);
			break;
		case '&':
			fprintf(yyout, "\t\tseqz %s, %s\t;; %s = %s && %s @L%d\n",
					$2, $4, $2, $4, $6, lineno); 
			fprintf(yyout, "\t\tadd %s, %s, -1\n", $2, $2);
			fprintf(yyout, "\t\tand %s, %s, %s\n", $2, $2, $6);
			fprintf(yyout, "\t\tsnez %s, %s\n", $2, $2);
			break;
		case '|':
			fprintf(yyout, "\t\tor %s, %s, %s\t;; %s = %s || %s @L%d\n",
					$2, $4, $6, $2, $4, $6, lineno);
			fprintf(yyout, "\t\tsnez %s, %s", $2, $2);
			break;
		case '=':
			fprintf(yyout, "\t\txor %s, %s, %s\t;; %s = %s == %s @L%d\n",
					$2, $4, $6, $2, $4, $6, lineno);
			fprintf(yyout, "\t\tseqz %s, %s\n", $2, $2);
			break;
		case '!':
			fprintf(yyout, "\t\txor %s, %s, %s\t;; %s = %s != %s @L%d\n",
					$2, $4, $6, $2, $4, $6, lineno);
			fprintf(yyout, "\t\tsnez %s, %s\n", $2, $2);
			break;
		case '<':
			fprintf(yyout, "\t\tslt %s, %s, %s\t;; %s = %s < %s @L%d\n",
					$2, $4, $6, $2, $4, $6, lineno);
			break;
		case '>':
			fprintf(yyout, "\t\tslt %s, %s, %s\t;; %s = %s > %s @L%d\n",
					$2, $6, $4, $2, $4, $6, lineno);
			break;
		default:	break;
		}
	}
	| func_body REG ASSIGN REG OP INT EOL	{	// rd = rs op imm
		switch($5[0])
		{
		case '+':
			fprintf(yyout, "\t\taddi %s, %s, %d\t;; %s = %s + %d @L%d\n",
					$2, $4, $6, $2, $4, $6, lineno);
			break;
		case '-':
			fprintf(yyout, "\t\taddi %s, %s, %d\t;; %s = %s - %d @L%d\n",
					$2, $4, -$6, $2, $4, $6, lineno);
			break;
		case '*':
			fprintf(yyout, "\t\taddi %s, x0, %d\t;; %s = %s * %d @L%d\n",
					$2, $6, $2, $4, $6, lineno);
			fprintf(yyout, "\t\tmul %s, %s, %s\n", $2, $4, $2);
			break;
		case '/':
			fprintf(yyout, "\t\taddi %s, x0, %d\t;; %s = %s / %d @L%d\n",
					$2, $6, $2, $4, $6, lineno);
			fprintf(yyout, "\t\tdiv %s, %s, %s\n", $2, $4, $2);
			break;
		case '%':
			fprintf(yyout, "\t\taddi %s, x0, %d\t;; %s = %s %% %d @L%d\n",
					$2, $6, $2, $4, $6, lineno);
			fprintf(yyout, "\t\trem %s, %s, %s\n", $2, $4, $2);
			break;
		case '&':
			fprintf(yyout, "\t\tseqz %s, %s\t;; %s = %s && %d @L%d\n",
					$2, $4, $2, $4, $6, lineno); 
			fprintf(yyout, "\t\tadd %s, %s, -1\n", $2, $2);
			fprintf(yyout, "\t\tandi %s, %s, %d\n", $2, $2, $6);
			fprintf(yyout, "\t\tsnez %s, %s\n", $2, $2);
			break;
		case '|':
			fprintf(yyout, "\t\tori %s, %s, %d\t;; %s = %s || %d @L%d\n",
					$2, $4, $6, $2, $4, $6, lineno);
			fprintf(yyout, "\t\tsnez %s, %s", $2, $2);
			break;
		case '=':
			fprintf(yyout, "\t\taddi %s, x0, %d\t;; %s = %s == %d @L%d\n",
					$2, $6, $2, $4, $6, lineno);
			fprintf(yyout, "\t\txor %s, %s, %s\n", $2, $4, $2);
			fprintf(yyout, "\t\tseqz %s, %s\n", $2, $2);
			break;
		case '!':
			fprintf(yyout, "\t\taddi %s, x0, %d\t;; %s = %s != %d @L%d\n",
					$2, $6, $2, $4, $6, lineno);
			fprintf(yyout, "\t\txor %s, %s, %s\n", $2, $4, $2);
			fprintf(yyout, "\t\tsnez %s, %s\n", $2, $2);
			break;
		case '<':
			fprintf(yyout, "\t\tslti %s, %s, %d\t;; %s = %s < %d @L%d\n",
					$2, $4, $6, $2, $4, $6, lineno);
			break;
		case '>':
			fprintf(yyout, "\t\taddi %s, x0, %d\t;; %s = %s > %d @L%d\n",
					$2, $6, $2, $4, $6, lineno);
			fprintf(yyout, "\t\tslt %s, %s, %s\n", $2, $2, $4);
			break;
		default:	break;
		}
	}
	| func_body REG ASSIGN OP REG EOL	{	// rd = op rs
		switch($4[0])
		{
		case '+':
			fprintf(yyout, "\t\tadd %s, x0, %s\t;; %s = + %s @L%d\n",
					$2, $5, $2, $5, lineno);
			break;
		case '-':
			fprintf(yyout, "\t\tsub %s, x0, %s\t;; %s = - %s @L%d\n",
					$2, $5, $2, $5, lineno);
			break;
		case '!':
			fprintf(yyout, "\t\txori %s, %s, -1\t;; %s = ! %s @L%d\n",
					$2, $5, $2, $5, lineno);
			fprintf(yyout, "\t\tsnez %s, %s\n", $2, $2);
			break;
		default: break;
		}
	}
	| func_body REG ASSIGN REG EOL	{	// rd = rs
		fprintf(yyout, "\t\taddi %s, %s, 0\t;; %s = %s @L%d\n",
				$2, $4, $2, $4, lineno);
	}
	| func_body REG ASSIGN INT EOL	{	// rd = imm
		fprintf(yyout, "\t\taddi %s, x0, %d\t;; %s = %d @L%d\n",
				$2, $4, $2, $4, lineno);
	}
	| func_body REG ARR_L INT ARR_R ASSIGN REG EOL	{	// rd[imm] = rs
		fprintf(yyout, "\t\tsw %s, %d(%s)\t;; %s[%d] = %s @L%d\n",
				$7, $4, $2, $2, $4, $7, lineno);
	}
	| func_body REG ASSIGN REG ARR_L INT ARR_R EOL	{	// rd = rs[imm]
		fprintf(yyout, "\t\tlw %s, %d(%s)\t;; %s = %s[%d] @L%d\n",
				$2, $6, $4, $2, $4, $6, lineno);
	}
	| func_body IF REG OP REG GOTO LABEL EOL	{	// if rs1 op rs2 goto label
		switch($4[0])
		{
		case '<':
			if (strlen($4) == 1)
				fprintf(yyout, "\t\tblt %s, %s, .%s\t;; if %s < %s goto %s @L%d\n",
						$3, $5, $7, $3, $5, $7, lineno);
			else if (strlen($4) == 2 && $4[1] == '=')
				fprintf(yyout, "\t\tble %s, %s, .%s\t;; if %s <= %s goto %s @L%d\n",
						$3, $5, $7, $3, $5, $7, lineno);
			break;
		case '>':
			if (strlen($4) == 1)
				fprintf(yyout, "\t\tblt %s, %s, .%s\t;; if %s > %s goto %s @L%d\n",
						$3, $7, $5, $3, $5, $7, lineno);
			else if (strlen($4) == 2 && $4[1] == '=')
				fprintf(yyout, "\t\tble %s, %s, .%s\t;; if %s >= %s goto %s @L%d\n",
						$3, $7, $5, $3, $5, $7, lineno);
			break;
		case '=':
			fprintf(yyout, "\t\tbeq %s, %s, .%s\t;; if %s == %s goto %s @L%d\n",
					$3, $7, $5, $3, $5, $7, lineno);
			break;
		case '!':
			fprintf(yyout, "\t\tbne %s, %s, .%s\t;; if %s != %s goto %s @L%d\n",
					$3, $7, $5, $3, $5, $7, lineno);
			break;
		default:
			break;
		}
	}
	| func_body GOTO LABEL EOL	{	// goto label
		fprintf(yyout, "\t\tj .%s\t;; goto %s @L%d\n", $3, $3, lineno);
	}
	| func_body LABEL COLON EOL	{	// label:
		fprintf(yyout, "\t.%s:\t;; .%s: @L%d\n", $2, $2, lineno);
	}
	| func_body CALL FUNC EOL	{	// call func
		fprintf(yyout, "\t\tcall %s\t;; call %s @L%d\n", $3, $3, lineno);
	}
	| func_body STORE REG INT EOL	{	// mem[rs] = imm
		fprintf(yyout, "\t\tsw %s, %d(sp)\t;; store %s %d @L%d\n",
				$3, $4*4, $3, $4, lineno);
	}
	| func_body LOAD INT REG EOL	{	// rd = mem[imm]
		fprintf(yyout, "\t\tlw %s, %d(sp)\t;; load %d %s @L%d\n",
				$4, $3*4, $3, $4, lineno);
	}
	| func_body LOAD VAR REG EOL	{	// rd = mem[var]
		fprintf(yyout, "\t\tlui %s, %%hi(%s)\t;; load %s %s @L%d\n",
				$4, $3, $3, $4, lineno);
		fprintf(yyout, "\t\taddi %s, %%lo(%s)(%s)\n", $4, $3, $4);
	}
	| func_body LOADADDR INT REG EOL	{	// rd = addr(stk+imm)
		fprintf(yyout, "\t\taddi %s, sp, %d\t;; loadaddr %d %s @L%d\n",
				$4, $3*4, $3, $4, lineno);
	}
	| func_body LOADADDR VAR REG EOL	{	// rd = addr(var)
		fprintf(yyout, "\t\tlui %s, %%hi(%s)\t;; loadaddr %s %s @L%d\n",
				$4, $3, $3, $4, lineno);
		fprintf(yyout, "\t\taddi %s, %s, %%lo(%s)\n", $4, $4, $3);
	}
	| func_body RETURN EOL	{	// return
		fprintf(yyout, "\t\tlw ra, %d(sp)\t;; return @L%d\n", stk-4, lineno);
		fprintf(yyout, "\t\taddi sp, sp, %d\n", stk);
		fprintf(yyout, "\t\tjr ra\n");
	}
	| func_body EOL { }
	| { }
	;

%%

void yyerror(char* s)
{
	fprintf(stderr, ">> ERROR@L%d: %s\n", lineno, s);
	exit(-1);
}
