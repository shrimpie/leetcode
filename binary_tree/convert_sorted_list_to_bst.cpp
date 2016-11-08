// Problem description:

// Given a singly linked list where elements are sorted in ascending order, convert it to 
// a height balanced BST.

// Idea:
// 1. This one is a little bit hard to understand, but try anyway.
// 2. This one uses recursive calling's magic to add node one by one.

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct ListNode {
	int val;
	ListNode * next;
	ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class BinaryTree
{
private:
	TreeNode* root;

	void add_node(int v, TreeNode* n)
	{
		if(v <= n->val)
		{
			if(n->left)
				add_node(v, n->left);
			else
				n->left = new TreeNode(v);
		}
		else
		{
			if(n->right)
				add_node(v, n->right);
			else
				n->right = new TreeNode(v);
		}
	}

public:

	BinaryTree() : root(NULL) {}

	BinaryTree(vector<int>& nums)
	{
		if(nums.size() < 1)
			root = NULL;
		root = add_to_tree(nums, 0, nums.size() - 1);
	}

	BinaryTree(ListNode* head)
	{
		if(!head)
			root = NULL;

		int n = 0;
		ListNode* p = head;
		while(p)
		{
			++n;
			p = p->next;
		}

		root = convert_sorted_list_to_bst(head, 0, n - 1);
	}

	TreeNode* add_to_tree(vector<int>& vals, int start, int end)
	{
		if(end < start)
			return NULL;
		int mid = start + (end - start)/2;
		TreeNode* n = new TreeNode(vals[mid]);
		n->left = add_to_tree(vals, start, mid - 1);
		n->right = add_to_tree(vals, mid + 1, end);

		return n;
	}

	TreeNode* convert_sorted_list_to_bst(ListNode* &head, int start, int end)
	{
		if(start > end)
			return NULL;

		int mid = start + (end - start) / 2;
		TreeNode* left_child = convert_sorted_list_to_bst(head, start, mid - 1);
		TreeNode* parent = new TreeNode(head->val);
		parent->left = left_child;
		head = head->next;
		parent->right = convert_sorted_list_to_bst(head, mid + 1, end);

		return parent;
	}

	TreeNode* get_root()
	{
		return root;
	}

	void add_node(int v)
	{
		if(!root)
			root = new TreeNode(v);
		else
			add_node(v, root);
	}

	bool is_same_tree(BinaryTree* tree2)
	{
		TreeNode* root2 = tree2->get_root();
		return is_same_tree(root, root2);
	}

	bool is_same_tree(TreeNode* p, TreeNode* q)
	{
		if(!p && !q)
			return true;
		else if(p && !q)
			return false;
		else if(!p && q)
			return false;
		return is_same_tree(p->left, q->left) && 
		       is_same_tree(p->right, q->right) &&
		       (p->val == q->val);
	}


	~BinaryTree()
	{
		free_node(root);
	}

	void free_node(TreeNode* leaf)
	{
		if(leaf)
		{
			free_node(leaf->left);
			free_node(leaf->right);
			delete leaf;
		}
	}
};



int main()
{

	vector<int> nums1 { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> nums2 { 5, 2, 7, 1, 3, 6, 8, 4, 9 };

	ListNode* head = new ListNode(-1);
	ListNode* p = head;

	for(int i = 0; i < nums1.size(); ++i)
	{
		p->next = new ListNode(nums1[i]);
		p = p->next;
	}

	BinaryTree bt1(nums1), bt2, bt3(head->next);

	for(int i = 0; i < nums2.size(); ++i)
		bt2.add_node(nums2[i]);
	

	cout << "Convert sorted array to BST test case 1 returns "
	     << (bt1.is_same_tree(&bt2) == true ? "True" : "False")
	     << endl;

	cout << "Convert sorted list to BST test case 1 returns "
	     << (bt1.is_same_tree(&bt3) == true ? "True" : "False")
	     << endl;


	while(head)
	{
		p = head->next;
		delete head;
		head = p;
	}


	return 0;
}

