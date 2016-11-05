// Given an array of strings, group anagrams together.
// For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
// Return:
// [
//    ["ate", "eat", "tea"],
//    ["nat", "tan"],
//    ["bat"]
// ]


#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<vector<string> > group_anagrams(vector<string>& strs)
{
	if(strs.size() == 0)
		return {};
	vector<vector<string> > ans;
	if(strs.size() == 1)
	{
		ans.push_back(strs);
		return ans;
	}

	// Map each word to its target index in the vector
	map<string, int> m;
	int word_cnt = 0;
	for(int i = 0; i < strs.size(); ++i)
	{
		string tmp = strs[i];
		sort(tmp.begin(), tmp.end());
		auto it = m.find(tmp);
		// If met new anagram, record its position and insert it to ans.
		// Update next anagram position by word_cnt.
		if(it == m.end())
		{
			m.insert(pair<string, int>(tmp, word_cnt));
			vector<string> newstr { strs[i] };
			ans.push_back(newstr);
			++word_cnt;
		}
		else // If already have this anagram, push it in.
		{
			int index = it->second;
			ans[index].push_back(strs[i]);
		}
	}

	return ans;
}

int main()
{
	vector<string> strs { "eat", "tea", "tan", "ate", "nat", "bat" };
	auto res = group_anagrams(strs);
	cout << "Test case one returns "
	     << ((res.size() == 3 &&
	     	  res[0].size() == 3 && 
	     	  res[0][0] == "eat" && res[0][1] == "tea" && res[0][2] == "ate" &&
	     	  res[1].size() == 2 &&
	     	  res[1][0] == "tan" && res[1][1] == "nat" && 
	     	  res[2].size() == 1 &&
	     	  res[2][0] == "bat") ? "True" : "False")
	     << endl;

	return 0;
}


