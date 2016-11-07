// Problem description:
// Implement int sqrt(int x).
// Compute and return the square root of x.

// Idea:
// 1. Newton method, very cute.
// 2. Of course, you can use binary search too.



#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int my_sqrt(int x)
{
	if(x == 0 || x == 1)
		return x;

	double pre;
	double cur = 1;
	do
	{
		pre = cur;
		cur = (pre + x/pre) / 2;
	}while(abs(pre - cur) > 0.00001);

	return int(cur);
}


int main()
{
	vector<int> nums { 1, 20, 450, 4890, 48390, 584902 };
	vector<int> tgt { 1, 4, 21, 69, 219, 764 };
	for(int i = 0; i < nums.size(); ++i)
	{
		cout << "Test case " << i + 1 << " returns "
	         << (my_sqrt(nums[i]) == tgt[i] ? "True" : "False")
	         << endl;
	}

	return 0;
}

