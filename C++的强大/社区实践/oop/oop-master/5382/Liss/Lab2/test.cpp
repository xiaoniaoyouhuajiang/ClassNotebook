#include "stdafx.h"
#include "Shape.h"
#include "Pentagon.h"
#include "Segment.h"
#include "Ellips.h"
#include "gtest/gtest.h"
TEST(shape_test, test1)
{
    Ellips ellipse(0, 3, 7, 8, 3.0, 90, "pink");
    Ellips ellipse1(0, 3, 3, 4, 3.0, 90, "blue");
    EXPECT_FALSE(ellipse.equalProjection(ellipse1));
}
TEST(shape_test, test2)
{
	Segment seg1(0, 0, 3, 2.0, 60, "yellow" );
	Segment seg2(1, 1, 3, 2.0, 60, "red");
    EXPECT_TRUE(seg1.equalProjection(seg2));
}
TEST(shape_test, test3)
{
	Pentagon pen1(0, 0, 3, 4.0, 45, "pink");
	Pentagon pen2(2, 3, 3, 5.0, 45, "black");
    EXPECT_TRUE(pen1.equalProjection(pen2));
}

int main(int argc, char* argv[])
{
	Pentagon pen1(0, 0, 3, 4.0, 45, "pink");
	Pentagon pen2(2, 3, 3, 5.0, 45, "black");
	std::cout << (pen1.equalProjection(pen2));
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}