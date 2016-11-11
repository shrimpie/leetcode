// Problem description:
// Given two words (beginWord and endWord), and a dictionary's word list, 
// find the length of shortest transformation sequence from beginWord to 
// endWord, such that:
// 1. Only one letter can be changed at a time
// 2. Each intermediate word must exist in the word list

// For example,
// Given:
// beginWord = "hit"
// endWord = "cog"
// wordList = ["hot", "dot", "dog", "lot", "log"]
// As one shortest transformation is "hit"->"hot"->"dot"->"dog"->"cog",
// return its length 5.

// Note:
//   * Return 0 if there is no such transformation sequence.
//   * All words have the same length.
//   * All words contain only lowercase alphabetic characters.


// Idea:
// 1. Breadth first search, use queue to implement it.
// 2. From the start word, find its next level words in the word list, check if
//    the end word is there.
//    a) If not, find all next level words in the word list.
//    b) Remember to clear the word in previous level so the search won't meet 
//       cycles.
//    c) Here we modifies the word list by erasing already visited words. If 
//       this is not allowed, you can implement a mapping of each word 
//       indicating if the word has been search before.
//       



#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;


vector<string> find_neighbors(string s, unordered_set<string>& word_list)
{
	vector<string> nghbs;
	for(int i = 0; i < s.size(); ++i)
	{
		char c = s[i];
		for(int j = 0; j < 26; ++j)
		{
			if(c == 'a' + j)
				continue;
			s[i] = 'a' + j;
			if(word_list.count(s))
			{
				nghbs.push_back(s);
				word_list.erase(s);
			}
		}
		s[i] = c;
	}
	return nghbs;
}

int ladder_length(string start, string end, unordered_set<string>& word_list)
{
	word_list.insert(end);
	queue<pair<string, int> > q;
	q.push(make_pair(start, 1));
	while(!q.empty())
	{
		string s = q.front().first;
		int len = q.front().second;
		q.pop();
		if(s == end)
			return len;
		vector<string> neighbors = find_neighbors(s, word_list);
		for(int i = 0; i < neighbors.size(); ++i)
			q.push(make_pair(neighbors[i], len + 1));
	}
	return 0;
}



int main()
{
	string start = "hit";
	string end = "cog";
	unordered_set<string> word_list { "hot", "dot", "dog", "lot", "log" };

	cout << "Test case 1 returns "
	     << (ladder_length(start, end, word_list) == 5 ? "True" : "False")
	     << endl;

	return 0;
}

