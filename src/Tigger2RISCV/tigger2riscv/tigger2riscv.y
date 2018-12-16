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

global_var_decl	: VAR ASSIGN INT EOL	{
		//fprintf(yyout, "; %s = %d @L%d\n", $1, $3, lineno);
		fprintf(yyout, "\t.global %s\n", $1);
		fprintf(yyout, "\t.section .sdata\n");
		fprintf(yyout, "\t.align 2\n");
		fprintf(yyout, "\t.type %s, @object\n", $1);
		fprintf(yyout, "\t.size %s, 4\n", $1);
		fprintf(yyout, "%s:\n", $1);
		fprintf(yyout, "\t.word %d\n", $3);
	}
	;

global_arr_decl	: VAR ASSIGN MALLOC INT EOL	{
		//fprintf(yyout, "; %s = malloc %d @L%d\n", $1, $4, lineno);
		fprintf(yyout, "\t.comm %s, %d, 4\n", $1, $4*4);
	}
	;

func_decl	: func_begin func_body func_end	{ }
	;

func_begin	: FUNC ARR_L INT ARR_R ARR_L INT ARR_R EOL	{
		stk = ($6 / 4 + 1) * 16;
		//fprintf(yyout, "; %s[%d][%d] @L%d\n", $1, $3, $6, lineno);
		fprintf(yyout, "\t.text\t\n");
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
		// fprintf(yyout, "; end %s @L%d\n", $2, lineno);
		fprintf(yyout, "\t.size %s, .-%s\n", $2+2, $2+2);
	}
	;

