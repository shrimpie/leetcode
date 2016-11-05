// Given two numbers represented as strings, return multiplication of the 
// numbers as a string.

// Note:
// 1. The numbers can be arbitrarily large and are non-negative.
// 2. Converting the input string to integer is NOT allowed.
// 3. You should NOT use internal library such as BigInteger.


#include <iostream>
#include <vector>
using namespace std;



string multiply(string a, string b)
{
	if(a == "0" || b == "0")
		return "0";

	string ans = "";
	// Single array to store intermediate values.
	vector<int> result(a.size() + b.size(), 0);
	for(int i = a.size() - 1; i >= 0; --i)
	{
		for(int j = b.size() - 1; j >= 0; --j)
		{
			result[i+j+1] += (b[j] - '0') * (a[i] - '0');
		}
	}

	for(int i = result.size() - 1; i >= 0; --i)
	{
		if(result[i] >= 10)
		{
			result[i-1] += result[i] / 10;
			result[i] %= 10;
		}
	}

	// You want to erase the lending '0's.
	int i = 0;
	while(i < result.size() && result[i] == 0)
		++i;
	if(i == result.size())
		return "0";

	for(; i < result.size(); ++i)
		ans = ans.append(to_string(result[i]));

	return ans;
}



int main()
{
	string a = "12345678";
	string b = "987654321";

	cout << "Test case 1 returns "
	     << (multiply(a, b) == "12193262222374638" ? "True" : "False")
	     << endl;

	a = "0";
	b = "0";

	cout << "Test case 2 returns "
	     << (multiply(a, b) == "0" ? "True" : "False")
	     << endl;

	a = "19200";
	b = "0";

	cout << "Test case 3 returns "
	     << (multiply(a, b) == "0" ? "True" : "False")
	     << endl;

	a = "0";
	b = "10190191";

	cout << "Test case 4 returns "
	     << (multiply(a, b) == "0" ? "True" : "False")
	     << endl;

	a = "272872";
	b = "282829";

	cout << "Test case 5 returns "
	     << (multiply(a, b) == "77176114888" ? "True" : "False")
	     << endl;


	return 0;
}