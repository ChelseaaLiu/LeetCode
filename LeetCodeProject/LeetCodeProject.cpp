#include "LeetCodeProject.h"
#include <iostream>
#include <stack>
#include<algorithm> // sort

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
}

void PrintVector::print_1d_vec(vector<int>& vec)
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
	print_2d_vec(out);
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
vector<vector<int>> Backtracking::combinationSum2(vector<int>& candidates, int target)
{
	vector<vector<int>> out;
	vector<int> subOut;
	sort(candidates.begin(), candidates.end());
	_helper2(out, subOut, candidates, target, 0, 0);

	print_2d_vec(out);
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
