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

An example shown below, is generated from "example.c" by running the command "./eeyore -I example.c -T -S".

The original MiniC file "example.c" is shown below.

```C
// example.c
1  int a;
2  int b;
3  
4  int main(){
5  	a = 10;
6  	b = 20;
7  	int c;
8  	c = a + b;
9  	return c;
10  }
```

The symbol table looks like below. [CLICK HERE](/images/parse_tree_example.md) to see the parse tree generated from "example.c".

```
// symbol table of example.c
0	[INT] 	a           	L1~L-1	T0
1	[INT] 	b           	L2~L-1	T1
2	[INT] 	c           	L7~L10	T2
3	[FUNC]	main        	L4~L-1
```

Error/warning checking is performed based on the parse tree and the symbol table. The following errors/warnings will be checked. [CLICK HERE](/images/ew.md) to see the examples of errors and warnings.

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

It has passed the MiniC Checker automatic testing.

![pass_eeyore](images/pass_eeyore.png)

PHASE 1 (MiniC2Eeyore & type checking) COMPLETE!

## Phase 2. Eeyore2Tigger

Eeyore parsing complete.

Eeyore data-flow graph built.

TODO: variable life cycle, register assignment, tigger code generation

## Phase 3. Tigger2RISC-V

To be continued...
