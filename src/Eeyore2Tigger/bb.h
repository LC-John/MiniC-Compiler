#ifndef __BB_H__
#define __BB_H__

#include "tree.h"
#include "list.h"
#include <stdio.h>

struct BasicBlock
{
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

void print_bb(struct BasicBlock*, FILE*); 	// (BasicBlock2BPrinted, OutputFile)

#endif
