// Problem description:
// Given a string of numbers and operators, return all possible results from 
// computing all the different possible ways to group numbers and operators. 
// The valid operators are +, -, and *.

// Example 1
// Input: "2-1-1"
// ((2-1)-1) = 0
// (2-(1-1)) = 2
// Output: [0, 2].

// Idea:
// 1. Recursively deal with left and right part.
// 2. Left and right are separated by operators.



#include <iostream>
#include <vector>

using namespace std;



vector<int> diff_ways_to_compute(string input)
{
	vector<int> res;
	for(int i = 0; i < input.size(); ++i)
	{
		if(input[i] == '+' || input[i] == '-' || input[i] == '*')
		{
			vector<int> left = diff_ways_to_compute(input.substr(0, i));
			vector<int> right = diff_ways_to_compute(input.substr(i+1));
			for(int j = 0; j < left.size(); ++j)
			{
				for(int k = 0; k < right.size(); ++k)
				{
					if(input[i] == '+')
						res.push_back(left[j] + right[k]);
					else if(input[i] == '-')
						res.push_back(left[j] - right[k]);
					else
						res.push_back(left[j] * right[k]);
				}
			}
		}
	}
	if(res.empty())
		res.push_back(atoi(input.c_str()));
	return res;
}




int main()
{
	string input = "2-1-1";

	auto ans = diff_ways_to_compute(input);

	cout << "Test case 1 returns "
	     << ((ans.size() == 2 && 
	     	  ((ans[0] == 0 && ans[1] == 2) || (ans[1] == 0 && ans[0] == 2)))
	     	  ? "True" : "False")
	     << endl;




	return 0;
}

