// Problem description:
// Given a non-negative number represented as an array of digits, plus one to 
// the number. The digits are stored such that the most significant digit is 
// at the head of the list.


// Idea:
// Elementary math.



#include <iostream>
#include <vector>

using namespace std;

vector<int> plus_one(vector<int>& digits)
{
    int carry = 1;
    vector<int> res(digits.size(), 0);
    for(int i = digits.size() - 1; i >= 0; --i)
    {
        carry += digits[i];
        res[i] = carry % 10;
        carry /= 10;
    }
    if(carry)
        res.insert(res.begin(), 1);
    return res;
}


int main()
{
	vector<int> number { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto ans = plus_one(number);

	cout << "Test case 1 returns "
	     << ((ans.size() == 9 &&
	     	  ans[0] == 1 && ans[1] == 2 && ans[2] == 3 && ans[3] == 4 && 
	     	  ans[4] == 5 && ans[5] == 6 && ans[6] == 7 && ans[7] == 9 &&
	     	  ans[8] == 0) ? "True" : "False")
	     << endl;

	return 0;
}

