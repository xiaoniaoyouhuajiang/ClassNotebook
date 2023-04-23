// Unittest_shapes.cpp : Defines the entry point for the console application.
//


#include "gtest/gtest.h"
#include "oop_lr2.h"

TEST(test_setColor, test_allShapes)
{
	Trapezium tr(Point(1, 1), Point(2, 2), 4, 4);
	ASSERT_THROW(tr.setColor(-8), std::invalid_argument);
	ASSERT_NO_THROW(tr.setColor(4));
	IsoscelesTrapezium is(Point(0, 0), Point(5, 4), 6);
	ASSERT_THROW(is.setColor(10), std::invalid_argument);
	ASSERT_NO_THROW(is.setColor(5));
	Ellipse el(Point(0, 0), 1, 2);
	ASSERT_THROW(el.setColor(10), std::invalid_argument);
	ASSERT_NO_THROW(el.setColor(5));
}

TEST(test_ellipseConstructor, test_radius)
{
	ASSERT_NO_THROW(Ellipse el(Point(0, 0), 1, 3));
	ASSERT_THROW(Ellipse el(Point(0, 0), -3, 3), std::invalid_argument);
	ASSERT_THROW(Ellipse el(Point(0, 0), 1, -5), std::invalid_argument);
	ASSERT_THROW(Ellipse el(Point(0, 0), -7, -5), std::invalid_argument);
}

TEST(test_trapeziumConstructor, test_coordinates)
{
	ASSERT_NO_THROW(Trapezium tr(Point(0, 0), Point(1, 2), 10, 20));
	ASSERT_THROW(Trapezium tr(Point(1, 2), Point(1, 2), 10, 20), std::invalid_argument);
}

TEST(test_trapeziumConstructor, test_basis)
{
	ASSERT_NO_THROW(Trapezium tr(Point(0, 0), Point(1, 2), 10, 20));
	ASSERT_THROW(Trapezium tr(Point(0, 2), Point(1, 2), -10, 20), std::invalid_argument);
	ASSERT_THROW(Trapezium tr(Point(0, 2), Point(1, 2), -10, -20), std::invalid_argument);
	ASSERT_THROW(Trapezium tr(Point(0, 2), Point(1, 2), 10, -20), std::invalid_argument);
	ASSERT_THROW(Trapezium tr(Point(0, 2), Point(1, 2), 0, 20), std::invalid_argument);
}


TEST(test_isoscelesTrapeziumConstructor, test_coordinates)
{
	ASSERT_NO_THROW(IsoscelesTrapezium istr(Point(2, 3), Point(1, 1), 4));
	ASSERT_THROW(IsoscelesTrapezium istr(Point(1, 1), Point(1, 1), 4), std::invalid_argument);
}

TEST(test_isoscelesTrapeziumConstructor, test_basis)
{
	ASSERT_NO_THROW(IsoscelesTrapezium istr(Point(2, 3), Point(1, 1), 4));
	ASSERT_THROW(IsoscelesTrapezium istr(Point(2, 3), Point(1, 1), -4), std::invalid_argument);
	ASSERT_THROW(IsoscelesTrapezium istr(Point(2, 3), Point(1, 1), 0), std::invalid_argument);
	ASSERT_THROW(IsoscelesTrapezium istr(Point(2, 3), Point(1, 1), 2), std::invalid_argument);
	ASSERT_THROW(IsoscelesTrapezium istr(Point(2, 3), Point(1, 1), 1), std::invalid_argument);
	ASSERT_NO_THROW(IsoscelesTrapezium istr(Point(2, 4), Point(4, 1), 2));
	ASSERT_THROW(IsoscelesTrapezium istr(Point(2, 4), Point(4, 1), 0), std::invalid_argument);
}

TEST(test_Scale, test_allShapes)
{
	Trapezium tr(Point(1, 1), Point(2, 2), 4, 4);
	ASSERT_THROW(tr.Scale(-7), std::invalid_argument);
	ASSERT_NO_THROW(tr.Scale(2));
	IsoscelesTrapezium is(Point(0, 0), Point(5, 4), 6);
	ASSERT_THROW(is.Scale(0), std::invalid_argument);
	ASSERT_NO_THROW(is.Scale(0.5));
	Ellipse el(Point(0, 0), 1, 2);
	ASSERT_THROW(el.Scale(-23), std::invalid_argument);
	ASSERT_NO_THROW(el.Scale(0.001));
}


int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
