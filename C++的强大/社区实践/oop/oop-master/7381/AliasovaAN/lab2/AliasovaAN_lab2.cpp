#include "pch.h"
#include <iostream>
#include <ostream>
#include <cmath>
#include <vector>
#include <string>

struct RGB {
	int red;
	int green;
	int blue;
};

class Shape {
private:
	static unsigned int ID_c;
protected:
	double centre_x;
	double centre_y;
	double angle;
	RGB color;
	double scale = 1.0;
	unsigned int ID;
public:

	Shape() :
		centre_x(0.0),
		centre_y(0.0),
		angle(0.0),
		color({ 0,0,0 }),
		ID(ID_c)
	{
		ID_c++;
	}

	Shape(double x, double y, const RGB& set_color) :
		centre_x(x),
		centre_y(y),
		angle(0.0),
		color(set_color),
		ID(ID_c)
	{
		ID_c++;
	}

	//Перемещение центра
	void move(double x, double y) {
		centre_x = x;
		centre_y = y;
	}

	//Поворот угла
	void rotate(double plus_angle) {
		angle += plus_angle;
	}

	//Масштаб
	virtual void scaling(double scale) = 0;

	//Установ цвета
	void set_color(const RGB& set_color) {
		color = set_color;
	}

	//Получение цвета
	RGB& get_color() {
		return color;
	}

	/*friend std::ostream& operator << (std::ostream& stream, const Shape& shape) {
		std::cout << shape.print(stream));
		return stream;
	}*/

	virtual std::ostream& print(std::ostream& stream, Shape& shape) = 0;

	/*virtual std::ostream& print(std::ostream& stream, Shape& shape) {
		stream << "ID : " << ID << std::endl;
		stream << "Centre coordinates: (" << centre_x << ", " << centre_y << ")" << std::endl;
		stream << "Angle : " << angle << std::endl;
		stream << "Color (RGB) : " << color.red << ":" << color.green << ":" << color.blue << std::endl;
		stream << "Scale : " << scale << std::endl;
	}*/


	friend std::ostream& operator << (std::ostream& stream, Shape& shape)
	{
		return shape.print(stream, shape);
	}
};

unsigned int Shape::ID_c = 0;

class Triangle : public Shape {
protected:
	double a;
	double b;
	double c;
public:
	Triangle() :
		Shape(), a(0.0), b(0.0), c(0.0)
	{}

	Triangle(double x, double y, const RGB& color, double a, double b, double c) :
		Shape(x, y, color), a(a), b(b), c(c)
	{}

	void scaling(double scale) override {
		a *= scale;
		b *= scale;
		c *= scale;
	}
	
	std::ostream& print(std::ostream& stream, Shape& tri) override{
		stream << "Figure : Triangle" << std::endl;
		stream << "ID : " << ID << std::endl;
		stream << "Centre coordinates: (" << centre_x << ", " << centre_y << ")" << std::endl;
		stream << "Angle : " << angle << std::endl;
		stream << "Color (RGB) : " << color.red << ":" << color.green << ":" << color.blue << std::endl;
		stream << "Scale : " << scale << std::endl;
		stream << "Side: : a - " << a << ", b - " << b << ", b - " << c << std::endl;
		return stream;
	}

	/*friend std::ostream& operator << (std::ostream& stream, const Triangle& tri) {
		stream << "Figure : Triangle" << std::endl;
		stream << (Shape&) tri;
		stream << "Side: : a - " << tri.a << ", b - " << tri.b << ", c - " << tri.c << std::endl;
		return stream;
	}*/
};


class Equilateral_Triangle : public Triangle {
public:
	Equilateral_Triangle() :
		Triangle()
	{}

	Equilateral_Triangle(double x, double y, const RGB& color, double a) :
		Triangle(x, y, color, a, a, a)
	{}

	/*friend std::ostream& operator << (std::ostream& stream, const Equilateral_Triangle& tri) {
		stream << "Figure : Equilateral Triangle" << std::endl;
		stream << (Shape&) tri;
		stream << "Side: : a - " << tri.a << ", b - " << tri.a << ", b - " << tri.a << std::endl;
		return stream;
	}*/

