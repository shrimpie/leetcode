// Problem description:
// Reverse a singly linked list.

// Idea:
// You have to understand this so well that you can directly write code in your
// head.

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

	void reverse_iter()
	{
		ListNode* reversed = NULL;
		//
		while(head)
		{
			// Remember rest of the list.
			ListNode* remain = head->next;
			// Reverse current node and connects to already reversed.
			head->next = reversed;
			// Update reversed list.
			reversed = head;
			// Advances head to next node.
			head = remain;
		}
		head = reversed;
	}

	void reverse_recur()
	{
		head = reverse_recur(head);
	}

	ListNode* reverse_recur(ListNode* head)
	{
		// Return last node if there is one.
		// Base condition.
		if(!head || !head->next)
			return head;
		// Remember next node.
		ListNode* n = head->next;
		// Mark the node (head points to) the end node of current level.
		head->next = NULL;
		// Get the reversed list head.
		ListNode* rest = reverse_recur(n);
		// Make the next node points to current level end node.
		n->next = head;

		// The last will be save in rest and sent up level by level.
		return rest;
	}

	void print_list()
	{
		cout << "The list contains: ";
		ListNode* n = head;
		while(n)
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
	LinkedList l, tgt;
	for(int i = 0; i < 5; ++i)
	{
		l.add_last(new ListNode(i+1));
		tgt.add_front(new ListNode(i+1));
	}

	l.reverse_iter();

	cout << "Test case 1 returns "
	     << (l.is_equal(&tgt) ? "True" : "False")
	     << endl;

	l.reverse_recur();
	tgt.reverse_iter();
	cout << "Test case 2 returns "
	     << (l.is_equal(&tgt) ? "True" : "False")
	     << endl;


	return 0;
}