func_body	: func_body REG ASSIGN REG OP REG EOL	{	// rd = rs1 op rs2
		switch($5[0])
		{
		case '+':	
			//fprintf(yyout, "; %s = %s + %s @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\tadd %s, %s, %s\n", $2, $4, $6);
			break;
		case '-':
			//fprintf(yyout, "; %s = %s - %s @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\tsub %s, %s, %s\n", $2, $4, $6);
			break;
		case '*':
			//fprintf(yyout, "; %s = %s * %s @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\tmul %s, %s, %s\n", $2, $4, $6);
			break;
		case '/':
			//fprintf(yyout, "; %s = %s / %s @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\tdiv %s, %s, %s\n", $2, $4, $6);
			break;
		case '%':
			//fprintf(yyout, "; %s = %s %% %s @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\trem %s, %s, %s\n", $2, $4, $6);
			break;
		case '&':
			//fprintf(yyout, "; %s = %s && %s @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\tseqz %s, %s\n", $2, $4); 
			fprintf(yyout, "\t\tadd %s, %s, -1\n", $2, $2);
			fprintf(yyout, "\t\tand %s, %s, %s\n", $2, $2, $6);
			fprintf(yyout, "\t\tsnez %s, %s\n", $2, $2);
			break;
		case '|':
			// fprintf(yyout, "; %s = %s || %s @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\tor %s, %s, %s\n", $2, $4, $6);
			fprintf(yyout, "\t\tsnez %s, %s\n", $2, $2);
			break;
		case '=':
			// fprintf(yyout, "; %s = %s == %s @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\txor %s, %s, %s\n", $2, $4, $6);
			fprintf(yyout, "\t\tseqz %s, %s\n", $2, $2);
			break;
		case '!':
			// fprintf(yyout, "; %s = %s != %s @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\txor %s, %s, %s\n", $2, $4, $6);
			fprintf(yyout, "\t\tsnez %s, %s\n", $2, $2);
			break;
		case '<':
			// fprintf(yyout, "; %s = %s < %s @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\tslt %s, %s, %s\n", $2, $4, $6);
			break;
		case '>':
			// fprintf(yyout, "; %s = %s > %s @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\tslt %s, %s, %s\n", $2, $6, $4);
			break;
		default:	break;
		}
	}
	| func_body REG ASSIGN REG OP INT EOL	{	// rd = rs op imm
		switch($5[0])
		{
		case '+':
			// fprintf(yyout, "; %s = %s + %d @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\taddi %s, %s, %d\n", $2, $4, $6);
			break;
		case '-':
			// fprintf(yyout, "; %s = %s - %d @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\taddi %s, %s, %d\n", $2, $4, -$6);
			break;
		case '*':
			// fprintf(yyout, "; %s = %s * %d @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\taddi %s, x0, %d\n", $2, $6);
			fprintf(yyout, "\t\tmul %s, %s, %s\n", $2, $4, $2);
			break;
		case '/':
			// fprintf(yyout, "; %s = %s / %d @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\taddi %s, x0, %d\n", $2, $6);
			fprintf(yyout, "\t\tdiv %s, %s, %s\n", $2, $4, $2);
			break;
		case '%':
			// fprintf(yyout, "; %s = %s %% %d @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\taddi %s, x0, %d\n", $2, $6);
			fprintf(yyout, "\t\trem %s, %s, %s\n", $2, $4, $2);
			break;
		case '&':
			// fprintf(yyout, "; %s = %s && %d @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\tseqz %s, %s\n", $2, $4); 
			fprintf(yyout, "\t\tadd %s, %s, -1\n", $2, $2);
			fprintf(yyout, "\t\tandi %s, %s, %d\n", $2, $2, $6);
			fprintf(yyout, "\t\tsnez %s, %s\n", $2, $2);
			break;
		case '|':
			// fprintf(yyout, "; %s || %d @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\tori %s, %s, %d\n", $2, $4, $6);
			fprintf(yyout, "\t\tsnez %s, %s", $2, $2);
			break;
		case '=':
			// fprintf(yyout, "; %s = %s == %d @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\taddi %s, x0, %d\n", $2, $6);
			fprintf(yyout, "\t\txor %s, %s, %s\n", $2, $4, $2);
			fprintf(yyout, "\t\tseqz %s, %s\n", $2, $2);
			break;
		case '!':
			// fprintf(yyout, "; %s = %s != %d @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\taddi %s, x0, %d\n", $2, $6);
			fprintf(yyout, "\t\txor %s, %s, %s\n", $2, $4, $2);
			fprintf(yyout, "\t\tsnez %s, %s\n", $2, $2);
			break;
		case '<':
			// fprintf(yyout, "; %s = %s < %d @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\tslti %s, %s, %d\n", $2, $4, $6);
			break;
		case '>':
			// fprintf(yyout, "; %s = %s > %d @L%d\n", $2, $4, $6, lineno);
			fprintf(yyout, "\t\taddi %s, x0, %d\n", $2, $6);
			fprintf(yyout, "\t\tslt %s, %s, %s\n", $2, $2, $4);
			break;
		default:	break;
		}
	}
	| func_body REG ASSIGN OP REG EOL	{	// rd = op rs
		switch($4[0])
		{
		case '+':
			// fprintf(yyout, "; %s = + %s @L%d\n", $2, $5, lineno);
			fprintf(yyout, "\t\tadd %s, x0, %s\n", $2, $5);
			break;
		case '-':
			// fprintf(yyout, "; %s = - %s @L%d\n", $2, $5, lineno);
			fprintf(yyout, "\t\tsub %s, x0, %s\n", $2, $5);
			break;
		case '!':
			// fprintf(yyout, "; %s = ! %s @L%d\n", $2, $5, lineno);
			fprintf(yyout, "\t\txori %s, %s, -1\n", $2, $5);
			fprintf(yyout, "\t\tsnez %s, %s\n", $2, $2);
			break;
		default: break;
		}
	}
	| func_body REG ASSIGN REG EOL	{	// rd = rs
		// fprintf(yyout, "; %s = %s @L%d\n", $2, $4, lineno);
		fprintf(yyout, "\t\taddi %s, %s, 0\n", $2, $4);
	}
	| func_body REG ASSIGN INT EOL	{	// rd = imm
		// fprintf(yyout, "; %s = %d @L%d\n", $2, $4, lineno);
		fprintf(yyout, "\t\taddi %s, x0, %d\n", $2, $4);
	}
	| func_body REG ARR_L INT ARR_R ASSIGN REG EOL	{	// rd[imm] = rs
		// fprintf(yyout, "; %s[%d] = %s @L%d\n", $2, $4, $7, lineno);
		fprintf(yyout, "\t\tsw %s, %d(%s)\n", $7, $4, $2);
	}
	| func_body REG ASSIGN REG ARR_L INT ARR_R EOL	{	// rd = rs[imm]
		// fprintf(yyout, "; %s = %s[%d] @L%d\n", $2, $4, $6, lineno);
		fprintf(yyout, "\t\tlw %s, %d(%s)\n", $2, $6, $4);
	}
	| func_body IF REG OP REG GOTO LABEL EOL	{	// if rs1 op rs2 goto label
		switch($4[0])
		{
		case '<':
			if (strlen($4) == 1)
			{
				// fprintf(yyout, "; if %s < %s goto %s @L%d\n", $3, $5, $7, lineno);
				fprintf(yyout, "\t\tblt %s, %s, .%s\n", $3, $5, $7);
			}
			else if (strlen($4) == 2 && $4[1] == '=')
			{
				// fprintf(yyout, "; if %s <= %s goto %s @L%d\n", $3, $5, $7, lineno);
				fprintf(yyout, "\t\tble %s, %s, .%s\n", $3, $5, $7);
			}
			break;
		case '>':
			if (strlen($4) == 1)
			{
				// fprintf(yyout, "; if %s > %s goto %s @L%d\n", $3, $5, $7, lineno);
				fprintf(yyout, "\t\tblt %s, %s, .%s\n", $5, $3, $7);
			}
			else if (strlen($4) == 2 && $4[1] == '=')
			{
				// fprintf(yyout, "; if %s >= %s goto %s @L%d\n", $3, $5, $7, lineno);
				fprintf(yyout, "\t\tble %s, %s, .%s\n", $5, $3, $7);
			}
			break;
		case '=':
			// fprintf(yyout, "; if %s == %s goto %s @L%d\n", $3, $5, $7, lineno);
			fprintf(yyout, "\t\tbeq %s, %s, .%s\n", $3, $5, $7);
			break;
		case '!':
			// fprintf(yyout, "; if %s != %s goto %s @L%d\n", $3, $5, $7, lineno);
			fprintf(yyout, "\t\tbne %s, %s, .%s\n", $3, $5, $7);
			break;
		default:
			break;
		}
	}
	| func_body GOTO LABEL EOL	{	// goto label
		// fprintf(yyout, "; goto %s @L%d\n", $3, lineno);
		fprintf(yyout, "\t\tj .%s\n", $3);
	}
	| func_body LABEL COLON EOL	{	// label:
		// fprintf(yyout, "; %s: @L%d\n", $2, lineno);
		fprintf(yyout, "\t.%s:\n", $2);
	}
	| func_body CALL FUNC EOL	{	// call func
		// fprintf(yyout, "; call %s @L%d\n", $3, lineno);
		fprintf(yyout, "\t\tcall %s\n", $3+2);
	}
	| func_body STORE REG INT EOL	{	// mem[rs] = imm
		// fprintf(yyout, "; store %s %d @L%d\n", $3, $4, lineno);
		fprintf(yyout, "\t\tsw %s, %d(sp)\n", $3, $4*4);
	}
	| func_body LOAD INT REG EOL	{	// rd = mem[imm]
		// fprintf(yyout, "; load %d %s @L%d\n", $3, $4, lineno);
		fprintf(yyout, "\t\tlw %s, %d(sp)\n", $4, $3*4);
	}
	| func_body LOAD VAR REG EOL	{	// rd = mem[var]
		// fprintf(yyout, "; load %s %s @L%d\n", $3, $4, lineno);
		fprintf(yyout, "\t\tlui %s, %%hi(%s)\n", $4, $3);
		fprintf(yyout, "\t\taddi %s, %%lo(%s)(%s)\n", $4, $3, $4);
	}
	| func_body LOADADDR INT REG EOL	{	// rd = addr(stk+imm)
		// fprintf(yyout, "; loadaddr %d %s @L%d\n", $3, $4, lineno);
		fprintf(yyout, "\t\taddi %s, sp, %d\n", $4, $3*4);
	}
	| func_body LOADADDR VAR REG EOL	{	// rd = addr(var)
		// fprintf(yyout, "; loadaddr %s %s @L%d\n", $3, $4, lineno);
		fprintf(yyout, "\t\tlui %s, %%hi(%s)\n", $4, $3);
		fprintf(yyout, "\t\taddi %s, %s, %%lo(%s)\n", $4, $4, $3);
	}
	| func_body RETURN EOL	{	// return
		// fprintf(yyout, "; return @L%d\n", lineno);
		fprintf(yyout, "\t\tlw ra, %d(sp)\n", stk-4);
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
