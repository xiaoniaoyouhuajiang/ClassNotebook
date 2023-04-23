#include "gtest/gtest.h"
//#include "5angle.cpp"
#include "5angle.h"
#include "Rectangle.h"
#include "Pentagram.h"
#include <math.h>


TEST(testDistancePentagon, simpletest){
	Pentagon pentagon(-2, -3, -2, 4, 0, 5, 2, 4, 2, -3);
	pentagon.distance(-2, -3);

	EXPECT_EQ(pentagon.distance(-2, -3), 0);
	
}

TEST(testDistanceRectangle, simpletest){
	Rectangle rectangle(10, 20);
	rectangle.distance(30,40);

	EXPECT_EQ(rectangle.distance(30, 40), 5*sqrt(61));

}

TEST(testDistanceRectangle1, simpletest){
	Rectangle rectangle1(8, 6);
	rectangle1.distance(0,0);

	EXPECT_EQ(rectangle1.distance(0, 0), 5);

}