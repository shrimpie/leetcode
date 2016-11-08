// Problem description:
// Two elements of a binary search tree (BST) are swapped by mistake.
// Recover the tree without changing its structure.
// Note:
// A solution using O(n) space is pretty straight forward. Could you devise a 
// constant space solution?

// Idea:
// 1. Inorder traversal, found the two swapped nodes.
// 2. Use two pointers to store the two nodes, another one to compare current pair.
// 3. Once traversed, swapped them back.

// Further notes:
// Check out "Morris In-order traversal using threading".

#include <iostream>
#include <vector>

using namespace std;


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void inorder_traverse(TreeNode* root, vector<TreeNode*>& p)
{
	if(!root)
		return;
	else
	{
		inorder_traverse(root->left, p);
		if(p[0] == NULL)
			p[0] = root;
		else
		{
			if(p[0]->val > root->val)
			{
				if(p[1] == NULL)
					p[1] = p[0];
				p[2] = root;
			}
			p[0] = root;
		}
		inorder_traverse(root->right, p);
	}
}

void recover_tree(TreeNode* root)
{
	vector<TreeNode*> p(3, NULL);
	// p[0]: pre; p[1]: first; p[1]: second.
	inorder_traverse(root, p);
	int v = p[1]->val;
	p[1]->val = p[2]->val;
	p[2]->val = v;

	return;
}



int main()
{

	TreeNode* root = new TreeNode(0);
	root->left = new TreeNode(1);

	recover_tree(root);

	cout << "Test case 1 returns "
	     << ((root && root->val == 1 && root->left && root->left->val == 0 && 
	     	  root->right == NULL) ? "True" : "False")
	     << endl;

	delete root->left;
	delete root;

	return 0;
}

