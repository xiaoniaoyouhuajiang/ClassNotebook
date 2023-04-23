#pragma once

#include "shape.h"

#include <ostream>

using namespace std;

class Circle: public Shape {
	double radius;

public:
	explicit Circle(Point center, 
			double radius, 
			Color color = Color(0, 0, 0)): Shape(center, color), radius(radius) {checkRadius(radius);}

	void setRadius(double radius) {checkRadius(radius); this->radius = radius;}

	double getRadius() const {return radius;}

	virtual void scale(double k) override {checkScale(k); this->radius *= k;}
	virtual void printClass(ostream& stream) {stream << "Class: Circle" << endl;}

	friend ostream& operator <<(ostream& stream, Circle& circle);

protected:
	virtual void rotate(double angle) {};

private:
	void checkRadius(double r) {if (r <= 0) throw logic_error("Bad radius");}
};

ostream& operator <<(ostream& stream, Circle& circle) {
	stream << dynamic_cast<Shape&>(circle) 
	       << "Радиус: " << circle.getRadius() << endl;
}
