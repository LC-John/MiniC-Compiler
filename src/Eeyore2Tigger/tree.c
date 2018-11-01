#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

void init_tree()
{
	n_treenode = 0;
}

struct TreeNode* alloc_treenode(int arg_type, char* arg_str, int arg_val)
{
	struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	node->idx = n_treenode++;
	node->type = arg_type;
	node->str = NULL;
	if (arg_str != NULL)
		node->str = strdup(arg_str);
	node->val = arg_val;
	switch(node->type)
	{
	
	}
	return node;
}
