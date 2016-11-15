// Problem description:
// Given a singly linked list, return a random node's value from the linked 
// list. Each node must have the same probability of being chosen.
// Follow up:
// What if the linked list is extremely large and its length is unknown to you?
// Could you solve this efficiently without using extra space?


// Idea:
// 1. Reservior sampling.


#include <iostream>
#include <vector>

using namespace std;

// There is 1/k chance that new item will overwrite previous item
// Take the first one as an example:
// 1. frist time it will be selected: 1/2
// 2. second time it will be selected: 2/3, 
//    * this is due to the second item gets selected with the prob of 1/3
// 3. third time it will be selected: 3/4
//    * this is due to the third item gets selected with the prob of 1/4
// ..
// 1/2 * 2/3 * 3/4 * ... * (n-1)/n = 1/n, assume there are n items in total.

struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};


int get_random(ListNode* head)
{
	if(!head)
		return 0;

	int res = head->val, i = 2;
	ListNode* cur = head->next;
	while(cur)
	{
		int j = rand() % i;
		if(j == 0)
			res = cur->val;
		++i;
		cur = cur->next;
	}

	return res;
}


vector<int> count_random_result(ListNode* head, int num, int trial)
{
	srand(time(NULL));

	vector<int> res(num, 0);
	for(int i = 0; i < num * trial; ++i)
	{
		int r = get_random(head);
		++res[r-1];
	}
	return res;
}

int main()
{

	ListNode* head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);

	int num = 3;
	int trial = 100000;
	double error_ratio = 0.01;
	int error = error_ratio * trial;

	auto ans = count_random_result(head, num, trial);
	cout << "ans[0]: " << ans[0] << endl;
	cout << "ans[1]: " << ans[1] << endl;
	cout << "ans[2]: " << ans[2] << endl;
	cout << "Test case 1 returns "
	     << ((ans.size() == num && 
	     	  abs(ans[0] - trial) < error &&
	     	  abs(ans[1] - trial) < error &&
	     	  abs(ans[2] - trial) < error)
	     	 ? "True" : "False")
	     << endl;

	delete head->next->next;
	delete head->next;
	delete head;

	return 0;
}

