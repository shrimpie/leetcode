// Problem description:
// Sort a linked list using insertion sort.


// Idea:
// 1. Use a dummy head to ease operation.
// 2. Iterate currently sorted items by comparing next node value with the 
//    next to-be-inserted node's value, so you got the previous node's pointer.
// 3. Run an example if there is any problem.


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

	void insertion_sort()
	{
		ListNode* new_head = new ListNode(INT_MIN);
		while(head)
		{
			ListNode* cur = head;
			ListNode* p = new_head;
			// p points to head of already sorted list.
			head = head->next;
			// head points to next to-be-inserted node.

			// Find the insert position.
			while(p->next && p->next->val <= cur->val)
				p = p->next;

			// connects them.
			cur->next = p->next;
			p->next = cur;
		}

		head = new_head->next;
		delete new_head;
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
	int val[] = { 4, 5, 1, 2, 3 };
	for(int i = 0; i < sizeof(val) / sizeof(val[0]); ++i)
		l.add_last(new ListNode(val[i]));

	LinkedList tgt;
	for(int i = 0; i < 5; ++i)
		tgt.add_last(new ListNode(i+1));

	l.insertion_sort();

	cout << "Test case 1 returns "
	     << (l.is_equal(&tgt) ? "True" : "False")
	     << endl;


	return 0;
}

