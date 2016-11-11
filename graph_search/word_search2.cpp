// Problem description:

// Given a 2D board and a word, find all words in the board.

// Each word must be constructed from letters of sequentially adjacent cell, 
// where "adjacent" cells are those horizontally or vertically neighboring.
// The same letter cell may not be used more than once.
// For example,
// Given words = ["oath", "pea", "eat", "rain"], board = 
// [
//    ['o', 'a', 'a', 'n'],
//    ['e', 't', 'a', 'e'],
//    ['i', 'h', 'k', 'r'],
//    ['i', 'f', 'l', 'v']
// ]
// Return ["eat", "oath"].

// Idea:
// 1. Start from each position, use bfs or dfs.
// 2. Use trie to cut branches.



#include <iostream>
#include <vector>
#include <set>

using namespace std;


struct TrieNode
{
	TrieNode* ch[26];
	bool is_word;
	TrieNode() : is_word(false)
	{
		for(auto &a : ch)
			a = NULL;
	}
};

class Trie {
private:
	TrieNode* root;

public:
	Trie()
	{
		root = new TrieNode();
	}

	void insert(string word)
	{
		TrieNode* p = root;
		for(auto &a : word)
		{
			int i = a - 'a';
			if(!p->ch[i])
				p->ch[i] = new TrieNode();
			p = p->ch[i];
		}
		p->is_word = true;
	}

	bool is_prefix(string word)
	{
		TrieNode* p = root;
		for(auto &a : word)
		{
			int i = a - 'a';
			if(!p->ch[i])
				return false;
			p = p->ch[i];
		}
		return true;
	}

	bool is_word(string word)
	{
		TrieNode* p = root;
		for(auto &a : word)
		{
			int i = a - 'a';
			if(!p->ch[i])
				return false;
			p = p->ch[i];
		}
		return p->is_word;
	}
};

void dfs(vector<vector<char> >& board, vector<vector<bool> >& visited,
	     set<string>& st, string& s, int row, int col, Trie* t)
{
	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };
	visited[row][col] = true;
	int x, y;
	for(int i = 0; i < 4; ++i)
	{
		x = row + dx[i];
		y = col + dy[i];
		if(!(x < 0 || y < 0 || x >= board.size() || y >= board[0].size()
		   || visited[x][y]))
		{
			s.push_back(board[x][y]);
			if(t->is_word(s))
				st.insert(s);
			if(t->is_prefix(s))
				dfs(board, visited, st, s, x, y, t);
			s.pop_back();
		}
	}
	
	visited[row][col] = false;
}

vector<string> find_words(vector<vector<char> >& board, vector<string>& words)
{
	vector<string> res;
	if(board.empty() || board[0].empty() || words.empty())
		return res;

	Trie* t = new Trie();
	for(auto & word : words)
		t->insert(word);


	int m = board.size(), n = board[0].size();
	vector<vector<bool> > visited(m, vector<bool>(n, false));

	string s;
	set<string> st;

	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			s.push_back(board[i][j]);
			if(t->is_word(s))
				st.insert(s);
			if(t->is_prefix(s))
				dfs(board, visited, st, s, i, j, t);
			s.pop_back();
		}
	}
	for(auto & word : st)
		res.push_back(word);

	return res;
}

int main()
{
	vector<vector<char> > board { { 'o', 'a', 'a', 'n' },
								  { 'e', 't', 'a', 'e' },
								  { 'i', 'h', 'k', 'r' },
								  { 'i', 'f', 'l', 'v' } };

	vector<string> words { "oath", "pea", "eat", "rain" };

	auto ans = find_words(board, words);

	cout << "Test case 1 returns "
         << ((ans.size() == 2 && ((ans[0] == "oath" && ans[1] == "eat") ||
         	                      (ans[1] == "oath" && ans[0] == "eat")))
              ? "True" : "False")
         << endl;
	
	return 0;
}

