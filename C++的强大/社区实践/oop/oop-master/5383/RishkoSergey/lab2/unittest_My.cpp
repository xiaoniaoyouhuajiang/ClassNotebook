#include "gtest/gtest.h"
#include "../OOP_Lab2/Shape.h"
#include "../OOP_Lab2/Pentagon.h"
#include "../OOP_Lab2/Ellipse.h"
#include "../OOP_Lab2/Section.h"

TEST(testPerimetr, simpletest){
	Section section(0, 0, 1, 1);
	EXPECT_DOUBLE_EQ(section.Perimetr(), 1.41421);
}

TEST(testPerimetr, simpletest2){
	Ellipse ellipse(2, 0, 0, 1, 0, 0);
	EXPECT_DOUBLE_EQ(ellipse.Perimetr(), 9.42478);
}

TEST(testPentagon, simpletest3){
	Pentagon pentagon(0, 0, 0, 2, 1, 2, 2, 1, 2, 0);
	EXPECT_DOUBLE_EQ(pentagon.Perimetr(), 7.41421);
}