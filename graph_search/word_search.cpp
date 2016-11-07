// Problem description:

// Given a 2D board and a word, find if the word exists in the grid.
// The word can be constructed from letters of sequentially adjacent cell, 
// where "adjacent" cells are those horizontally or vertically neighboring.
// The same letter cell may not be used more than once.
// For example,
// Given board = 
// [
//    ['A', 'B', 'C', 'E'],
//    ['S', 'F', 'C', 'S'],
//    ['A', 'D', 'E', 'E']
// ]
// word = "ABCCED", returns true,
// word = "SEE", returns true,
// word = "ABCB", returns false.

// Idea:
// 1. Start from each position, use bfs or dfs.



#include <iostream>
#include <vector>

using namespace std;

bool find_word(vector<vector<char> >& board, vector<vector<bool> >& visited,
	           int row, int col, string& word, int char_cnt)
{
	if(char_cnt == word.size())
		return true;
	if(row < 0 || col < 0 || row >= board.size() || col >= board[0].size() ||
	   visited[row][col] || board[row][col] != word[char_cnt])
		return false;
	visited[row][col] = true;

	vector<int> dx = { -1, 1, 0, 0 };
	vector<int> dy = { 0, 0, -1, 1 };
	for(int i = 0; i < dx.size(); ++i)
	    if(find_word(board, visited, row + dx[i], col + dy[i], word, char_cnt + 1))
	        return true;  
    
    visited[row][col] = false;

    return false;
}

bool exist(vector<vector<char> >& board, string word)
{
	if(board.empty() || board[0].empty())
		return false;
	int m = board.size(), n = board[0].size();
	vector<vector<bool> > visited(m, vector<bool>(n, false));

	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			if(find_word(board, visited, i, j, word, 0))
				return true;
		}
	}
	return false;
}

int main()
{
	vector<vector<char> > board { { 'A', 'B', 'C', 'E' }, 
	                              { 'S', 'F', 'C', 'S' }, 
	                              { 'A', 'D', 'E', 'E' } };

	vector<string> words { "ABCCED", "SEE", "ABCB" };
	vector<bool> tgt { true, true, false };
	for(int i = 0; i < words.size(); ++i)
	{
		cout << "Test case " << i + 1 << " returns "
	         << (exist(board, words[i]) == tgt[i] ? "True" : "False")
	         << endl;
	}
	
	return 0;
}

