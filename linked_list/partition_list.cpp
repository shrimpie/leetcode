// Problem description:

// Given a linked list and a value x, partition it such that all nodes less 
// than x come before nodes greater than or equal to x.
// You should preserve the original ralative order of the nodes in each of 
// the two partitions.

// For example,
// Given 1->4->3->2->5->2 and x = 3,
// return 1->2->2->4->3->5.




// Idea:
// 1. Construct a new list with nodes >= x, and append it to the remaining
//    list.



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

	void partition(int x)
	{
		if(!head)
			return;
		// Two dummy heads and a tail.
		ListNode* head1 = new ListNode(-1);
		ListNode* head2 = new ListNode(-1);
		ListNode* tail2 = head2;
		head1->next = head;
		head = head1;

		while(head->next)
		{
			if(head->next->val < x) // Skip nodes less than x
				head = head->next;
			else
			{
				// Tail points to the node >= x.
				tail2->next = head->next;
				// Modify original list pointer to jump over nodes >= x.
				head->next = head->next->next;
				// Advances tail to current tail node.
				tail2 = tail2->next;
				// End current list with nodes >= x.
				tail2->next = NULL;
			}
		}
		// Join the two lists, smaller in front.
		head->next = head2->next;
		// Get head points to the right node.
		head = head1->next;

		// Clean dummy heads.
		delete head1;
		delete head2;
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

	l.partition(4);

	cout << "Test case 1 returns "
	     << (l.is_equal(&tgt) ? "True" : "False")
	     << endl;


	return 0;
}
