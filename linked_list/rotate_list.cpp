// Problem description:
// Given a list, rotate the list to the right by k places, where k is 
// non-negative.

// For example:
// Given 1->2->3->4->5->NULL and k = 2,
// return 4->5->1->2->3->NULL.


// Idea:
// 1. Connect the list's end to head.
// 2. Find the (k+1)th node from the last, disconnect it from the kth node. The
//    kth node becomes the new head.
// 3. Corner cases:
//    a) k <= 0 || head == NULL, return
//    b) k >= L, L is the list length, set k = k % L.



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

	void rotate_right(int k)
	{
		if(k < 1 || !head)
			return ;

		ListNode* p = head;
		int len = 1;
		while(p->next) // Get list length
		{
			p = p->next;
			++len;
		}

		p->next = head; // Connect head to the tail
		k = len - k % len;

		while(k)
		{
			p = p->next;
			--k;
		}
		head = p->next; // Set head
		p->next = NULL; // Set list end
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

	// l.print_list();

	LinkedList tgt;
	int val[] = { 4, 5, 1, 2, 3 };
	for(int i = 0; i < sizeof(val) / sizeof(val[0]); ++i)
		tgt.add_last(new ListNode(val[i]));

	// tgt.print_list();

	int k = 2;
	l.rotate_right(k);
	// l.print_list();	

	cout << "Test case 1 returns "
	     << (l.is_equal(&tgt) ? "True" : "False")
	     << endl;


	return 0;
}

