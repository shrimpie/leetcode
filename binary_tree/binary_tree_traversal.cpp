// Problem description:
// Given a binary tree, return the inorder traversal of its nodes' values.
// For example:
// Given binary tree [1, null, 2, 3],
//  1 
//   \
//    2
//   /
//  3
// return [1,3,2].

// Note: recursive solution is trivial, could you do it iteratively?

// Idea:
// 1. 
// 2. 



#include <iostream>
#include <vector>
#include <stack>

using namespace std;

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

	vector<int> inorder_traverse_recur()
	{
		vector<int> node_vals;
		inorder_traverse(root, node_vals);
		return node_vals;
	}

	void inorder_traverse(TreeNode* root, vector<int>& node_vals)
	{
		if(!root)
			return;
		inorder_traverse(root->left, node_vals);
		node_vals.push_back(root->val);
		inorder_traverse(root->right, node_vals);
	}

	vector<int> preorder_traverse_iter()
	{
		vector<int> node_vals;
		TreeNode* cur = root;
		stack<TreeNode*> s;
		while(cur || !s.empty())
		{
			if(!cur)
			{
				// Current left substree done, go check right one.
				cur = s.top();
				s.pop();
			}
			// Every time meets a root, add its value.
			node_vals.push_back(cur->val);
			// If there is a right subtree, cache it.
			if(cur->right)
				s.push(cur->right);
			// Go search the left child.
			cur = cur->left;
		}
		return node_vals;
	}

	vector<int> inorder_traverse_iter()
	{
		vector<int> node_vals;
		TreeNode* cur = root;
		stack<TreeNode*> s;

		while(cur || !s.empty())
		{
			if(!cur)
			{
				// If cur is NULL, then you have traversed the left branch.
				// Save current root value and go check right branch.
				cur = s.top();
				s.pop();
				node_vals.push_back(cur->val);
				cur = cur->right;
			}
			else
			{
				// Find the left-most.
				s.push(cur);
				cur = cur->left;
			}
		}

		return node_vals;
	}

	vector<int> postorder_traverse_iter()
	{
		stack<TreeNode*> st;
		vector<int> res;
		if(!root)
			return res;

		// Push root in to make the stack non-empty,
		// and start the iteration.
		st.push(root);
		TreeNode* head = root;
		while(!st.empty())
		{
			// Get the top of each substree.
			TreeNode* top = st.top();
			// If meet leaf node, or current head is top node's child,
			// now you traversed the whole subtree pointing by top, and 
			// you can add it to result.
			if((!top->left && !top->right) || 
				top->right == head || top->left == head)
			{
				res.push_back(top->val);
				st.pop();
				// head points to previous top, 
				// that's the root node of next top.
				head = top;
			}
			// when meet intermediate nodes, keep cacheing it.
			// Notice the order, first right node, then left node,
			// then the stack will pop it out in the right order.
			else
			{
				if(top->right)
					st.push(top->right);
				if(top->left)
					st.push(top->left);
			}
		}

		return res;
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
	BinaryTree bt;

	vector<int> nums { 1, 3, 5, 2, 4, 6, 9, 7, 8 };

	for(int i = 0; i < nums.size(); ++i)
		bt.add_node(nums[i]);
	auto ans = bt.inorder_traverse_recur();
	ans = bt.inorder_traverse_iter();
	bool res = (ans.size() == nums.size());
	for(int i = 0; i < ans.size(); ++i)
		res &= (ans[i] == i + 1);

	cout << "Inorder traverse test case returns "
	     << (res ? "True" : "False")
	     << endl;

	ans = bt.preorder_traverse_iter();
	vector<int> preorder_vals { 1, 3, 2, 5, 4, 6, 9, 7, 8 };
	res = (ans.size() == preorder_vals.size());
	for(int i = 0; i < ans.size(); ++i)
		res &= (ans[i] == preorder_vals[i]);
	cout << "Preorder traverse tese case returns "
	     << (res ? "True" : "False")
	     << endl;

	ans = bt.postorder_traverse_iter();
	vector<int> postorder_vals { 2, 4, 8, 7, 9, 6, 5, 3, 1 };
	res = (ans.size() == postorder_vals.size());
	for(int i = 0; i < ans.size(); ++i)
		res &= (ans[i] == postorder_vals[i]);
	cout << "Postorder traverse tese case returns "
	     << (res ? "True" : "False")
	     << endl;

	return 0;
}

