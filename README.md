# MiniC-Compiler


[![Build Status](https://travis-ci.org/LC-John/MiniC-Compiler.svg?branch=master)](https://travis-ci.org/LC-John/MiniC-Compiler)

This repo is a series of labs from the Compiler Lab course, EECS, PKU, which aims for a compiler to compile miniC (a subset of C language) source code to RISC-V (majorly RV64I) executable.

![pooh](images/pooh.jpg)

The work flow is shown below.

```
MiniC => (Type Checking) => Eeyore => Tigger => RISC-V
```

## Phase 1. MiniC2Eeyore & Type Checking

In progress...

Now, the parse tree is built using Flex & Bison. A symbol table (including all variables and functions) is extracted while building the parse tree.

Type Checking & parse tree transformation will be finished soon.

## Phase 2. Eeyore2Tigger

To be continued...

## Phase 3. Tigger2RISC-V

To be continued...
