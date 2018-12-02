#ifndef __REG_ALLOC_H__
#define __REG_ALLOC_H__

#include "bb.h"
#include "tree.h"

#define REG_N		27

#define REG_T0		0	// Caller-saved
#define REG_T1		1
#define REG_T2		2
#define REG_T3		3
#define REG_T4		4
#define REG_T5		5
#define REG_T6		6
#define REG_A0		7	// Caller-saved, function parameters & return values
#define REG_A1		8
#define REG_A2		9
#define REG_A3		10	
#define REG_A4		11
#define REG_A5		12
#define REG_A6		13
#define REG_A7		14
#define REG_S0		15	// Callee-saved
#define REG_S1		16
#define REG_S2		17
#define REG_S3		18
#define REG_S4		19
#define REG_S5		20
#define REG_S6		21
#define REG_S7		22
#define REG_S8		23
#define REG_S9		24
#define REG_S10		25
#define REG_S11		26
#define REG_GLOBAL	100
#define REG_STACK	1000

struct BasicBlock;

char* registers[REG_N];

void init_reg();

int find_reg(int, int*, int*, char**);	// (ID#, DieAt, RegAllocation, RegFile)

int reg_alloc(struct BasicBlock*, int, int*);	// (CurrentBB, CurrentStackSize, RegUsed)

#endif
