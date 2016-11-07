// Problem description:
// Reverse a linked list from position m to n. Do it in-place and in one-pass.

// For example:
// Given 1->2->3->4->5->NULL and m = 2 and n = 4,
// return 1->4->3->2->5->NULL.


// Idea:
// 1. Since when m = 1, the head of the list will be modified, so you might 
//    want to add a dummy head.
// 2. Find the (m-1)th node, and from that reverse the list with length of 
//    n - m + 1.
// 3. At last concatenate the lists.





#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode * next;
	ListNode(int x) : val(x), next(NULL) {}
};



class LinkedList
{
private:
	ListNode* head;

public:
	LinkedList()
	{
		head = NULL;
	}

	ListNode* get_head()
	{
		return head;
	}

	void add_front(ListNode* node)
	{
		if(!head)
			head = node;
		else
		{
			node->next = head;
			head = node;
		}
	}
	void add_last(ListNode* node)
	{
		if(!head)
			head = node;
		else
		{
			ListNode* p = head;
			while(p->next)
				p = p->next;
			p->next = node;
		}
	}

	bool is_equal(LinkedList* another)
	{
		ListNode* p = head;
		ListNode* q = another->get_head();
		while(p && q)
		{
			if(p->val != q->val)
				return false;
			p = p->next;
			q = q->next;
		}
		if(!p && !q)
			return true;
		return false;
	}

	void reverse_between(int m, int n)
	{
		if(m < 1 || m >= n || !head)
			return ;
		ListNode* dummy = new ListNode(-1);
		dummy->next = head;
		head = dummy;

		// Move head to (m-1)th node
		for(int i = 0; i < m - 1; ++i)
		{
			if(head)
				head = head->next;
			else
				return;
		}

		// Reverse list from pre with length n - m + 1
		ListNode* pre = head->next, *cur = pre->next;
		for(int i = 0; i < n - m; ++i)
		{
			ListNode* tmp = cur->next;
			cur->next = pre;
			pre = cur;
			cur = tmp;
		}

		head->next->next = cur;
		head->next = pre;
		head = dummy->next;
		delete dummy;
	}

	void print_list()
	{
		cout << "The list contains: ";
		ListNode* n = head;
		while(n != NULL)
		{
			cout << n->val << " ";
			n = n->next;
		}
		cout << endl;
	}

	~LinkedList()
	{
		ListNode* p = head;
		while(p->next)
		{
			p = p->next;
			delete head;
			head = p;
		}
	}
};




int main()
{
	LinkedList l;
	for(int i = 0; i < 5; ++i)
		l.add_last(new ListNode(i+1));

	LinkedList tgt;
	int val[] = { 1, 4, 3, 2, 5 };
	for(int i = 0; i < sizeof(val) / sizeof(val[0]); ++i)
		tgt.add_last(new ListNode(val[i]));

	int m = 2, n = 4;
	l.reverse_between(m, n);

	cout << "Test case 1 returns "
	     << (l.is_equal(&tgt) ? "True" : "False")
	     << endl;


	return 0;
}

