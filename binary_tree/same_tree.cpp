// Problem description:
// Given two binary trees, write a function to check if they are equal or not.
// Two binary trees are equal if they are structurally identical and the nodes
// have the same value.



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
	BinaryTree bt1, bt2, bt3;

	vector<int> nums { 1, 3, 5, 2, 4, 6, 9, 7, 8 };

	for(int i = 0; i < nums.size(); ++i)
	{
		bt1.add_node(nums[i]);
		bt2.add_node(nums[i]);
		bt3.add_node(nums[i]);
	}
	bt3.add_node(10);
	

	cout << "Same tree test case 1 returns "
	     << (bt1.is_same_tree(&bt2) == true ? "True" : "False")
	     << endl;

	cout << "Same tree test case 2 returns "
	     << (bt1.is_same_tree(&bt3) == false ? "True" : "False")
	     << endl;

	return 0;
}

