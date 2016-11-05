// Given a collection of distinct numbers, return all possible permutations.


#include <iostream>
#include <vector>

using namespace std;


// 1. The swap idea is like for the first position, you can choose each number.
//    When the first is fixed, permute all remaining numbers.
// 2. The same idea applies to the next level with one item picked already.
// Example:
// [1, 2, 3]
// First round: 1 [2, 3]
//            : 1 [2 [3]], add to result.
//            :  1 [3 [2]], add to result.
// Swap 1 and 2: 2 [1, 3]
//             : 2 [1 [3]], add to result.
//             : 2 [3 [1]], add to result.
// Swap 1 and 3, now you get the idea..
//    
void perm(vector<int> num, int k, int n, vector<vector<int> >& res)
{
	if( k == n)
		res.push_back(num);
	else
	{
		for(int i = k; i <=n; ++i)
		{
			swap(num[k], num[i]);
			perm(num, k+1, n, res);
			swap(num[k], num[i]);
		}
	}
}

vector<vector<int> > permute(vector<int>& num)
{
	vector<vector<int> > res;
	perm(num, 0, num.size() - 1, res);

	return res;
}

// Well, there is a similar way in which you can keep inserting
// new elements and make the final permutation.
// The idea is pretty straight-forward.
vector<vector<int> > permute2(vector<int>& num)
{
	vector<vector<int> > all_pers;
	if(num.empty())
		return all_pers;
	// Insert the first element to start.
	all_pers.push_back(vector<int>(1, num[0]));
	for(int i = 1; i < num.size(); ++i)
	{
		int n = all_pers.size();
		for(int j = 0; j < n; ++j)
		{
			// For each of permutations currently got,
			// Insert next number 
			for(int k = 0; k < all_pers[j].size(); ++k)
			{
				vector<int> per = all_pers[j];
				per.insert(per.begin() + k, num[i]);
				all_pers.push_back(per);
			}
			// Don't forget the last position of jth.
			all_pers[j].push_back(num[i]);
		}
	}
	return all_pers;
}


int main()
{

	vector<int> a { 1, 2, 3 };
	auto res = permute(a);
	cout << "Test case 1 returns: "
	<< ((res[0][0] == 1 && res[0][1] == 2 && res[0][2] == 3 &&
	   	 res[1][0] == 1 && res[1][1] == 3 && res[1][2] == 2 &&
	   	 res[2][0] == 2 && res[2][1] == 1 && res[2][2] == 3 &&
	   	 res[3][0] == 2 && res[3][1] == 3 && res[3][2] == 1 &&
	   	 res[4][0] == 3 && res[4][1] == 2 && res[4][2] == 1 &&
	   	 res[5][0] == 3 && res[5][1] == 1 && res[5][2] == 2 ) ? "True" : "False")
	<< endl;

	vector<int> b { 1, 2, 3 };
	res = permute2(a);
	cout << "Test case 2 returns: "
	<< ((res[0][0] == 1 && res[0][1] == 2 && res[0][2] == 3 &&
	   	 res[1][0] == 2 && res[1][1] == 1 && res[1][2] == 3 &&
	   	 res[2][0] == 3 && res[2][1] == 1 && res[2][2] == 2 &&
	   	 res[3][0] == 1 && res[3][1] == 3 && res[3][2] == 2 &&
	   	 res[4][0] == 3 && res[4][1] == 2 && res[4][2] == 1 &&
	   	 res[5][0] == 2 && res[5][1] == 3 && res[5][2] == 1 ) ? "True" : "False")
	<< endl;

	return 0;
}


