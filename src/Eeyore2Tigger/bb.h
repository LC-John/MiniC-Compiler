#ifndef __BB_H__
#define __BB_H__

#include "tree.h"
#include <stdio.h>

struct ListNode
{
	void* obj;
	struct ListNode* nxt;
	struct ListNode* prv;
};

struct BasicBlock
{
	int n_stmt;
	struct TreeNode* begin;
	struct TreeNode* end;
	struct ListNode** live;
	
};

struct BasicBlock* alloc_bb(struct TreeNode*, struct TreeNode**);	// (StartNode, EndNodeReturnPtr)
void free_bb(struct BasicBlock*);	// (BasicBlock2BFreed)

void print_bb(struct BasicBlock*, FILE*); 	// (BasicBlock2BPrinted, OutputFile)

#endif
