// Problem description:
// Given a binary tree, determine if it is a valid binary search tree (BST).
// Assume a BST is defined as follows:
//   * The left subtree of a node contains only nodes with keys less than the 
//     node's key.
//   * The right subtree of a node contains only nodes with keys greater than
//     the node's key.
//   * Both the left and right subtrees must also be binary search trees.

// Idea:
// 1. Inorder traversal.
// 2. Remember previous value, if greater than current node, return false.



#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


bool validate_bst(TreeNode* root, int& cur_max)
{
	// For leaf nodes, return true.
	if(!root)
		return true;
	// If left subtree returns true, 
	// use cur_max record it's largest value.
	if(!validate_bst(root->left, cur_max))
		return false;
	// cur_max (records previous node value)
	// cannot be greater than current root.
	if(cur_max >= root->val)
		return false;
	// This actually records the previous value.
	cur_max = root->val;
	// If right subtree returns true, return true.
	return validate_bst(root->right, cur_max);
}

bool is_valid_bst(TreeNode* root)
{
	int cur_max = INT_MIN;
	return validate_bst(root, cur_max);
}


int main()
{

	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);

	cout << "Test case 1 returns "
	     << (is_valid_bst(root) == false ? "True" : "False")
	     << endl;
	delete root->left;
	delete root->right;
	delete root;

	root = new TreeNode(2);
	root->left = new TreeNode(1);
	root->right = new TreeNode(3);

	cout << "Test case 2 returns "
	     << (is_valid_bst(root) == true ? "True" : "False")
	     << endl;
	delete root->left;
	delete root->right;
	delete root;



	return 0;
}

