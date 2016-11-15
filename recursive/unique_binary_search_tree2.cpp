// Problem description:
// Given n, generate all structurally unique BST's (binary search trees) that 
// store values 1..n?
// For example,
// Given n = 3, your program should return all 5 unique BST's shown below.
// 1        3    3     2     1
//  \      /    /     / \     \
//   3    2    2     1   3     2
//  /    /      \               \
// 2    1        1               3

// Idea:
// Define f(n) to be the number of BST's of n. Take n = 3 as an example:
// 1. If let 1 be the root, left subtree can have 0 node, right subtree can 
//    have 2 nodes. The combination of left/right subtree is f(0)*f(2) = 2.
// 2. If let 2 be the root, left subtree can only be 1, right subtree can only 
//    be 3: f(1)*f(1) = 1.
// 3. If let 3 be the root, same as case 1.

// In summary:
// 1. f(0) = 1
// 2. f(n) = f(0)*f(n-1) + f(1)*f(n-2) + ... + f(n-2)*f(1) + f(n-1)*f(0).

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<TreeNode*> gen_bst(int min, int max)
{
	vector<TreeNode*> ret;
	if(min > max)
	{
		ret.push_back(NULL);
		return ret;
	}
	for(int i = min; i <= max; ++i)
	{
		vector<TreeNode*> left_subtree = gen_bst(min, i - 1);
		vector<TreeNode*> right_subtree = gen_bst(i + 1, max);
		for(int j = 0; j < left_subtree.size(); ++j)
		{
			for(int k = 0; k < right_subtree.size(); ++k)
			{
				TreeNode* root = new TreeNode(i);
				root->left = left_subtree[j];
				root->right = right_subtree[k];
				ret.push_back(root);
			}
		}
	}

	return ret;
}

vector<TreeNode*> generate_trees(int n)
{
	if(n == 0)
		return {};
	return gen_bst(1, n);
}


// Here to ease the test case for generated BST, add serialization 
// of BST, which is also a problem leetcode provides.

void serialize(TreeNode* root, ostringstream &out)
{
	if(root)
	{
		out << root->val << ' ';
		serialize(root->left, out);
		serialize(root->right, out);
	}
	else
		out << "# ";
}

string serialize(TreeNode* root)
{
	ostringstream out;
	serialize(root, out);
	return out.str();
}


int main()
{
	int n = 3;
	auto res = generate_trees(n);

	vector<string> ans;
	for(int i = 0; i < res.size(); i++)
		ans.push_back(serialize(res[i]));

	vector<string> bsts {
		"1 # 2 # 3 # # ",
		"1 # 3 2 # # # ",
		"2 1 # # 3 # # ",
		"3 1 # 2 # # # ",
		"3 2 1 # # # # ",
	};

	cout << "Test case 1 returns "
         << ((ans.size() == bsts.size() &&
              ans[0] == bsts[0] &&
              ans[1] == bsts[1] &&
              ans[2] == bsts[2] &&
              ans[3] == bsts[3] &&
              ans[4] == bsts[4]) ? "True" : "False")
         << endl;
	
	return 0;
}

