
#include "stdafx.h"
#include <iostream>
#include <string>
#include <cmath>  
const double M_PI = 4 * atan(1);

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
		os << std::endl << std::endl;
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
			<< "Center: (" << x0 << ", " << y0 << ") \n" << "Color: " << color << " \nRadius X: " << xr << "\nRadius Y: " << yr << "\n"
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
			<< " \nRadius X: " << xr << "\nRadius Y: " << yr << "\nStart angle: " << a0 << "\nFinal angle: " << a << "\n"
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
		, angle(angle % 90 == 0 ? 90 : angle % 90)
		, angle_turn(0)
	{}
	void scaling(int n) {
		a *= n;
		b *= n;
	}

	void turn(int alf) {
		if (alf % 90 != 0)
			throw std::invalid_argument("Angle not a multiple of 90 degrees");
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
		else return b*sin(angle*M_PI / 180);
	}

	void s_out() const {
		std::cout << "Parallelogram\n"
			<< "Center: (" << x0 << ", " << y0 << ") \n" << "Color: " << color << '\n'
			<< "First side: " << a << "\n" << "Second side: " << b << "\n" << "Angle between sides: " << angle << "\n" << "Turn angle: " << angle_turn << '\n'
			<< "ID: " << get_ID() << '\n';
	}
};

bool isIntersect(const Shape& first, const Shape& second) {
	float x1 = first.rectangle_x();
	float x2 = second.rectangle_x();
	float y1 = first.rectangle_y();
	float y2 = second.rectangle_y();
	if (first.get_y0() - 0.5*y1 > second.get_y0() + 0.5*y2)	return false;
	if (second.get_y0() - 0.5*y2 > first.get_y0() + 0.5*y1) return false;
	if (first.get_x0() - 0.5*x1 > second.get_x0() + 0.5*x2) return false;
	if (second.get_x0() - 0.5*x2 > first.get_x0() + 0.5*x1) return false;
	else return true;
}