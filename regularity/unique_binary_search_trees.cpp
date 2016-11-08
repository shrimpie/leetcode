// Problem description:
// Given n, how many structurally unique BST's (binary search trees) that store
// values 1..n?
// For example,
// Given n = 3, there are a total of 5 unique BST's.
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
#include <vector>

using namespace std;


int num_trees(int n)
{
	vector<int> num_bst(n+1, 0);
	num_bst[0] = 1;

	for(int i = 1; i <= n; ++i)
	{
		for(int j = 0; j < i; ++j)
			num_bst[i] += num_bst[j] * num_bst[i-1-j];
	}
	return num_bst[n];
}


int main()
{
	vector<int> nums { 1, 2, 3, 4, 5, 6, 7 };
	vector<int> tgt { 1, 2, 5, 14, 42, 132, 429 };
	for(int i = 0; i < nums.size(); ++i)
	{
		cout << "Test case " << i + 1 << " returns "
	         << (num_trees(nums[i]) == tgt[i] ? "True" : "False")
	         << endl;
	}
	




	return 0;
}

