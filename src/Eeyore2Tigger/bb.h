#ifndef __BB_H__
#define __BB_H__

#include "tree.h"
#include "list.h"
#include <stdio.h>

struct BasicBlock
{
	int flag;
	int idx;
	int n_stmt;
	char* str;
	struct TreeNode* begin;
	struct TreeNode* end;
	struct ListNode** live;
	struct BasicBlock* nxt[2];
	struct ListNode* prv;
};

int n_bb;

void init_bb();

struct BasicBlock* alloc_bb(struct TreeNode*, struct TreeNode**);	// (StartNode, EndNodeReturnPtr)
void free_bb(struct BasicBlock*);	// (BasicBlock2BFreed)

struct ListNode** tree2bbs(struct TreeNode* root, int*);	// (ParseTreeRoot, FuncNumberReturn Ptr)

int var_life_within_bb(struct BasicBlock*, struct ListNode*);	// (BB, ListNodeContainer4LiveVarsTillThisBBEnd)
int var_life_between_bbs(struct ListNode*);	// (ListNodeContainer4EntryBB)
int var_life_bb2bb(struct BasicBlock*, struct BasicBlock*);	// (BB1, BB2) BB is in BB2->prv

void print_bb(struct BasicBlock*, FILE*); 	// (BasicBlock2BPrinted, OutputFile)

#endif
