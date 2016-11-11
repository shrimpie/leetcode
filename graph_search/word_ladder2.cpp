// Problem description:

// Given two words (beginWord and endWord), and a dictionary's word list, 
// find all shortest transformation sequence(s) from beginWord to 
// endWord, such that:
// 1. Only one letter can be changed at a time
// 2. Each intermediate word must exist in the word list

// For example,
// Given:
// beginWord = "hit"
// endWord = "cog"
// wordList = ["hot", "dot", "dog", "lot", "log"]
// Return
// [
//    ["hit", "hot", "dot", "dog", "cog"],
//    ["hit", "hot", "lot", "log", "cog"]
// ]
//

// Note:
//   * All words have the same length.
//   * All words contain only lowercase alphabetic characters.


// Idea:
// 1. Breadth first search, use two unordered_set's to implement it.
// 2. From the start word, find its next level words in the word list, check if
//    the end word is there.
//    a) If not, find all next level words in the word list.
//    b) Remember to clear the word in previous level so the search won't meet 
//       cycles.
//    c) Here we modifies the word list by erasing already visited words. If 
//       this is not allowed, you can implement a mapping of each word 
//       indicating if the word has been search before.
// 3. Use a map to record each word transformation, and at last reverse the 
//    process to find all possible paths.
// 



#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;


void find_neighbors(string str, unordered_set<string>& word_list, 
                    unordered_set<string>& next_level,
                    unordered_map<string, vector<string> >& mp)
{
	int sz = str.size();
	string s = str;
	for(int i = 0; i < sz; ++i)
	{
		s = str;
		for(char j = 'a'; j <= 'z'; ++j)
		{
			s[i] = j;
			if(word_list.count(s))
			{
				next_level.insert(s);
				mp[s].push_back(str);
			}
		}
	}
}

void output(string& start, string last, vector<string>& path, 
	        vector<vector<string> >& res, 
	        unordered_map<string, vector<string> >& mp)
{
	if(last == start)
	{
		reverse(path.begin(), path.end());
		res.push_back(path);
		reverse(path.begin(), path.end());
	}
	else
	{
		for(int i = 0; i < mp[last].size(); ++i)
		{
			path.push_back(mp[last][i]);
			output(start, mp[last][i], path, res, mp);
			path.pop_back();
		}
	}
}


vector<vector<string> > find_ladders(string start, string end, 
	                                 unordered_set<string>& word_list)
{
	unordered_map<string, vector<string> > mp;
	vector<vector<string> > res;
	vector<string> path;

	word_list.insert(start);
	word_list.insert(end);


	unordered_set<string> cur_level;
	cur_level.insert(start);
	unordered_set<string> next_level;
	path.push_back(end);

	while(true)
	{
		for(auto s : cur_level)
			word_list.erase(s);
		for(auto s : cur_level)
			find_neighbors(s, word_list, next_level, mp);

		if(next_level.empty())
		{
			
			return res;
		}

		if(next_level.count(end))
		{
			output(start, end, path, res, mp);
			return res;
		}

		cur_level.clear();
		cur_level = next_level;
		next_level.clear();
	}

	return res;
}



int main()
{
	string start = "hit";
	string end = "cog";
	unordered_set<string> word_list { "hot", "dot", "dog", "lot", "log" };

	auto ans = find_ladders(start, end, word_list);
	// cout << ans.size() << endl;

	cout << "Test case 1 returns "
	     << ((ans.size() == 2 && ans[0].size() == 5 && ans[1].size() == 5 &&
	     	  ans[0][0] == "hit" && ans[0][1] == "hot" && ans[0][2] == "dot" && 
	          ans[0][3] == "dog" && ans[0][4] == "cog" &&
	          ans[1][0] == "hit" && ans[1][1] == "hot" && ans[1][2] == "lot" && 
	     	  ans[1][3] == "log" && ans[1][4] == "cog")
	          ? "True" : "False")
	     << endl;

	return 0;
}

