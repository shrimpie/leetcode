// Problem description:
// Given a binary tree, flatten it it a linked list in-place.

// For example,
// Given
//      1
//     / \
//    2   5
//   / \   \
//  3   4   6
// 
// The flattened tree should look like:
// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
//          \
//           6



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

	void flatten()
	{
		flatten(root);
	}

	TreeNode* flatten(TreeNode* root)
	{
		if(!root)
			return NULL;
		TreeNode* left_tail = flatten(root->left);
		TreeNode* right_tail = flatten(root->right);

		if(root->left)
		{
			// If left subtree exists, then append root->right to the left list,
			// and connect left_tail->right to root->right.
			// also set root->left to NULL.
			TreeNode* tmp = root->right;
			root->right = root->left;
			root->left = NULL;
			left_tail->right = tmp;
		}
		// If the right subtree exists, that's current root's right tail.
		if(right_tail)
			return right_tail;
		// If the right subtree does not exist, 
		// then left tail becomes the right tail.
		if(left_tail)
			return left_tail;
		// If at leaf node, the left node itself becomes the right tail.
		return root;
	}

	void flatten_iter()
	{
		TreeNode* cur = root;
		while(cur)
		{
			// Here founds the left subtree, if none, pass.
			if(cur->left)
			{
				// If current left exists,
				// append rightmost node's right to current node's right 
				// subtree, and current right connects to current left.
				// Also set current left to NULL.
				TreeNode* p = cur->left;
				while(p->right)
					p = p->right;
				p->right = cur->right;
				cur->right = cur->left;
				cur->left = NULL;
			}
			// Do this thing for each node that has a left child.
			cur = cur->right;
		}
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
	BinaryTree bt1, bt2;

	vector<int> nums { 1, 3, 5, 2, 4, 6, 9, 7, 8 };
	vector<int> tgt { 1, 3, 2, 5, 4, 6, 9, 7, 8 };

	for(int i = 0; i < nums.size(); ++i)
	{
		bt1.add_node(nums[i]);
		bt2.add_node(nums[i]);
	}

	bt1.flatten();
	TreeNode* p = bt1.get_root();
	bool res = true;
	for(int i = 0; i < tgt.size() && p; ++i)
	{
		// cout << "p->val: " << p->val << endl;
		res &= (p && !p->left && p->val == tgt[i]);
		p = p->right;
	}

	cout << "Flatten tree test case 1 returns "
	     << (res ? "True" : "False")
	     << endl;

	bt2.flatten_iter();
	p = bt2.get_root();
	res = true;
	for(int i = 0; i < tgt.size() && p; ++i)
	{
		// cout << "p->val: " << p->val << endl;
		res &= (p && !p->left && p->val == tgt[i]);
		p = p->right;
	}

	cout << "Flatten tree test case 2 returns "
	     << (res ? "True" : "False")
	     << endl;

	

	return 0;
}

