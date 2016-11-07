// Problem description:
// Given a sorted linked list, delete all duplicates such that each element 
// appear only once.

// For example:
// Given 1->1->2, return 1->2.
// Given 1->1->2->3->3, return 1->2->3.


// Idea:
// 1. Check current node's and the next one's values
//    a) If they are the same, update current node's next pointer.
//    b) If not, let current pointer advance.



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

	void delete_duplicates()
	{
		ListNode* p = head;
		while(p)
		{
			ListNode* n = p->next;
			if(n && p->val == n->val)
				p->next = n->next;
			else
				p = p->next;
		}
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
	LinkedList l, tgt;

	for(int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < 3; ++j)
			l.add_last(new ListNode(i+1));
		tgt.add_last(new ListNode(i+1));
	}

	l.delete_duplicates();
	
	cout << "Test case 1 returns "
	     << (l.is_equal(&tgt) ? "True" : "False")
	     << endl;


	return 0;
}