	std::ostream& print(std::ostream& stream, Shape& tri) override {
		stream << "Figure : Equilateral Triangle" << std::endl;
		stream << "ID : " << ID << std::endl;
		stream << "Centre coordinates: (" << centre_x << ", " << centre_y << ")" << std::endl;
		stream << "Angle : " << angle << std::endl;
		stream << "Color (RGB) : " << color.red << ":" << color.green << ":" << color.blue << std::endl;
		stream << "Scale : " << scale << std::endl;
		stream << "Side: : a - " << a << ", b - " << a << ", b - " << a << std::endl;
		return stream;
	}
};

class Parallelogram : public Shape {
protected:
	double a;
	double b;
	double angle;
public:
	Parallelogram()
		: Shape(), a(0.0), b(0.0), angle(0.0)
	{}

	Parallelogram(double x, double y, const RGB& color, double a, double b, double angle)
		: Shape(x, y, color), a(a), b(b), angle(angle)
	{}

	void scaling(double scale) {
		a *= scale;
		b *= scale;
	}

/*	friend std::ostream& operator <<(std::ostream& stream, const Parallelogram& par) {
		stream << "Figure : Parallelogram" << std::endl;
		stream << (Shape&) par;
		stream << "Side: : a - " << par.a << ", b - " << par.b << std::endl;
		return stream;
	}*/

	std::ostream& print(std::ostream& stream, Shape& par) override {
		stream << "Figure : Equilateral Triangle" << std::endl;
		stream << "ID : " << ID << std::endl;
		stream << "Centre coordinates: (" << centre_x << ", " << centre_y << ")" << std::endl;
		stream << "Angle : " << angle << std::endl;
		stream << "Color (RGB) : " << color.red << ":" << color.green << ":" << color.blue << std::endl;
		stream << "Scale : " << scale << std::endl;
		stream << "Side: : a - " << a << ", b - " << b << std::endl;
		return stream;
	}
};

int main() {

	Triangle triangle(1, 2, { 67, 50, 20 }, 3, 4, 8);
	std::cout << "\033[4;32mDEMO TRIANGLE\033[0m" << std::endl;
	std::cout << triangle << std::endl;
	std::cout << "\033[4;32mROTATE TRIANGLE +50\033[0m" << std::endl;
	triangle.rotate(50);
	std::cout << triangle << std::endl;
	std::cout << "\033[4;32mSCALING TRIANGLE x25\033[0m" << std::endl;
	triangle.scaling(25);
	std::cout << triangle << std::endl;
	std::cout << "\033[4;32mSET COLOR TRIANGLE 80:80:80\033[0m" << std::endl;
	triangle.set_color({ 80, 80, 80 });
	std::cout << triangle << std::endl;
	std::cout << "\033[4;32mMOVE TRIANGLE (50, 60)\033[0m" << std::endl;
	triangle.move(50, 60);
	std::cout << triangle << std::endl;

	Equilateral_Triangle eq_triangle(13, 13, { 60, 60, 60 }, 5);
	std::cout << "\033[4;36mDEMO Equilateral TRIANGLE\033[0m" << std::endl;
	std::cout << eq_triangle << std::endl;

	Parallelogram par(4, 10, { 40, 50, 60 }, 3, 8, 120);
	std::cout << "\033[4;31mDEMO Parallelogram\033[0m" << std::endl;
	std::cout << par << std::endl;

	std::cout << "\033[4;31mTASK\033[0m";
	std::cout << std::endl;
	std::vector <Shape*> objs;

	objs.push_back(new Parallelogram(8, 17, { 40, 50, 60 }, 3, 8, 120));
	objs.push_back(new Triangle(13, 13, { 60, 70, 60 }, 5, 10, 7));
	objs.push_back(new Equilateral_Triangle(17, 13, { 60, 60, 60 }, 5));

	/*std::cout << *(Parallelogram*)objs[0] << std::endl;
	std::cout << *(Equilateral_Triangle*)objs[2] << std::endl;
	std::cout << *(Triangle*)objs[1] << std::endl;*/


	for (int i = 0; i < objs.size(); i++) {
		std::cout << *objs[i] << std::endl;
	}

	return 0;
}