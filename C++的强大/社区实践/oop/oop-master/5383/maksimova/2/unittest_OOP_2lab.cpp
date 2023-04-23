// unittest_OOP_2lab.cpp : Defines the entry point for the console application.
//

#include "gtest\gtest.h"
#include "Shape.h"
#include "Rhombus.h"
#include "Square.h"
#include "Trapezium.h"
#include "Dot.h"
#include <vector>
#include <cmath>

//1 Два пересекающихся квадрата.
TEST(area_test, test_true) {
	std::vector<Dot> a = {Dot(1, 1), Dot(1, 3), Dot(3, 3), Dot(3, 1)};
	std::vector<Dot> b = { Dot(3, 1), Dot(3, 3), Dot(5,3), Dot(5, 1) };
	Square square(a);
	Square square2(b);
	ASSERT_EQ(true, square.common_side(&square2));
}
//2 Два непересекающихся квадрата.
TEST(area_test, test_false) {
	std::vector<Dot> a = { Dot(1, 1), Dot(1, 3), Dot(3, 3), Dot(3, 1) };
	std::vector<Dot> b = { Dot(4, 1), Dot(4, 2), Dot(5, 2), Dot(5, 1) };
	Square square(a);
	Square square2(b);
	ASSERT_EQ(false, square.common_side(&square2));
}
//3 Пересекающиеся трапеция и квадрат.
TEST(area_test, trapezium_test) {
	std::vector<Dot> a = { Dot(0, 0), Dot(2, 2), Dot(5, 2), Dot(7, 0) };
	std::vector<Dot> b = { Dot(2, 2), Dot(2, 5), Dot(5, 5), Dot(5, 2) };
	Trapezium trapezium(a);
	Square square2(b);
	ASSERT_EQ(true, trapezium.common_side(&square2));
}
//4 Ошибка при создании ромба.
TEST(area_test, rhombus_fail_test) {
	std::vector<Dot> a = { Dot(0, 0), Dot(2, 2), Dot(5, 2), Dot(7, 0) };

	ASSERT_THROW(Rhombus(a, Color(), 0), std::invalid_argument);
}
//5 Ошибка при создании трапеции.
TEST(area_test, trapezium_fail_test) {
	std::vector<Dot> a = { Dot(0, 0), Dot(2, 5), Dot(5, 5), Dot(5, 2) };

	ASSERT_THROW(Trapezium(a, Color(), 0), std::invalid_argument);
}
//6 Ошибка при создании квадрата.
TEST(area_test, square_fail_test) {
	std::vector<Dot> a = { Dot(0, 0), Dot(2, 2), Dot(5, 2), Dot(7, 0) };

	ASSERT_THROW(Square(a, Color(), 0), std::invalid_argument);
}
//7 Пересечение ромба и квадрата.
TEST(area_test, rhombus_square_test) {
	std::vector<Dot> a = { Dot(1, 1), Dot(2, 1+sqrt(3)), Dot(4, 1 + sqrt(3)), Dot(3, 1) };
	std::vector<Dot> b = { Dot(1, 1), Dot(1, 3), Dot(3,3), Dot(3, 1) };
	Rhombus rhombus(a);
	Square square2(b);
	ASSERT_EQ(true, rhombus.common_side(&square2));
}
//8 Пересечение ромба и трапеции.
TEST(area_test, rhombus_trapezium_test) {
	std::vector<Dot> a = { Dot(1, 1), Dot(2, 1 + sqrt(3)), Dot(4, 1 + sqrt(3)), Dot(3, 1) };
	std::vector<Dot> b = { Dot(0, 0), Dot(1, 1), Dot(3, 1), Dot(4, 0) };
	Rhombus rhombus(a);
	Trapezium trapezium(b);
	ASSERT_EQ(true, rhombus.common_side(&trapezium));
}
//9 Пересечение двух ромбов.
TEST(area_test, rhombus_rhombus_test) {
	std::vector<Dot> a = { Dot(1, 1), Dot(2, 1 + sqrt(3)), Dot(4, 1 + sqrt(3)), Dot(3, 1) };
	std::vector<Dot> b = { Dot(3, 1), Dot(4, 1 + sqrt(3)), Dot(6, 1 + sqrt(3)), Dot(5, 1) };
	Rhombus rhombus1(a);
	Rhombus rhombus2(b);
	ASSERT_EQ(true, rhombus1.common_side(&rhombus2));
}
//10 Пересечение двух квадратов, находящихся под углом.
TEST(area_test, square_square_test) {
	std::vector<Dot> a = { Dot(0, 0), Dot(1, 1), Dot(0,2), Dot(-1, 1) };
	std::vector<Dot> b = { Dot(-1, 1), Dot(0,0), Dot(-1,-1), Dot(-2, 0) };
	Square square1(a);
	Square square2(b);
	ASSERT_EQ(true, square1.common_side(&square2));
}
//11 Пересечение трапециии и ромба.
TEST(area_test, trapezium_rhombus_with_angle) {
	std::vector<Dot> a = { Dot(1, 3), Dot(2, 4), Dot(6, 5), Dot(2, 1) };
	std::vector<Dot> b= { Dot(1, 1), Dot(2, 1 + sqrt(3)), Dot(4, 1 + sqrt(3)), Dot(3, 1) };

	Rhombus rhombus(b);
	Trapezium trapezium(a);
	ASSERT_EQ(false, rhombus.common_side(&trapezium));

}
//12 Построение трапеции по точкам квадрата.
TEST(area_test, trapezium_fail_test2) {
	std::vector<Dot> a = { Dot(1, 1), Dot(1, 3), Dot(3, 3), Dot(3, 1) };

	ASSERT_THROW(Trapezium(a, Color(), 0), std::invalid_argument);
}