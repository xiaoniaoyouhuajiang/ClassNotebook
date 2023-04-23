#include "stdafx.h"
#include "trapecia.h"
#include "base.h"
#include "square.h"
#include <Windows.h>
#include <vector>
#include <algorithm>
#include "romb.h"
#include <string>
#include "gtest/gtest.h"




TEST(Testing, Test1)
{

	EXPECT_EQ(false, Square(Point(0,0), Point(1,1)).CommonSide(Square(Point(0,2), Point(1,1))));
}

TEST(Testing, Test2) {
	EXPECT_EQ(false, Square(Point(0, 0), Point(1, 1)).CommonSide(Square(Point(0, 0), Point(2, 2))));
}

TEST(Testing, Test3) {
	EXPECT_EQ(true, Square(Point(0, 0), Point(1, 1)).CommonSide(Rombus(Point(0, 0), Point(1, 1), Point(-1, 1))));
}

TEST(Testing, Test4) {
	EXPECT_EQ(false, Square(Point(0, 0), Point(1, 1)).CommonSide(Rombus(Point(0, 0), Point(1, 0), Point(0, 1))));
}



TEST(Testing, Test5) {
	EXPECT_EQ(false, Trapecia(Point(0,0), Point(1,1), Point(-1,1), Point(-2,-1), Point(2,-1)).CommonSide(Rombus(Point(0, 0), Point(1, 0), Point(0, 1))));
}

GTEST_API_ int main(int argc, char** argv)
{
	setlocale(LC_CTYPE, "rus");
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	
	system("pause");
	return 0;
}