// Problem description:
// Given a singly linked list L: L0->L1->...->Ln-1->Ln,
// reorder it to: L0->Ln->L1->Ln-1->...

// You must do this in-place without altering the node's values.

// For example:
// Given {1,2,3,4}, reorder it to {1,4,2,3}.


// Idea:
// 1. Find the mid,
// 2. Reverse the right half,
// 3. Reorder one by one.



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

	ListNode* find_mid(ListNode* head)
	{
		ListNode* fast = head;
		ListNode* slow = head;
		while(fast && fast->next)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		return slow;
	}

	ListNode* reverse_list(ListNode* head)
	{
		if(!head)
			return head;
		ListNode* pre = head, *cur = head->next;
		while(cur)
		{
			ListNode* tmp = cur->next;
			cur->next = pre;
			pre = cur;
			cur = tmp;
		}
		head->next = NULL;
		return pre;
	}

	void reorder_list()
	{
		ListNode* mid = find_mid(head);
		// cout << "mid: " << mid->val << endl;
		ListNode* right = reverse_list(mid);

		ListNode* left = head;

		while(right && right->next)
		{
			ListNode* tmp = right;
			right = right->next;
			tmp->next = left->next;
			left->next = tmp;
			left = left->next->next;
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
	for(int i = 0; i < 4; ++i)
		l.add_last(new ListNode(i+1));

	LinkedList tgt;
	int val[] = { 1, 4, 2, 3 };
	for(int i = 0; i < sizeof(val) / sizeof(val[0]); ++i)
		tgt.add_last(new ListNode(val[i]));

	l.reorder_list();

	cout << "Test case 1 returns "
	     << (l.is_equal(&tgt) ? "True" : "False")
	     << endl;


	return 0;
}

