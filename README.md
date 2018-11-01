# MiniC-Compiler

[![Build Status](https://travis-ci.org/LC-John/MiniC-Compiler.svg?branch=master)](https://travis-ci.org/LC-John/MiniC-Compiler)

This repo is a series of labs from the Compiler Lab course, EECS, PKU, which aims for a compiler to compile miniC (a subset of C language) source code to RISC-V (majorly RV64I) executable.

Repo site: https://github.com/LC-John/MiniC-Compiler

![pooh](images/pooh.jpg)

The three-phase work flow is shown below.

```
MiniC => Eeyore => Tigger => RISC-V
```

## Requirement

```
gcc/g++		version == 7.3.0
Flex/Lex	version == 2.6.0
Bison/Yacc(GNU)	version == 3.0.4
```

## Phase 1. MiniC2Eeyore & Type Checking

It is in the directory "src/MiniC2Eeyore". Use the command "make" to compile the project, and get the executable compiler "eeyore". The options of "eeyore" is shown as below.

```
-I/--input/--infile <filename>		set the input file, whose default is STDIN
-O/--output/--outfile <filename>	set the output file, whose default is STDOUT
-C/--cheating/--cheatingfile <filename>	set the cheating output file, whose default is STDERR
-S/--symtab				output the symbol table to STDOUT
-T/--tree				output the parse tree to STDOUT
```

The work flow of this specific phase is shown below.

```
MiniC => Parse Tree & Symbol Table => Type checking => Eeyore
```

The parse tree is built using Flex & Bison. A symbol table (including all variables and functions) is extracted while building the parse tree.

An example of the parse tree and the Symbol table is shown below. It is generated from "example.c" by running the command "./eeyore -I example.c -T -S".

```C
// example.c

int a;
int b;

int main(){
	a = 10;
	b = 20;
	int c;
	c = a + b;
	return c;
}
```
```
// symbol table of example.c

0	[INT] 	a           	L1~L-1	T0
1	[INT] 	b           	L2~L-1	T1
2	[INT] 	c           	L7~L10	T2
3	[FUNC]	main        	L4~L-1

// parse tree of example.c

[*]Root(31) at L10, P (N) L (N) R (N) C = 2 I = -1
  child(s) 1 of (31)
    [*]VarDefn(2) at L1, P (31) L (N) R (5) C = 3 I = 0
      child(s) 1 of (2)
        [*]Type(int)(0) at L1, P (2) L (N) R (N) C = 0 I = 0
      child(s) 2 of (2)
        [*]Id(a)(1) at L1, P (2) L (N) R (N) C = 0 I = 1
      child(s) 3 of (2)
        NONE
    [*]VarDefn(5) at L2, P (31) L (2) R (N) C = 3 I = 0
      child(s) 1 of (5)
        [*]Type(int)(3) at L2, P (5) L (N) R (N) C = 0 I = 0
      child(s) 2 of (5)
        [*]Id(b)(4) at L2, P (5) L (N) R (N) C = 0 I = 1
      child(s) 3 of (5)
        NONE
  child(s) 2 of (31)
    [*]FuncDefn(30) at L10, P (31) L (N) R (N) C = 4 I = 1
      child(s) 1 of (30)
        [*]Type(int)(6) at L4, P (30) L (N) R (N) C = 0 I = 0
      child(s) 2 of (30)
        [*]Id(main)(29) at L4, P (30) L (N) R (N) C = 0 I = 1
      child(s) 3 of (30)
        NONE
      child(s) 4 of (30)
        [*]StmtVarAssn(10) at L5, P (30) L (N) R (14) C = 2 I = 3
          child(s) 1 of (10)
            [*]Id(a)(7) at L5, P (10) L (N) R (N) C = 0 I = 0
          child(s) 2 of (10)
            [*]ExprInt(9) at L5, P (10) L (N) R (N) C = 1 I = 1
              child(s) 1 of (9)
                [*]Int(10)(8) at L5, P (9) L (N) R (N) C = 0 I = 0
        [*]StmtVarAssn(14) at L6, P (30) L (10) R (18) C = 2 I = 3
          child(s) 1 of (14)
            [*]Id(b)(11) at L6, P (14) L (N) R (N) C = 0 I = 0
          child(s) 2 of (14)
            [*]ExprInt(13) at L6, P (14) L (N) R (N) C = 1 I = 1
              child(s) 1 of (13)
                [*]Int(20)(12) at L6, P (13) L (N) R (N) C = 0 I = 0
        [*]StmtVarDefn(18) at L7, P (30) L (14) R (25) C = 1 I = 3
          child(s) 1 of (18)
            [*]VarDefn(17) at L7, P (18) L (N) R (N) C = 3 I = 0
              child(s) 1 of (17)
                [*]Type(int)(15) at L7, P (17) L (N) R (N) C = 0 I = 0
              child(s) 2 of (17)
                [*]Id(c)(16) at L7, P (17) L (N) R (N) C = 0 I = 1
              child(s) 3 of (17)
                NONE
        [*]StmtVarAssn(25) at L8, P (30) L (18) R (28) C = 2 I = 3
          child(s) 1 of (25)
            [*]Id(c)(19) at L8, P (25) L (N) R (N) C = 0 I = 0
          child(s) 2 of (25)
            [*]ExprBiArith(+)(24) at L8, P (25) L (N) R (N) C = 2 I = 1
              child(s) 1 of (24)
                [*]ExprId(21) at L8, P (24) L (N) R (N) C = 1 I = 0
                  child(s) 1 of (21)
                    [*]Id(a)(20) at L8, P (21) L (N) R (N) C = 0 I = 0
              child(s) 2 of (24)
                [*]ExprId(23) at L8, P (24) L (N) R (N) C = 1 I = 1
                  child(s) 1 of (23)
                    [*]Id(b)(22) at L8, P (23) L (N) R (N) C = 0 I = 0
        [*]StmtReturn(28) at L9, P (30) L (25) R (N) C = 1 I = 3
          child(s) 1 of (28)
            [*]ExprId(27) at L9, P (28) L (N) R (N) C = 1 I = 0
              child(s) 1 of (27)
                [*]Id(c)(26) at L9, P (27) L (N) R (N) C = 0 I = 0

```

Error/warning checking is performed based on the parse tree and the symbol table. The following errors/warnings will be checked. See the errors and warnings [here](/images/ew.md).

```
ERROR
  Conflict variables  -- Variables have the same name in the same scope
  Conflict function(s)  -- Functions or functions and variable have the same name even in different scope
  Wrong assignment  -- Assigning to invalid integer variable, or even not-a-variable
  Wrong parameter(s)  -- Assigning invalid actual parameters to the function call
  Wrong expression  -- Using arithmetic expression in condition
  Undefined variable  -- Using an undefined variable
  Undefined function  -- Using an undefined function (the function may be declared)

WARNING 
  Mixed expression  -- Mix the logical and arithmatic expressions together
  No return   -- The last statement in the function body is not a return
  Function declarition in function body -- Declare a function inside another function body, which is allowed, but highly unrecommended!
```

Transformation is performed on the MiniC parse tree. A depth-first traverse is performed, and the Eeyore code for the sub-parse-tree of each corresponding node is generated in the meantime. The Eeyore code generated from "example.c" is shown as below.

```
// Eeyore code
//     MiniC source: example.c
//     Author: Zhang Huangzhao
//
// View https://github.com/LC-John/MiniC-Compiler for detail


var T0	// [VAR] a @ Line 1
var T1	// [VAR] b @ Line 2

f_main [0]	// [FUNC] main @ Line 10
	var t0
	t0 = 10	// [EXPR] NUM @ Line 5
	T0 = t0	// [STMT] VAR ASSN @ Line 5
	var t1
	t1 = 20	// [EXPR] NUM @ Line 6
	T1 = t1	// [STMT] VAR ASSN @ Line 6
	var T2	// [VAR] c @ Line 7
	var t2
	t2 = T0	// [EXPR] VAR @ Line 8
	var t3
	t3 = T1	// [EXPR] VAR @ Line 8
	var t4
	t4 = t2 + t3	// [EXPR] BI OP + @ Line 8
	T2 = t4	// [STMT] VAR ASSN @ Line 8
	var t5
	t5 = T2	// [EXPR] VAR @ Line 9
	return t5	// [STMT] RET @ Line 9
end f_main

```

It now has passed the MiniC Checker automatic testing.

![pass_eeyore](images/pass_eeyore.png)

Note that the cheating file is used to extract test minic source file from the MiniC Checker, which means it is useless for usual usage. Please ignore it, or redirect it to some temporary file and delete it after compilation. The cheating file option may be deleted in a later time.

## Phase 2. Eeyore2Tigger

To be continued...

## Phase 3. Tigger2RISC-V

To be continued...
