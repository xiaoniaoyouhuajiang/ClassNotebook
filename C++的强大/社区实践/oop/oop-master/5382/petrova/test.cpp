#include "Shape.h"
/*#include "gtest/gtest.h"

TEST(shape_test, test1) 
{
	Ellips ellipse(Point(10.0, -10.0), 5, 3);
	Ellips ellipse1(Point(10.0, -10.0), 5, 5);
	EXPECT_TRUE(ellipse.equalProjection(ellipse1, 1));
}

TEST(shape_test, test2)
{
	SegEl seg1(Point(0.0, 0.0), Point(1.0, 2.0), Point(3.0, 3.0));
	SegEl seg2(Point(0.0, 0), Point(3.0, 2.0), Point(4.0, 3.0));
	EXPECT_FALSE(seg1.equalProjection(seg2, 0));
}

TEST(shape_test, test3)
{
	Parallelogramm par1(Point(2.0, -1.0), 6.0, 4.0);
	Parallelogramm par2(Point(3.0, -39.0), 7.0, 9.0);
	EXPECT_TRUE(par1.equalProjection(par2, 0));
}
*/
int main(int argc, char* argv[])
{
	Parallelogramm par1(Point(2.0, -1.0), 6.0, 4.0);
	Parallelogramm par2(Point(3.0, -39.0), 7.0, 9.0);
    std::cout << (par1.equalProjection(par2, X));
	//testing::InitGoogleTest(&argc, argv);
	//return RUN_ALL_TESTS();
}
