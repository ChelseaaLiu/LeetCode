#include "pch.h"
#include "../LeetCodeProject/LeetCodeProject.h"
#include <array>
#include <string>

using namespace std;

class CheckVector
{
public:
	template<size_t SIZE>
	void test_2dVector(int& arrIdx, const vector<vector<int>>& vec, const array<int, SIZE>& expected_arr)
	{
		arrIdx = 0;
		for (size_t i = 0; i < vec.size(); ++i)
		{
			for (size_t j = 0; j < vec[i].size(); ++j)
			{
				ASSERT_LT(arrIdx, expected_arr.size());
				EXPECT_EQ(vec[i][j], expected_arr[arrIdx++]);
			}
		}
	}

	template<class T, size_t SIZE>
	void test_1dVector(const vector<T>& vec, const array<T, SIZE>& expected_arr)
	{
		for (size_t i = 0; i < vec.size(); ++i)
		{
			EXPECT_EQ(vec[i], expected_arr[i]);
		}
	}
};

class DPTests : public ::testing::Test, public CheckVector {
protected:
	template<size_t SIZE>
	void test_118(const int numRows, const array<int, SIZE>& expected_arr)
	{
		Solution sol;
		vector<vector<int>> vec = sol.generate(numRows);
		int res_len = 0;
		test_2dVector(res_len, vec, expected_arr);
	}
};

class BacktrackingTests : public ::testing::Test, public CheckVector {
protected:
	template<size_t SIZE>
	void test_39(vector<int> candidates, int target, const array<int, SIZE> expected_arr)
	{
		vector<vector<int>> res = sol.combinationSum(candidates, target);
		int res_len = 0;
		test_2dVector(res_len, res, expected_arr);
	}

	template<size_t SIZE>
	void test_40(vector<int> candidates, int target, const array<int, SIZE> expected_arr)
	{
		vector<vector<int>> res = sol.combinationSum2(candidates, target);
		int res_len = 0;
		//test_2dVector(res_len, res, expected_arr);

		//EXPECT_EQ(res_len, expected_arr.size());
	}

protected:
	Solution sol;
};

class OtherTests : public ::testing::Test {

protected:

	void test_20(string s, bool expected_res)
	{
		
		bool res = sol.isValid(s);
		// cout << s << endl;
		EXPECT_EQ(res, expected_res);
	}

	void test_26(vector<int>& nums, vector<int>& expected_nums, int expected_res)
	{
		int res = sol.removeDuplicates(nums);
		EXPECT_EQ(res, expected_res);
		for (size_t i = 0; i < res; ++i)
		{
			EXPECT_EQ(nums[i], expected_nums[i]);
		}
	}

	void test_other()
	{

		vector<vector<int>> vec;
		vec.push_back({ 0,2 });
		vec.push_back({ 0,5 });
		vec.push_back({ 2,4 });
		vec.push_back({ 1,6 });
		vec.push_back({ 5,4 });

		long long out = bdfs.countPairs(7, vec);
		cout << "countPairs = " << out << endl;
	}

protected:
	Solution sol;
	BDFS bdfs;
};

class Solution4Tests : public ::testing::Test, public CheckVector {

protected:

	void test_1742(int lowLimit, int highLimit, int expected_res)
	{
		int res = sol.countBalls(lowLimit, highLimit);
		EXPECT_EQ(res, expected_res);
	}

	void Test2264(string num, string expected_res)
	{
		string res = sol.largestGoodInteger(num);
		EXPECT_EQ(res, expected_res);
	}

	template<size_t SIZE>
	void test_1093(vector<int>& count, const array<double, SIZE>& expected_arr)
	{
		vector<double> res = sol.sampleStats(count);

		test_1dVector(res, expected_arr);
	}

protected:
	Solution sol;

};

TEST_F(DPTests, TestGenerate){

	array<int, 15> arr{ {1, 1, 1, 1, 2, 1, 1, 3, 3, 1, 1, 4, 6, 4, 1 } };
	for (size_t i = 0; i < 5; i++)
	{
		test_118(i+1, arr);
	}
}

TEST_F(OtherTests, Test20) {
	
	test_20("()", true);
	test_20("()[]{}", true);
	test_20("(]", false);
	test_20("({[)", false);
	test_20("([)]", false);
	test_20("[", false);
	test_20(")", false);
}

TEST_F(BacktrackingTests, Test39)
{
	vector<int> candidates = { 2,3,6,7 };
	int target = 7;
	array<int, 4> expected_arr_1{ {2, 2, 3, 7} };
	test_39(candidates, target, expected_arr_1);

	candidates = { 2,3,5 };
	target = 8;
	array<int, 9> expected_arr_2{ {2, 2, 2, 2, 2, 3, 3, 3, 5} };
	test_39(candidates, target, expected_arr_2);
}

TEST_F(BacktrackingTests, Test40)
{
	vector<int> candidates = { 8,1,2,7,6,1,5 };
	int target = 8;
	array<int, 10> expected_arr_1{ {1,1,6, 1, 2, 5, 1, 7, 2, 6} };
	// test_40(candidates, target, expected_arr_1);

	candidates = { 2,5,2,1,2}; // 1 2 2 2 5
	target = 5;
	array<int, 4> expected_arr_2{ {1, 2, 2, 5} };
	test_40(candidates, target, expected_arr_2);
}

TEST_F(OtherTests, Test26) {
	vector<int> nums = { 1, 1, 2 };
	vector<int> expected_nums = { 1, 2 };
	test_26(nums, expected_nums, 2);

	nums = { 0, 0, 1, 1, 1, 2, 2, 3, 3, 4 };
	expected_nums = { 0, 1, 2, 3, 4 };
	test_26(nums, expected_nums, 5);

	nums = { 0 };
	expected_nums = { 0 };
	test_26(nums, expected_nums, 1);
	sol.removeDuplicates(nums);
}

TEST_F(Solution4Tests, Test1742) {
	test_1742(1, 10, 2);
	test_1742(5, 15, 2);

	test_1742(1, 1, 1);
	test_1742(88888, 100000, 736);
}

TEST_F(Solution4Tests, Test2264) {
	Test2264("6777133339", "777");
	Test2264("2300019", "000");
	Test2264("42352338", "");
}

TEST_F(Solution4Tests, Test1039) {
	vector<int> count = { 0,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	array<double, 5> expected_arr{ {1.00000, 3.00000, 2.37500, 2.50000, 3.00000} };
	test_1093(count, expected_arr);


	count = { 0,4,3,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	expected_arr = { 1.00000, 4.00000, 2.18182, 2.00000, 1.00000 };
	test_1093(count, expected_arr);

	count = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3510,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6718,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,27870,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,26256,0,0,0,0,9586565,0,0,0,0,0,0,0,2333,0,0,0,0 };
	expected_arr = { 32.00000,251.00000,242.40435,243.00000,243.00000 };
	test_1093(count, expected_arr);

}


TEST_F(OtherTests, Tests)
{
	test_other();
}
