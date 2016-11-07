// Problem description:
// Given two binary strings, return their sum (also a binary string).
// For example,
// a = "11"
// b = "1"
// Return "100".

// Idea:
// 1. Basically same idea here.



#include <iostream>
#include <vector>

using namespace std;

string addBinary(string a, string b)
{
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    string sum;
    int carry = 0;
    int n = max(a.size(), b.size());
    for(int i = 0; i < n; ++i)
    {
        if(i < a.size())
            carry += a[i] - '0';
        if(i < b.size())
            carry += (b[i] - '0');
        sum.push_back(carry % 2 + '0');
        carry /= 2;
    }
    if(carry)
        sum.push_back('1');
    reverse(sum.begin(), sum.end());

    return sum;    
}


int main()
{
	vector<string> a { "11", "1111010101", "10101010010101010" };
	vector<string> b { "1", "1111111111", "101010100101" };
	vector<string> tgt { "100", "11111010100", "10101111101001111" };
	for(int i = 0; i < a.size(); ++i)
	{
		cout << "Test case " << i + 1 << " returns "
	         << (addBinary(a[i], b[i]) == tgt[i] ? "True" : "False")
	         << endl;
	}
	
	return 0;
}

