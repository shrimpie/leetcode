// Problem description:
// Validate if a given string is numeric.
// Some examples:
// "0" => true
// " 0.1" => true
// "abc" => false
// "1 a" => false
// "2e10" => true

// Idea:
// 1. Collect all the states that are invalid.



#include <iostream>
#include <vector>

using namespace std;


bool is_number(string s)
{
	int len = s.size();
    int i = 0, e = len - 1;
    while (i <= e && isspace(s[i]))
        ++i;
    if (i > len - 1)
        return false;
        
    while (e >= i && isspace(s[e]))
        --e;
        
    // skip leading +/-
    if (s[i] == '+' || s[i] == '-')
        ++i;
        
    bool num = false; // is a digit
    bool dot = false; // is a '.'
    bool exp = false; // is a 'e'
    
    while (i <= e)
    {
        char c = s[i];
        if ( c >= '0' && c <= '9') // Met a digit
            num = true;
        else if (c == '.')         // Met a dot
        {
            if(exp || dot)         // If met a 'e' or dot before, false
                return false;
            dot = true;            // Set met a dot
        }
        else if (c == 'e')         // Met a 'e'
        {
            if(exp || !num)        // If met 'e' or met first 'e' before 
                return false;      // met a num, false
            exp = true;            // Set met a 'e'
            num = false;           // You can met a new num now.
        }
        else if (c == '+' || c == '-') // Met a sign again
        {
            if (s[i-1] != 'e')         // Should before a 'e'
                return false;          // Otherwise, false.
        }
        else                           // Other chars are invalid.
            return false;
        ++i;                           // Keep checking.
    }
    return num;
}





int main()
{
	vector<string> nums { "0", " 0.1", "abc", "1 a", "2e10" };
	vector<bool> tgt { true, true, false, false, true };

	for(int i = 0; i < nums.size(); ++i)
	{
		cout << "Test case " << i + 1 << "returns "
		     << (is_number(nums[i]) == tgt[i] ? "True" : "False")
		     << endl;
	}

	return 0;
}

