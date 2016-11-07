// Problem description:
// Given a sorted linked list, delete all nodes that have duplicate numbers, 
// leaving only distinct numbers from the original list.

// For example:
// Given 1->2->3->3->4->4->5, return 1->2->5.
// Given 1->1->1->2->3, return 2->3.


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
		if(!head || !head->next)
			return;

		ListNode* hc = new ListNode(-1);
		hc->next = head;
		ListNode* pre = hc, *cur = head;
		while(cur)
		{
			bool found_dupli = false;
			while(cur->next && cur->val == cur->next->val)
			{
				// Current round of duplicates.
				found_dupli = true;
				ListNode* tmp = cur;
				cur = cur->next;
				delete tmp;
			}
			if(found_dupli)
			{
				// If found duplicates, jump over the duplicate ones.
				// Then you can next round of duplicates if there are some.
				ListNode* tmp = cur;
				cur = cur->next;
				delete tmp;
				continue;
			}
			// If no duplicates found, make pre points to the new next item.
			// Advances cur and pre too.
			pre->next = cur;
			pre = pre->next;
			cur = cur->next;
		}
		// There are occasions in which the last ones are all duplicates,
		// so the above pointers updates may not have the chance to execute,
		// so make sure pre points to the right node.
		pre->next = cur;
		head = hc->next;
		delete hc;
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
		// cout << "In destructor()" << endl;
		if(!head)
			return;

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
	}

	l.delete_duplicates();
	
	cout << "Test case 1 returns "
	     << (l.is_equal(&tgt) ? "True" : "False")
	     << endl;


	for(int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < 3; ++j)
			l.add_last(new ListNode(i+1));
	}
	l.add_last(new ListNode(6));
	tgt.add_last(new ListNode(6));

	l.delete_duplicates();
	
	cout << "Test case 2 returns "
	     << (l.is_equal(&tgt) ? "True" : "False")
	     << endl;



	return 0;
}

