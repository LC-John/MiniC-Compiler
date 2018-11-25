#ifndef __LIST_H__
#define __LIST_H__

struct ListNode
{
	void* obj;
	struct ListNode* nxt;
	struct ListNode* prv;
};

struct ListNode* merge_str_lists(struct ListNode*, struct ListNode*);	// (List1, List2) Merge list2 into list1
struct ListNode* find_str_list(struct ListNode*, char*);	// (List, String2BFound)

struct ListNode* delete_node_from_list(struct ListNode*, struct ListNode*);	// (ListNode2BDelted, ListHead)
struct ListNode* insert_str_node_into_list(struct ListNode*, char*);	// (ListHead, String2BInserted)

struct ListNode* copy_str_list(struct ListNode*);	// (List2BCopied)
int cmp_str_lists(struct ListNode*, struct ListNode*);	// (List1, List2)

#endif
