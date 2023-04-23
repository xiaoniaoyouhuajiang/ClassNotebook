
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "oop_lr2.h"

using namespace std;

std::vector<std::string> colors {"transparent", "red", "yellow", "blue", "white", "black"};

unsigned getNumberDigits(unsigned x) 
{
	unsigned count = 0;
	while (x != 0) 
	{
		count++;
		x /= 10;
	}
	return count;
}

Point::Point(float x_, float y_):
		x(x_), y(y_) {};
		
void Point::move(float x_, float y_)
{
	x += x_;
	y += y_;
};

void Point::rotate(float alpha)
{
	 float x_ = x * cos(alpha) - y * sin(alpha);
	 float y_ = x * sin(alpha) + y * cos(alpha);
	 x = x_; y = y_;		
};

void Point::scale(Point point0, float k)
{
	x = point0.x + abs(x - point0.x)*k;
	y = point0.y + abs(y - point0.y)*k;		
};


Shape::Shape()
	:color(0)
{
}

void Shape::Move(float x_, float y_)  
{
	for (Point &point_ : point)
		point_.move(x_, y_);
}

void Shape::Rotate(float alpha)        //поворот фигуры относительно начала координат
{
	for (Point &point_ : point)
		point_.rotate(alpha);
}

void Shape::setColor(unsigned color_)
{
	if (color_ > colors.size())
		throw std::invalid_argument("It's not such color!");
	color = color_;
}

unsigned Shape::getColor() const
{
	return color;
}

ostream& operator<< (ostream& s, const Shape& shape_)
{
	return shape_.put(s);
}

Ellipse::Ellipse(Point center, float r1_, float r2_):
	r1(r1_), r2(r2_)
{
	if ((r1_ <= 0) || (r2_ <= 0))
		throw std::invalid_argument("Radius must be positive");
	id_ellipse++;
	point.push_back(center);	
}

unsigned Ellipse::id_ellipse = 0;

unsigned Ellipse::getId() const
{
	return pow(10, getNumberDigits(id_ellipse)) + id_ellipse;
}

void Ellipse::Scale(float k) 
{
	if (k <= 0)
		throw std::invalid_argument("Coefficient of scale must be positive");
	r1 *= k;
	r2 *= k;
}

ostream& Ellipse::put(ostream& out) const
{
	out << "The figure is ellipse\nwith center in coordinates\n("
		<< point[0].x << "; " << point[0].y << ")\n"
		<< "and radius are r1 = " << r1 << "   r2 = " << r2 << "\n"
		<< "color is " << colors[getColor()] << "\n\n";
	return out;
}

Trapezium::Trapezium(Point topLeftCoord, Point bottomLeftCoord, float topBase_, float bottomBase_):
	topBase(topBase_), bottomBase(bottomBase_)
{
	if ((topLeftCoord.x == bottomLeftCoord.x) && (topLeftCoord.y == bottomLeftCoord.y))
		throw std::invalid_argument("There is not distance between coordinates of left side of trapezium");
	if ((topBase_ <= 0) || (bottomBase_ <= 0))
		throw std::invalid_argument("Bases of trapezium must be positive");
	id_trapezium++;	
	point.push_back(topLeftCoord);
	point.push_back(bottomLeftCoord);
	point.push_back(Point(topLeftCoord.x + topBase, topLeftCoord.y));
	point.push_back(Point(bottomLeftCoord.x + bottomBase, bottomLeftCoord.y));
}

unsigned Trapezium::id_trapezium = 0;

unsigned Trapezium::getId() const
{
	return pow(10, getNumberDigits(id_trapezium))*2 + id_trapezium;
}

void Trapezium::Scale(float k)   
{
	if (k <= 0)
		throw std::invalid_argument("Coefficient of scale must be positive");
	for (int i = 1; i < point.size(); i++)
	{
		point[i].scale(point[0], k);
	}
	topBase *= k; bottomBase *= k;
}

std::string Trapezium::FriendlyName() const
{
	return " ";
}

ostream& Trapezium::put(ostream& out) const
{
	out << "The figure is" << FriendlyName() << "trapezium\nwith coordinates\n";
	for (int i = 0; i < point.size(); i++)
		out << "(" << point[i].x << "; " << point[i].y << ")\n";
	out << "length of basis are top_base = " << topBase << "   bottom_base = " << bottomBase
		<< "\ncolor is " << colors[getColor()] << "\n\n";
	return out;
}

IsoscelesTrapezium::IsoscelesTrapezium(Point topLeftCoord, Point bottomLeftCoord, float bottomBase) :
		Trapezium(topLeftCoord, bottomLeftCoord, -2 * topLeftCoord.x + bottomBase + 2 * bottomLeftCoord.x, bottomBase)
{
	id_isosceles++;
}

unsigned IsoscelesTrapezium::id_isosceles = 0;

unsigned IsoscelesTrapezium::getId() const
{
	return pow(10, getNumberDigits(id_isosceles))*3+id_isosceles;
}

std::string IsoscelesTrapezium::FriendlyName() const
{
	return " isolated ";
}


/*int main()
{
	Shape* Shape = new Trapezium(1,1,2,2,3,4);
	cout << *Shape << (*Shape).getId();
	delete Shape;
	IsoscelesTrapezium tr(Point(2,2), Point(1,1), 6);
	cout << tr;
	tr.Scale(2);
	cout << tr;
	Ellipse el1(0, 0, -1, 1);
	cout  << el1.getId() << "\n";
	Ellipse el2(0, 0, 1, 1);
	cout << el2.getId() << "\n";
	
	return 0;
}*/
