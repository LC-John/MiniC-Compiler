#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode* merge_str_lists(struct ListNode* list1, struct ListNode* list2)
{
	struct ListNode* node1;
	struct ListNode* node2;
	for (node2 = list2; node2 != NULL; node2 = node2->nxt)
	{
		int already_have = 0;
		for (node1 = list1; node1 != NULL; node1 = node1->nxt)
			if (node1->obj != NULL && node2->obj != NULL
				&& strcmp((char*)node1->obj, (char*)node2->obj) == 0)
			{
				already_have = 1;
				break;
			}
		if (already_have > 0)
			continue;
		if (list1 == NULL)
		{
			list1 = (struct ListNode*)malloc(sizeof(struct ListNode));
			list1->obj = strdup((char*)(node2->obj));
			list1->nxt = list1->prv = NULL;
		}
		else
		{
			struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
			tmp->obj = strdup((char*)(node2->obj));
			tmp->prv =NULL;
			tmp->nxt = list1;
			list1->prv = tmp;
			list1 = tmp;
		}
	}
	return list1;
}

struct ListNode* find_str_list(struct ListNode* list, char* str)
{
	struct ListNode* node = list;
	while (node != NULL)
	{
		if (strcmp((char*)(node->obj), str) == 0)
			return node;
		node = node->nxt;
	}
	return NULL;
}

struct ListNode* delete_node_from_list(struct ListNode* node, struct ListNode* head)
{
	if (node->prv != NULL && node->nxt != NULL)
	{
		node->prv->nxt = node->nxt;
		node->nxt->prv = node->prv;
	}
	else if (node->prv == NULL && node->nxt != NULL)
	{
		node->nxt->prv = NULL;
		head = node->nxt;
	}
	else if (node->prv != NULL && node->nxt == NULL)
	{
		node->prv->nxt = NULL;
	}
	else	// node->prv == NULL && node->nxt == NULL
	{
		head = NULL;
	}
	if (node->obj != NULL)
		free(node->obj);
	free(node);
	return head;
}

struct ListNode* insert_str_node_into_list(struct ListNode* list, char* str)
{
	if (list == NULL)
	{
		list = (struct ListNode*)malloc(sizeof(struct ListNode));
		list->obj = strdup(str);
		list->nxt = list->prv = NULL;
	}
	else
	{
		struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
		tmp->obj = strdup(str);
		tmp->prv = NULL;
		tmp->nxt = list;
		list->prv = tmp;
		list = tmp;
	}
	return list;
}

struct ListNode* copy_str_list(struct ListNode* list)
{
	struct ListNode* ret = NULL;
	while (list != NULL)
	{
		ret = insert_str_node_into_list(ret, (char*)(list->obj));
		list = list->nxt;
	}
	return ret;
}

int cmp_str_lists(struct ListNode* list1, struct ListNode* list2)
{
	for (struct ListNode* node1 = list1; node1 != NULL; node1 = node1->nxt)
	{
		int find = 0;
		for (struct ListNode* node2 = list2; node2 != NULL; node2 = node2->nxt)
			if (strcmp((char*)(node1->obj), (char*)(node2->obj)) == 0)
			{
				find = 1;
				break;
			}
		if (find != 0)
			continue;
		return -1;
	}
	for (struct ListNode* node1 = list2; node1 != NULL; node1 = node1->nxt)
	{
		int find = 0;
		for (struct ListNode* node2 = list1; node2 != NULL; node2 = node2->nxt)
			if (strcmp((char*)(node1->obj), (char*)(node2->obj)) == 0)
			{
				find = 1;
				break;
			}
		if (find != 0)
			continue;
		return -1;
	}
	return 0;
}
