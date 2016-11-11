// Problem description:
// Sort a linked list in O(nlogn) time using constant space complexity.


// Idea:
// 1. Merge sort.
// 2. Fast/slow pointer to find the middle element.
// 3. Sort first half and second half, and merge them.


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

	void sort()
	{
		head = sort_list(head);
	}

	ListNode* sort_list(ListNode* head)
	{
		if(!head || !head->next)
			return head;

		ListNode* fast = head, *slow = head;
		while(fast->next && fast->next->next)
		{
			slow = slow->next;
			fast = fast->next->next;
		}
		fast = slow;
		slow = slow->next;
		fast->next = NULL;

		fast = sort_list(head);
		slow = sort_list(slow);
		return merge(fast, slow);
	}

	ListNode* merge(ListNode* head1, ListNode* head2)
	{
		ListNode* res = new ListNode(-1);
		ListNode* cur = res;
		while(head1 && head2)
		{
			if(head1->val < head2->val)
			{
				cur->next = head1;
				head1 = head1->next;
			}
			else
			{
				cur->next = head2;
				head2 = head2->next;
			}
			cur = cur->next;
		}

		if(head1)
			cur->next = head1;
		if(head2)
			cur->next = head2;
		ListNode* head = res->next;
		delete res;
		return head;
	}

	void print()
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

	l.sort();

	cout << "Test case 1 returns "
	     << (l.is_equal(&tgt) ? "True" : "False")
	     << endl;


	return 0;
}

