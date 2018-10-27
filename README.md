# MiniC-Compiler


[![Build Status](https://travis-ci.org/LC-John/MiniC-Compiler.svg?branch=master)](https://travis-ci.org/LC-John/MiniC-Compiler)

This repo is a series of labs from the Compiler Lab course, EECS, PKU, which aims for a compiler to compile miniC (a subset of C language) source code to RISC-V (majorly RV64I) executable.

![pooh](images/pooh.jpg)

The work flow is shown below.

```
MiniC => (Type Checking) => Eeyore => Tigger => RISC-V
```

## Phase 1. MiniC2Eeyore & Type Checking

Almost finished!

The parse tree is built using Flex & Bison. A symbol table (including all variables and functions) is extracted while building the parse tree.

Error/warning checking is performed. The following errors/warning will be detected.

```
ERROR
	Conflict variables	-- Variables have the same name in the same scope
	Conflict function(s)	-- Functions or functions and variable have the same name even in different scope
	Wrong assignment	-- Assigning to invalid integer variable, or even not-a-variable
	Wrong parameter(s)	-- Assigning invalid actual parameters to the function call
	Wrong function call	-- Call a invalid function
	Wrong expression	-- Using arithmetic expression in condition

WARNING	
	Mixed expression	-- Mix the logical and arithmatic expressions together
	No return		-- The last statement in the function body is not a return
	Function declarition in function body	-- Declare a function inside another function body, which is allowed, but highly unrecommended!
```

Transformation is performed on the MiniC parse tree. A depth-first traverse is performed, and the Eeyore code for the sub-parse-tree of each corresponding node is generated in the meantime.

Waiting to be test automatically on the test server...

## Phase 2. Eeyore2Tigger

To be continued...

## Phase 3. Tigger2RISC-V

To be continued...
