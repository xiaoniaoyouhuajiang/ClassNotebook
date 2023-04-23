#pragma once

#include "fundament.h"

#include <ostream>

using namespace std;
using namespace fundament;

using ulli = unsigned long long int;

class Shape {
	static ulli number_of_shapes;
	ulli id;

protected:
	Point center;
	Color color;

public:
	explicit Shape(Point center, Color color = Color(0, 0, 0)): center(center), color(color) {id = ++number_of_shapes;}

	virtual void setPos(double x, double y) {center = Point(x, y);}
	virtual void setPos(Point p) {center = p;}
	void setColor(Color color) {this->color = color;}

	ulli getId() const {return id;}
	Color getColor() const {return color;}
	Point getPos() const {return center;}

	virtual void rotate(double Angle) = 0;
	virtual void scale(double k) = 0;
	virtual void printClass(ostream& stream) = 0;

	virtual ~Shape(){--number_of_shapes;}

	friend ostream& operator <<(ostream& stream, Shape& shape);

protected:
	void checkScale(double k) {if (k <= 0) throw logic_error("Bad scale");}
};

ulli Shape::number_of_shapes = 0;

ostream& operator <<(ostream& stream, Shape& shape) {
	stream << "Id: "		   << shape.getId()		  << endl
		   << "Координаты (x,y): " << shape.getPos().x		  << " "
					   << shape.getPos().y		  << endl

		   << "Цвет (RGB): "	   << (int)shape.getColor().red	  << " "
		   			   << (int)shape.getColor().green << " "
		   			   << (int)shape.getColor().blue  << endl;
}
