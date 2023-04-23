// unittest_lab2oop.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "Pentagon.h"
#include "RegPentagon.h"
#include "round.h"

TEST(testlab2, defaultTest)
{
	Pentagon p1 = Pentagon(Color(0, 0, 0));
	Pentagon p2 = Pentagon(Color(0, 0, 0));
	bool res = p1.isInsideOfAnother(p2);
	EXPECT_EQ(res, true);
}

TEST(testlab2, RoundInPentagonTrue)
{
	Round r = Round(10, Point(0, 0), Color(0, 0, 0));
	Pentagon p = Pentagon(Point(-15, -15), Point(-30, 10), Point(0, 30), Point(30, 10), Point(15, -15), Color(0, 0, 0));
	bool res = r.isInsideOfAnother(p);
	EXPECT_EQ(res, true);
}

TEST(testlab3, RoundInRegPentagonFalse)
{
	Round r1 = Round(10, Point(10, 10), Color(0, 0, 0));
	RegPentagon rp = RegPentagon(Point(10, 10), Point(0, 10), Color(0, 0, 0));
	bool res = r1.isInsideOfAnother(rp);
	EXPECT_EQ(res, false);
}

TEST(testlab4, RegPentagonInPentagonFalse)
{
	Pentagon p2 = Pentagon(Point(-1, -1), Point(-1, 0.5), Point(0, 1), Point(1, 0.5), Point(1, -1), Color(0, 0, 0));
	RegPentagon rp2 = RegPentagon(Point(0, 0), Point(100, 100), Color(0, 0, 0));
	bool res = rp2.isInsideOfAnother(p2);
	EXPECT_EQ(res, false);
}

TEST(testlab5, PentagonInRoundTrue)
{
	Round r1 = Round(10, Point(0, 0), Color(0, 0, 0));
	Pentagon p2 = Pentagon(Point(-1, -1), Point(-1, 0.5), Point(0, 1), Point(1, 0.5), Point(1, -1), Color(0, 0, 0));
	bool res = p2.isInsideOfAnother(r1);
	EXPECT_EQ(res, true);
}

/*int main()
{
    return 0;
}
*/
