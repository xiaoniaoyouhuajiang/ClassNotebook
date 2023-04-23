
#include "stdafx.h"
#include "Windows.h"
#include <iostream>
#include <string>
#include <cmath>  
#include "gtest/gtest.h"
const double M_PI = 4*atan(1);

class Shape {
protected:
	Shape(float x0 = 0, float y0 = 0, std::string color = "white") : x0(x0), y0(y0), color(color) 
	{
		set_ID();
	}
	float x0, y0;
	std::string color;
	unsigned ID;
public:
	void moving(float newx, float newy) {
		x0 = newx;
		y0 = newy;
	}

	std::string get_color() const {
		return color;
	}

	void change_color(std::string newcolor) {
		color = newcolor;
	}

	void set_ID()
	{
		static unsigned counter = 0;
		ID = ++counter;
	}

	unsigned get_ID() const { return ID; }

	virtual void turn(int alf) = 0;
	virtual void scaling(int n) = 0;
	virtual void s_out() const = 0;
	virtual ~Shape() {}
	virtual float rectangle_x() const = 0;
	virtual float rectangle_y() const = 0;

	friend std::ostream& operator <<(std::ostream& os, const Shape& shape) { // оператор вывода
		shape.s_out();
		return os;
	}

	float get_x0() const
	{
		return x0;
	}

	float get_y0() const
	{
		return y0;
	}
};


class Ellipse_m : public Shape {
protected:
	float xr, yr;
public:
	Ellipse_m(float x0 = 0, float y0 = 0, std::string color = "white", float xr = 2, float yr = 1)
		: Shape(x0, y0, color)
		, xr(xr)
		, yr(yr)
	{}
	void scaling(int n) {
		xr *= n;
		yr *= n;
	}

	virtual void turn(int alf) {
		if (alf % 90 != 0)
			throw std::invalid_argument("Angle not a multiple of 90 degrees");

		if (alf % 180 == 90) {
			std::swap(xr, yr);
		}
	}

	float rectangle_x() const {
		return xr * 2;
	}

	float rectangle_y() const {
		return yr * 2;
	}

	virtual void s_out() const {
		std::cout << "Ellipse\n"
			<< "Center: (" << x0 << ", " << y0 << ") \n" << "Color: " << color << " \n Radius X: " << xr << "\n Radius Y: " << yr << "\n"
			<< "ID: " << get_ID() << '\n';
	}
	virtual ~Ellipse_m() {}
};


class Sector : public Ellipse_m {
	int a0, a;
public:
	Sector(float x0 = 0, float y0 = 0, std::string color = "white", float xr = 2, float yr = 1, int a0 = 0, int a = 360)
		: Ellipse_m(x0, y0, color, xr, yr)
		, a0(a0 % 360)
		, a(a % 360)
	{}

	void turn(int alf) {
		if (alf % 90 != 0)
			throw std::invalid_argument("Angle not a multiple of 90 degrees");
		a0 = a0 + alf;
		a0 = a0 % 360;
		a = a + alf;
		a = a % 360;
		if (alf % 180 == 90) {
			std::swap(xr, yr);
		}
	}

	void s_out() const {
		std::cout << "Sector\n"
			<< "Center: (" << x0 << ", " << y0 << ") \n" << "Color: " << color 
			<< " \nRadius X: " << xr << "\nRadius Y: " << yr << "\n Start angle: " << a0 << "\n Final angle: " << a << "/n"
			<< "ID: " << get_ID() << '\n';
	}
	~Sector() {};
};


class Parallelogram : public Shape {
	double a, b;
	int angle;
	int angle_turn;
public:
	Parallelogram(float x0 = 0, float y0 = 0, std::string color = "white", float a = 1, float b = 1, int angle = 30)
		: Shape(x0, y0, color)
		, a(a)
		, b(b)
		, angle(angle)
		, angle_turn(0)
	{}
	void scaling(int n) {
		a *= n;
		b *= n;
	}

	void turn(int alf) {
		if (alf % 90 != 0)
			throw std::invalid_argument ("Angle not a multiple of 90 degrees");
		angle_turn = alf % 360;
	}

	float rectangle_x() const {
		if (angle_turn % 180 == 90) {
			return b*sin(angle*M_PI / 180);
		}
		else return (a + (b*cos(angle*M_PI / 180)));
	}

	float rectangle_y() const {
		if (angle_turn % 180 == 90) {
			return (a + (b*cos(angle*M_PI / 180)));
		}
		else return b*sin(angle*M_PI/180);
	}

