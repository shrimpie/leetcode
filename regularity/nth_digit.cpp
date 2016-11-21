// Problem description:

// Find the nth digit of the infinite integer sequence 1,2,3,4,5,6,...

// Note:

// n is positive and will fit within the range of a 32-bit signed integer
// (n < 2^31).

// Idea:
// 1. There are 9 digits of single-digit number
// 2. There are 90 digits of double-digit number
// 3. There are 900 digits of three-digit number.
// ...
// 4. Find the target number's size, interval and then you got it.


#include <iostream>
#include <vector>

using namespace std;

int find_nth_digit(int n)
{
	long long len = 1, cnt = 9, start = 1;

	while(n > len * cnt)
	{
		n -= len * cnt;
		++len;
		cnt *= 10;
		start *= 10;
	}

	// `n - 1` is used to correctly locate the target number,
    // for example if n = 69, len = 3, start = 100, 
    // then n/len = 23, and 100 + 23 will be one larger than 
    // the target number 122, 100 .. 122 has 69 digits.
    // so decrement 1 first to make it move one step.
    // For n such that n % len != 0, the -1 will still locate 
    // the right number.

	start += (n - 1) / len;
	string t = to_string(start);
	return t[(n-1) % len] - '0';
}


int main()
{

	int n = 11111;

	cout << "Test case 1 returns "
	     << (find_nth_digit(n) == 0 ? "True" : "False")
	     << endl;



	return 0;
}

