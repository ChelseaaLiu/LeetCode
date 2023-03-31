#include "LeetCodeProject.h"
#include <iostream>
#include <stack>
#include<algorithm> // sort
#include <numeric>

Solution::Solution()
{

}

void PrintVector::print_2d_vec(vector<vector<int>>& vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		for (size_t j = 0; j < vec[i].size(); ++j)
		{
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <class T>
void PrintVector::print_1d_vec(vector<T>& vec)
{

	for (size_t i = 0; i < vec.size(); ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}


#pragma region DP

// * 118. Pascal's Triangle
vector<vector<int>> DP::generate(int numRows)
{
	vector <vector <int>> res;
	vector <int> temp;
	// temp.reserve(numRows); // Reserved for numRows elements, no initialization
	for (size_t i = 0; i < numRows; i++) {
		temp.push_back(1);
		for (size_t j = 1; j < i; j++) {
			temp[j] = res[i - 1][j - 1] + res[i - 1][j];
		}
		// cout << temp.size() << endl;
		res.push_back(temp);
	}
	return res;
}

// * 300. Longest Increasing Subsequence (找最大的遞增數列長度, 不用連續)
// 用前k-1個 推到第 k 個
/* e.g. 1.
Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
*/
int DP::lengthOfLIS(vector<int>& nums)
{
	int out = 1; // length = 1

	const int len = nums.size();
	vector<int> dp(len, 1); // 前 k 項, max length (sub array)

	for (int i = 1; i < len; ++i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			if (nums[i] > nums[j])
			{
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		if (dp[i] > out)
		{
			out = dp[i];
		}
	}
	return out;
}

// * 509. Fibonacci Number
int DP::fib(int n)
{
	int a0 = 0, a1 = 1, tmp = 0;
	if (n == 0)
	{
		a1 = a0;
	}
	for (int i = 1; i < n; ++i)
	{
		tmp = a1;
		a1 = a1 + a0;
		a0 = tmp;
	}

	return a1;
}

// * 1137. N - th Tribonacci Number
int DP::tribonacci(int n)
{
	int tmp1 = 0, tmp2 = 0, T0 = 0, T1 = 1, T2 = 1;
	if (n == 0)
	{
		T2 = T0;
	}
	for (int i = 2; i < n; ++i)
	{
		tmp1 = T2;
		T2 = T2 + T1 + T0;
		tmp2 = T1;
		T1 = tmp1;
		T0 = tmp2;
	}
	return T2;
}
#pragma endregion

#pragma region DFSBFS

#pragma endregion

#pragma region Backtracking

// 39. Combination Sum (unique)
/*

             1            2        3
      /      |  \        / \       |
     1       2   3      2   3      3
   / | \    / \   \    / \   \     |
  1  2  3  2   3   3  2   3   3    3

*/
vector<vector<int>> Backtracking::combinationSum(vector<int>& candidates, int target)
{
	vector<vector<int>> out;
	vector<int> subOut;

	_helper(out, subOut, candidates, target, 0, 0);
	// print_2d_vec(out);
	return out;
}
void Backtracking::_helper(vector<vector<int>>& ans, vector<int> subAns,
	const vector<int>& candidates, const int& target, const int& sum, const int& i)
{
	if (sum == target)
	{
		ans.push_back(subAns);
		return;
	}

	if (i == candidates.size() || sum > target)
		return;

	// Self
	subAns.push_back(candidates[i]);
	_helper(ans, subAns, candidates, target, sum + candidates[i], i);

	// Next
	subAns.pop_back();
	_helper(ans, subAns, candidates, target, sum, i + 1);
}

// 40. Combination Sum II

/*
[1, 2, 2, 3] (剪枝)

		   1            2       x     3
	  /    |  \        / \      
	 2     x    3     2   3    
   /   \              |       
  2     3             3 
  |
  3

*/

vector<vector<int>> Backtracking::combinationSum2(vector<int>& candidates, int target)
{
	vector<vector<int>> out;
	vector<int> subOut;
	sort(candidates.begin(), candidates.end());
	_helper2(out, subOut, candidates, target, 0, 0);

	// print_2d_vec(out);
	return out;
}

void Backtracking::_helper2(vector<vector<int>>& ans, vector<int>& subAns,
	const vector<int>& candidates, const int& target, const int& sum, const int& i)
{
	if (sum == target)
	{
		ans.push_back(subAns);
		return;
	}

	if (i == candidates.size() || sum > target)
		return;

	for (int j = i; j < candidates.size(); ++j) {
		if (j > i && candidates[j] == candidates[j - 1])
			continue;
		subAns.push_back(candidates[j]);
		_helper2(ans, subAns, candidates, target, sum + candidates[j], j+1);
		subAns.pop_back();
	}
}

// 78. Subsets
/*
* 1 <= nums.length <= 10
* -10 <= nums[i] <= 10
* All the numbers of nums are unique.
* Return the solution in any order

	  1        2     3
    /   \      | 
   2     3     3     
   |
   3

*/
vector<vector<int>> Backtracking::subsets(vector<int>& nums)
{
	vector<vector<int>> out;
	vector<int> subOut;

	_helper3(out, subOut, nums, 0, false);

	// print_2d_vec(out);
	return out;
}

void Backtracking::_helper3(vector<vector<int>>& ans, vector<int>& subAns,
	const vector<int>& candidates, const int& i, const bool& isRepeated)
{

	ans.push_back(subAns);

	if (i == candidates.size())
		return;

	for (int j = i; j < candidates.size(); ++j) {
		if (isRepeated == true && j > i && candidates[j] == candidates[j - 1])
			continue;
		subAns.push_back(candidates[j]);
		_helper3(ans, subAns, candidates, j + 1, isRepeated);
		subAns.pop_back();
	}
}

// 90. Subsets II
vector<vector<int>> Backtracking::subsetsWithDup(vector<int>& nums) 
{
	vector<vector<int>> out;
	vector<int> subOut;
	sort(nums.begin(), nums.end());
	_helper3(out, subOut, nums, 0, true);

	// print_2d_vec(out);
	return out;
}

// 46. Permutations
/*
* 1 <= nums.length <= 6
* -10 <= nums[i] <= 10
* All the integers of nums are unique.

* Input: nums = [1,2,3]
* Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
*/
vector<vector<int>> Backtracking::permute(vector<int>& nums)
{
	vector<vector<int>> out;
	_helper4(out, nums, 0);
	// print_2d_vec(out);
	return out;
}
void Backtracking::_helper4(vector<vector<int>>& ans, vector<int>& candidates, const int& i)
{
	if (i == candidates.size())
	{
		ans.push_back(candidates);
		return;
	}

	for (int j = i; j < candidates.size(); ++j)
	{
		swap(candidates[i], candidates[j]);
		_helper4(ans, candidates, i + 1);
		swap(candidates[i], candidates[j]);
	}
}

// 47
// [3,3,0,3]
// [0,1,0,0,9]

bool IsDuplicated(int st, int end, vector<int>& nums) {
	for (int k = st; k < end; k++) {
		if (nums[k] == nums[end]) {
			return true;
		}
	}

	return false;
}

void Backtracking::_helper5(vector<vector<int>>& ans, vector<int>& candidates, const int& i)
{
	if (i == candidates.size())
	{
		ans.push_back(candidates);
		
		return;
	}

	for (int j = i; j < candidates.size(); ++j)
	{
		if ((j == i || candidates[i] != candidates[j]) && !IsDuplicated(i, j, candidates))
		{
			swap(candidates[i], candidates[j]);
			_helper5(ans, candidates, i + 1);
			swap(candidates[i], candidates[j]);
		}
	}
}

vector<vector<int>> Backtracking::permuteUnique(vector<int>& nums)
{
	vector<vector<int>> out;
	vector<int> subOut;
	// sort(nums.begin(), nums.end());
	_helper5(out, nums, 0);

	// print_2d_vec(out);
	return out;
}

#pragma endregion


#pragma region BFS DFS
BDFS::BDFS()
{

}

BDFS::~BDFS()
{

}

// 2316. Count Unreachable Pairs of Nodes in an Undirected Graph
/*
* [0][.......]
* [1][.......]
* [2][.......]
* 
*/
long long BDFS::_get_group_element_num(vector<vector<int>>& group, vector<bool>& visit, int idx)
{
	long long count = 1;
	visit[idx] = true;
	for (size_t i = 0; i < group[idx].size(); ++i)
	{
		int tmp_idx = group[idx][i];
		if (!visit[tmp_idx])
			count += _get_group_element_num(group, visit, tmp_idx);
	}
	return count;
}
long long BDFS::countPairs(int n, vector<vector<int>>& edges)
{
	long long out = 0;
	long long visitedCount = 0;
	vector<vector<int>> group(n);
	vector<bool> visit(n, false);

	// input group
	for (size_t i = 0; i < edges.size(); ++i)
	{
		int node1 = edges[i][0];
		int node2 = edges[i][1];

		group[node1].push_back(node2);
		group[node2].push_back(node1);
	}

	for (int i = 0; i < n; i++) 
	{
		if (!visit[i])
		{
			long long count = _get_group_element_num(group, visit, i);
			out += visitedCount * count;
			visitedCount += count;
		}
	}
	return out;
}


// 133. Clone Graph
//unordered_map<Node*, Node*> copies;
Node* get_root(vector<vector<int>>& vec, int idx)
{
	if (vec[idx].size() <= 0 || idx >= vec[idx].size())
	{
		return NULL;
	}

	Node* root = new Node(idx + 1, {});
	for (size_t i = 0; i < vec[idx].size(); i++)
	{
		root->neighbors.push_back(get_root(vec, vec[idx][i]));
	}
	return root;
}
Node* createInputNode(vector<vector<int>>& vec)
{
	return get_root(vec, 0);
}

void BDFS::free_copies_memories()
{
	unordered_map<int, int> map;

	map[1] = 10;
	map[3] = 30;
	map[5] = 50;

	for (auto& it : map) {
		// Do stuff
		cout << it.first << endl;
	}
}

Node* BDFS::cloneGraph(Node* root)
{
	if (root == NULL)
		return NULL;


	if (_copies.find(root) == _copies.end())
	{
		_copies[root] = new Node(root->val, {});
		for (Node* node: root->neighbors)
		{
			_copies[root]->neighbors.push_back(cloneGraph(node));
		}
	}

	return _copies[root];
}


#pragma endregion


// 20. Valid Parentheses
bool Solution::isValid(string s) 
{
	stack<char> left_brackets;
	for (auto tmp : s)
	{
		if (tmp == '(' || tmp == '[' || tmp == '{')
		{
			left_brackets.push(tmp);
		}
		else 
		{
			if (left_brackets.empty()) // not yet offset
			{
				return false;
			}
			if ((left_brackets.top() == '(' && tmp == ')')
			 || (left_brackets.top() == '[' && tmp == ']')
			 || (left_brackets.top() == '{' && tmp == '}'))
			{
				left_brackets.pop();
			}
			else
			{
				return false;
			}
		}
	}

	return left_brackets.empty();
}

// 26. Remove Duplicates from Sorted Array
int Solution::removeDuplicates(vector<int>& nums)
{
	int idx = 0;
	for (size_t i = 0; i < nums.size(); ++i)
	{
		if (nums[idx] != nums[i])
		{
			nums[++idx] = nums[i];
		}
		else
		{
			continue;
		}
	}
	return idx+1;
}

// 2413. Smallest Even Multiple
int Solution::smallestEvenMultiple(int n)
{
	if (!(n % 2))
	{
		return n;
	}
	return n+n;
}


// 1093. Statistics from a Large Sample
/*
* count.length == 256
* 0 <= count[i] <= 10^9
* 1 <= sum(count) <= 10^9
* The mode of the sample that count represents is unique.
*/
vector<double> Solution4::sampleStats(vector<int>& count)
{
	vector<double> out = { 255, 0, 0, 0, 0 }; // [minimum, maximum, mean, median, mode]
	int num = accumulate(count.begin(), count.end(), 0); // 1 <= sum(count) <= 10^9
	int maxCount = 0;

	for (int i = 0; i < count.size(); ++i)
	{
		if (count[i] > 0)
		{
			// * minimum
			if (i < out[0])
				out[0] = i;

			// * maximum
			if (i > out[1])
				out[1] = i;

			// * sum (mean = sum / num)
			out[2] += uint64_t(count[i]) * uint64_t(i); // 10 ^ 9 * 10 ^ 3

			// * mode
			if (count[i] > maxCount)
			{
				maxCount = count[i];
				out[4] = i;
			}
		}
	}

	// * mean
	if (num > 1)
	{
		out[2] /= num;
		out[2] = round(out[2] * 100000) / 100000;
	}

	// * median
	out[3] = _get_median(count, num);

	return out;
}

double Solution4::_get_median(vector<int>& count, const int& num)
{
	/*
	* 1. [0,1,3,4,0,0,0, ...]
	* [1,2,2,2,3,3,3,3], median_idx : [3, 4]
	* idx : 0 -> 3 -> 7
	* 2. [0,4,3,2,2,0,0,0, ...],
	* [1,1,1,1,2,2,2,3,3,4,4], median_idx : 5
	* idx : 3 -> 6 -> 8 -> 10
	*/

	int out = 0;
	int idx = 0;
	int previous_idx = 0;
	int median_idx = num / 2;
	bool is_odd = num % 2;

	for (int i = 0; i < count.size(); ++i)
	{
		if (count[i] > 0)
		{
			idx += count[i];
			if (idx - 1 >= median_idx)
			{
				if (is_odd)
					return i;

				else
				{
					if (idx - count[i] == median_idx)
						return (i + previous_idx) / 2.0;
					else
						return i;
				}
			}
			previous_idx = i;
		}
	}

	out = round(out * 100000) / 100000;
	return out;
}


// 1742. Maximum Number of Balls in a Box

/*
* 1 <= lowLimit <= highLimit <= 10^5
* box number : ex., 321 => 3+2+1
*/

int Solution4::countBalls(int lowLimit, int highLimit)
{
	// * 1 <= lowLimit <= highLimit <= 10^5
	int out = 0;
	vector<int> ball_count(45, 0); // 9*5
	for (int ball_num = lowLimit; ball_num < highLimit + 1; ++ball_num)
	{
		int box_sum = 0; // box number
		int tmp_ball_num = ball_num;
		while (tmp_ball_num > 0)
		{
			box_sum += tmp_ball_num % 10;
			tmp_ball_num = tmp_ball_num / 10;
		}

		ball_count[box_sum - 1] += 1; // box_sum - 1 >= 0
		if (ball_count[box_sum - 1] > out)
			out = ball_count[box_sum - 1];
	}

	return out;
}

// 2264. Largest 3-Same-Digit Number in String
/*
* 3 <= num.length <= 1000
* num only consists of digits
*/
string Solution4::largestGoodInteger(string num) 
{
	string out = "";

	for (size_t i = 0; i < num.size(); ++i)
	{
		if (i + 2 < num.size() && num[i] == num[i + 1] && num[i + 1] == num[i + 2])
		{
			if (out == "")
				out.push_back(num[i]);
			else if (int(out[0]) < int(num[i]))
				out = num[i];
		}
	}

	out = out + out + out;
	return out;
}