	void s_out() const {
		std::cout << "Parallelogram\n"
			<< "Center: (" << x0 << ", " << y0 << ") \n" << "Color: " << color <<'\n'
			<< "First side: " << a << "\n" << "Second side: " << b << "\n" << "Angle between sides: "<< angle << "\n" <<"Turn angle: " << angle_turn <<'\n'
			<< "ID: " << get_ID() << '\n';
	}
};

bool isIntersect(const Shape& first, const Shape& second) {
	float x1 = first.rectangle_x();
	float x2 = second.rectangle_x();
	float y1 = first.rectangle_y();
	float y2 = second.rectangle_y();
	if (first.get_y0() - 0.5*y1 > second.get_y0() + 0.5*y2) return false;
	if (second.get_y0() - 0.5*y2 > first.get_y0() + 0.5*y1) return false;
	if (first.get_x0() - 0.5*x1 > second.get_x0() + 0.5*x2) return false;
	if (second.get_x0() - 0.5*x2 > first.get_x0() + 0.5*x1) return false;
	else return true;
}

TEST(Figure_test, Ellipse_is_intersect_ellipse) {
	Ellipse_m ellipse_f(2, 1, "black", 2, 1);
	Ellipse_m ellipse_s(2, -1, "black", 1, 2);
	EXPECT_TRUE(isIntersect(ellipse_f, ellipse_s));
}

TEST(Figure_test, Ellipse_is_not_intersect_ellipse) {
	Ellipse_m ellipse_f(2, 1, "black", 2, 1);
	Ellipse_m ellipse_s(2, -2.1, "black", 1, 2);
	EXPECT_FALSE(isIntersect(ellipse_f, ellipse_s));
}

TEST(Figure_test, Ellipse_is_intersect_parallelogram) {
	Ellipse_m ellipse(2, 2, "black", 1, 1);
	Parallelogram parallelogram(2.5, 2.5, "black", 2, 2, 45);
	EXPECT_TRUE(isIntersect(ellipse, parallelogram));
}

TEST(Figure_test, Ellipse_is_not_intersect_parallelogram) {
	Ellipse_m ellipse(2, 2, "black", 1, 1);
	Parallelogram parallelogram(4.5, 4.5, "black", 2, 2, 45);
	EXPECT_FALSE(isIntersect(ellipse, parallelogram));
}

TEST(Figure_test, Ellipse_is_intersect_sector) {
	Ellipse_m ellipse(0, 0, "white", 2, 2);
	Sector sector(-2, 2, "white", 1, 1, 180, 270);
	EXPECT_TRUE(isIntersect(ellipse, sector));
}

TEST(Figure_test, Ellipse_is_not_intersect_sector) {
	Ellipse_m ellipse(0, 0, "white", 2, 2);
	Sector sector(0, 3.5, "white", 1, 1, 180, 360);
	EXPECT_FALSE(isIntersect(ellipse, sector));
}

TEST(Figure_test, Parallelogram_is_intersect_parallelogram) {
	Parallelogram parallelogram_f(1, 1, "green", 1, 1, 30);
	Parallelogram parallelogram_s(1, 0.5, "green", 1, 1, 30);
	EXPECT_TRUE(isIntersect(parallelogram_f, parallelogram_s));
}

TEST(Figure_test, Parallelogram_is_not_intersect_parallelogram) {
	Parallelogram parallelogram_f(1, 1, "green", 1, 1, 30);
	Parallelogram parallelogram_s(1, 0, "green", 1, 1, 30);
	EXPECT_FALSE(isIntersect(parallelogram_f, parallelogram_s));
}

TEST(Figure_test, Parallelogram_is_intersect_sector) {
	Parallelogram parallelogram(2, 2, "green", 2, 2, 90);
	Sector sector(2, 4, "green", 1, 1, 180, 360);
	EXPECT_TRUE(isIntersect(parallelogram, sector));
}

TEST(Figure_test, Parallelogram_is_not_intersect_sector) {
	Parallelogram parallelogram(2, 2, "green", 2, 2, 90);
	Sector sector(2, 4.1, "green", 1, 1, 180, 360);
	EXPECT_FALSE(isIntersect(parallelogram, sector));
}

TEST(Figure_test, Sector_is_intersect_sector) {
	Sector sector_f(1, 1, "blue", 2, 2, 90, 180);
	Sector sector_s(3, 3, "blue", 2, 2, 270, 360);
	EXPECT_TRUE(isIntersect(sector_f, sector_s));
}

TEST(Figure_test, Sector_is_not_intersect_sector) {
	Sector sector_f(1, 1, "blue", 2, 2, 90, 180);
	Sector sector_s(5, 5, "blue", 1, 1, 270, 360);
	EXPECT_FALSE(isIntersect(sector_f, sector_s));
}

GTEST_API_ int main(int argc, char **argv) {

	setlocale(0, "Rus");
	srand(time(0));
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}