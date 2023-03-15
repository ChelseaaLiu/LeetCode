#pragma once
#ifdef MATHLIBRARY_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

#include <vector>
#include <string>

using namespace std;

class DllExport PrintVector
{
public:
	void print_2d_vec(vector<vector<int>>& vec);

private:

};

class DllExport DP : public PrintVector
{
public : 

	vector<vector<int>> generate(int numRows);
	int lengthOfLIS(vector<int>& nums);//300
	int fib(int n); //509
	int tribonacci(int n); // 1137
};

class DllExport Solution : public DP
{
public:

	Solution();

	// String 
	bool isValid(string s);

private:

};

