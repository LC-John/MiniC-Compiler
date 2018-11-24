#ifndef __LIST_H__
#define __LIST_H__

struct ListNode
{
	void* obj;
	struct ListNode* nxt;
	struct ListNode* prv;
};

#endif
