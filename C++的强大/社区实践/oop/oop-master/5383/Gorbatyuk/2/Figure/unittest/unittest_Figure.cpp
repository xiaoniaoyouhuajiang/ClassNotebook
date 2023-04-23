// unittest_Figure.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "gtest/gtest.h"
//#include "Figure.cpp"
#include "Shape.h"
#include "Quadrate.h"
#include "RightTriangle.h"
#include "IsoscelesTriangle.h"

TEST(testMath,Test1)
{
	
	Shape *tri2 = new RightTriangle(-1, 2, -1, 0, 3, 0, "green");
	Shape *quad = new Quadrate(-4, -4, -4, 0, 0, 0, 0, -4, "blue");
	ASSERT_FALSE(tri2->IsInsideOfAnother(*quad));
	
}
TEST(testMath, Test2)
{
Shape *tri = new IsoscelesTriangle(-0.5, 0.5, 0, 1, 0.5, 0.5, "red");
Shape *quad2 = new Quadrate(-1, 0, -1, 2, 1, 2, 1, 0, "blue");
ASSERT_TRUE(tri->IsInsideOfAnother(*quad2));


}
TEST(testMath, Test3) 
{
	Shape *tri = new IsoscelesTriangle(-0.5, 0.5, 0, 1, 0.5, 0.5, "red");
	Shape *tri2 = new RightTriangle(-1, 2, -1, 0, 3, 0, "green");
	ASSERT_TRUE(tri->IsInsideOfAnother(*tri2));
}

TEST(testMath, Test4)
{
	Shape *bbtri = new IsoscelesTriangle(-4, 0, 0, 6, 4, 0, "white");
	Shape *ssquad = new Quadrate(-1, 0, -1, 1, 0, 1, 0, 0, "red");
	ASSERT_FALSE(ssquad->IsInsideOfAnother(*bbtri));
}
TEST(testMath, Test5) 
{
	Shape *btri = new RightTriangle(0, 0, 0, 4, 8, 0, "green");
	Shape *squad = new Quadrate(1, 1, 1, 2, 2, 2, 2, 1, "red");
	ASSERT_TRUE(squad->IsInsideOfAnother(*btri));
}