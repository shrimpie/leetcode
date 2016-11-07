// Problem description:
// Given a string containing only digits, restore it by returning all possible 
// valid IP address combinations.
// For example:
// Given "25525511135",
// Return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)

// Idea:



#include <iostream>
#include <vector>

using namespace std;

bool is_valid_num(string s)
{
	if(s.empty() || s.size() > 3)
		return false;
	if(s[0] == '0' && s.size() != 1)
		return false;
	if(s.size() == 3 && stoi(s) > 255)
		return false;
	return true;
}


void find_ip_addr(string &s, int index, vector<string>& ip_num, 
	              vector<string> & ip_comb)
{
	if(ip_num.size() == 4)
	{
		if(index == s.size())
		{
			string ip_addr = ip_num[0];
			for(int i = 1; i < 4; ++i)
				ip_addr.append("." + ip_num[i]);
			ip_comb.push_back(ip_addr);
		}
		return;
	}
	string cur_num;
	for(int i = index; i < s.size() && i < index + 3; ++i)
	{
		cur_num.push_back(s[i]);
		if(is_valid_num(cur_num))
		{
			ip_num.push_back(cur_num);
			find_ip_addr(s, i + 1, ip_num, ip_comb);
			ip_num.pop_back();
		}
	}
}


vector<string> restore_ip_addresses(string s)
{
	vector<string> ip_comb;
	vector<string> ip_num;
	find_ip_addr(s, 0, ip_num, ip_comb);
	return ip_comb;
}



int main()
{
	string s = "25525511135";
	auto ans = restore_ip_addresses(s);
	cout << "Test case 1 returns "
	     << ((ans.size() == 2 &&
	     	  ans[0] == "255.255.11.135" && 
	     	  ans[1] == "255.255.111.35")
	     	  ? "True" : "False")
	     << endl;




	return 0;
}

