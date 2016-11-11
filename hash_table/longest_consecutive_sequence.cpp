// Problem description:
// Given an unsorted array of integers, find the length of the longest 
// consecutive elements sequence.
// For example,
// Given [100, 4, 200, 1, 3, 2],
// The longest consecutive elements sequence is [1,2,3,4]. Return its length: 4.
// You algorithm should run in O(n) complexity.
//
// Idea: Use hash table to remember if a number exists.
// 1. For each number A[i] in the array, use hash table to find if A[i]+1 
//    or A[i-1] exists, and record each length.
// 2. Update each scan with max length.



#include <iostream>
#include <vector>

using namespace std;








int main()
{

	cout << "Test case returns "
	     << (   ? "True" : "False")
	     << endl;




	return 0;
}

