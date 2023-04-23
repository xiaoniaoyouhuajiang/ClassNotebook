
#include "string"
#include "math.h"
#include <cmath>
#include <iostream>
#include <ostream>
using namespace std;

enum ProjectionType { X = 0, Y = 1 };

struct Point
{
	double x, y;

 Point(const double& x = 0, const double& y = 0): x(x), y(y)
	{
	}
};

struct my_color
{
	double r, g, b;
	my_color(const double& r = 0, const double& g = 0, const double& b = 0) : r(r), g(g), b(b)
	{
	}
};


class Shape //базовый класс
{
protected:
	Point center;	
	my_color color;
	int angle; // поворот на угол 

public:
	Shape() {} //конструктор класса
	virtual void move(Point newCenter) = 0;
	virtual void changesize(double k) = 0;
	virtual void turn(double angle)=0; // поворачивает на угол
	my_color getColor()	//получение цвета
	{
		return this->color;
	}
	void setсolor(my_color color)	//установка цвета
	{
		this->color = color;
	}
	virtual ostream &operator << (ostream &output)	//оператор вывода в поток
	{
		return output;
	}
	bool equalProjection(const Shape& other, const ProjectionType projection) const
	{
		double left1 = this->leftx();
		double left2 = other.leftx();
		if (left1 == left2) return true;
		else return false;
	}
	virtual double const leftx() const = 0;
	virtual ~Shape();
};
class Ellips : public Shape //класс окружности
{
private:
	double R;
	double r;
	Point left;
public:
	Ellips(Point center, int _R = 1, int _r = 2);//конструктор класса
    void move(Point newCenter) ;
    void changesize(double k);
    void turn(double angle); // поворачивает на угол
	double const leftx() const;

	ostream &operator << (ostream &output)
	{
		my_color tmpColor = getColor();
		output << "Color: " << "red component = " << tmpColor.r << ", green component = " << tmpColor.g << ", blue component = " << tmpColor.b << " " << endl;
		output << "Center-point {" << this->center.x << " ; " << this->center.y << "}" << endl;
		output << "R" << R << " r " << r << endl;
		return output;
	}
	virtual ~Ellips() {}
};


class SegEl : public Shape //класс квадрата
{
private:
	Point left;
	Point right;
public:
	SegEl(Point center, Point left, Point right); //конструктор класса
	void move(Point newCenter);
	void changesize(double k);
	void turn(double angle); // виртуальный метод для повора фигуры на угол
	double const leftx() const;
	ostream &operator << (ostream &output)
	{
		my_color tmpColor = getColor();
		output << "Color: " << "red component = " << tmpColor.r << ", green component = " << tmpColor.g << ", blue component = " << tmpColor.b << " " << endl;
		output << "Center-point {" << this->center.x << " ; " << this->center.y << "}" << endl;
		output << "Left-point {" << this->left.x << " ; " << this->left.y << "}" << endl;
		output << "Right-point {" << this->right.x << " ; " << this->right.y << "}" << endl;
		return output;
	}
	virtual ~SegEl() {}
};

class Parallelogramm : public Shape //класс квадрата
{
private:
	double l,L;
public:
	Parallelogramm(Point center, int _l = 9, int _L = 3);
	void move(Point newCenter);
	void changesize(double k);
	void turn(double angle);  // виртуальный метод для повора фигуры на угол
	double const leftx() const;
	ostream &operator << (ostream &output)
	{
		my_color tmpColor = getColor();
		output << "Color: " << "red component = " << tmpColor.r << ", green component = " << tmpColor.g << ", blue component = " << tmpColor.b << " " ;
		output << "First-point {" << this->center.x << " ; " << this->center.y << "}" << endl;
		output << "L " << L << "l"<<l << endl;
		return output;
	}
	virtual ~Parallelogramm() {}
};
