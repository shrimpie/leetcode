// Problem description:
// The set [1,2,3,...,n] contains a total of n! unique permutations.
// By listing and labeling all of the permutations in order,
// we get the following sequence (i.e., for n = 3):
// 1. "123"
// 2. "132"
// 3. "213"
// 4. "231"
// 5. "312"
// 6. "321"

// Given n and k, return the kth permutation sequence.

// The logic here refers to below article.
// http://bangbingsyb.blogspot.com/2014/11/leetcode-permutation-sequence.html


#include <iostream>
#include <vector>

using namespace std;

string get_permutation(int n, int k) {
        
    string ret;
    vector<int> factorial(n, 1);
    vector<char> num(n, 1);
    
    for(int i = 1; i < n; ++i)
        factorial[i] = factorial[i-1] * i;
    
    for(int i = 0; i < n; ++i)
        num[i] = (i + 1) + '0';

    // Try one number that is exactly equals factorial[i],
    // and you'll get the idea that why --k.
    --k;
    for(int i = n; i >= 1; --i)
    {
    	// There are factorial[i-1] sequences for the ith number.
    	// j is used to find the number.
        int j = k / factorial[i-1];
        // Update k for next round.
        k %= factorial[i-1];
        ret.push_back(num[j]);
        // Erase the numbers so it is pointing to the right one using
        // the j index.
        num.erase(num.begin() + j);
    }
    
    return ret;
}


int main()
{
	int n[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int k[] = { 1, 2, 5, 14, 100, 500, 2990, 10000, 50000 };
	vector<string> seqs { "1", "21", "312", "3142", "51342", "516243", 
	                      "5174263", "28735461", "239574186" };

	for(int i = 0; i < sizeof(n)/sizeof(n[0]); ++i)
	{
		cout << "Test case " << i + 1 << " returns "
		     << (get_permutation(n[i], k[i]) == seqs[i] ? "True" : "False")
		     << endl;
	 }


	return 0;
}

