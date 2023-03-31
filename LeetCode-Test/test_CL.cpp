#include "pch.h"
#include "../LeetCodeProject/CyberLink.h"
#include <string>
#include <iostream>

using namespace std;


TEST(CLTest, __MissingDigit__)
{
	EXPECT_EQ(MissingDigit("4 - 2 = x"), "2");
	EXPECT_EQ(MissingDigit("1x0 * 12 = 1200"), "0");

	EXPECT_EQ(MissingDigit("40 - 2x = 15"), "5");

	// 37 - 12 = 25
	EXPECT_EQ(MissingDigit("x7 - 12 = 25"), "3");
	EXPECT_EQ(MissingDigit("37 - x2 = 25"), "1");
	EXPECT_EQ(MissingDigit("x7 - 12 = 25"), "3");
	EXPECT_EQ(MissingDigit("37 - 12 = x5"), "2");

	// 37 + 12 = 49
	EXPECT_EQ(MissingDigit("x7 + 12 = 49"), "3");
	EXPECT_EQ(MissingDigit("3x + 12 = 49"), "7");
	EXPECT_EQ(MissingDigit("37 + x2 = 49"), "1");
	EXPECT_EQ(MissingDigit("37 + 1x = 49"), "2");
	EXPECT_EQ(MissingDigit("37 + 12 = x9"), "4");
	EXPECT_EQ(MissingDigit("37 + 12 = 4x"), "9");

	// 234 * 45 = 10530
	EXPECT_EQ(MissingDigit("234 * 45 = 1053x"), "0");
	EXPECT_EQ(MissingDigit("234 * 45 = 10x30"), "5");
	EXPECT_EQ(MissingDigit("2x4 * 45 = 10530"), "3");
	EXPECT_EQ(MissingDigit("234 * x5 = 10530"), "4");
	EXPECT_EQ(MissingDigit("234 * 45 = x0530"), "1");
	EXPECT_EQ(MissingDigit("x34 * 45 = 10530"), "2");

	// 10530 / 234 = 45%
	EXPECT_EQ(MissingDigit("10530 / 2x4 = 45"), "3");
	EXPECT_EQ(MissingDigit("10530 / 234 = x5"), "4");
	EXPECT_EQ(MissingDigit("1x530 / 234 = 45"), "0");
	EXPECT_EQ(MissingDigit("10x30 / 234 = 45"), "5");
	EXPECT_EQ(MissingDigit("x0530 / 234 = 45"), "1");

	EXPECT_EQ(MissingDigit("10530/2x4=45"), "3");
	EXPECT_EQ(MissingDigit("10530/234=x5"), "4");
	EXPECT_EQ(MissingDigit("1x530/234=45"), "0");
	EXPECT_EQ(MissingDigit("10x30/234=45"), "5");
	EXPECT_EQ(MissingDigit("x0530/234=45"), "1");
}


TEST(CLTest, __HTMLElements__)
{
	EXPECT_EQ(HTMLElements("<div><div><b></b></div></p>"), "div");
	EXPECT_EQ(HTMLElements("<div>abc</div><p><em><i>test test test</b></em></p>"), "i");
	EXPECT_EQ(HTMLElements("<div><div><b></b></div></p>"), "div");
	//EXPECT_EQ(HTMLElements(">"), "false");
}

TEST(CLTest, __ElementMerger__)
{
	int arr1[] = { 5, 7, 16, 1, 2 };
	int arr2[] = { 1, 1, 1, 2 };
	int arr3[] = { 7 };
	EXPECT_EQ(ElementMerger(arr1, 5), 7);
	EXPECT_EQ(ElementMerger(arr2, 4), 1);
	EXPECT_EQ(ElementMerger(arr3, 1), 7);
}
