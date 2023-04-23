#pragma once

#include "shape.h"
#include "fundament.h"

#include <ostream>

using namespace std;
using namespace fundament;

class Trapeze: public Shape {
	Line b1, b2; // Основания трапеции.

public:
	explicit Trapeze(Point p1, Point p2, Point p3, Point p4, Color color = Color(0, 0, 0));

	virtual void setPos(Point p) override {fundament::movePoints(center, p, b1.p1, b1.p2, b2.p1, b2.p2);}
	virtual void setPos(double x, double y) override {setPos(Point(x, y));}

	Line getBigBase() {return (b1.getLength() > b2.getLength())? b1:b2;}
	Line getSmallBase() {return (b1.getLength() < b2.getLength())? b1:b2;}

	virtual void scale(double k) override {fundament::pullOutFromCenter(center, k, b1.p1, b1.p2, b2.p1, b2.p2);}
	virtual void rotate(double angle) override {fundament::rotate(center, angle, b1.p1, b1.p2, b2.p1, b2.p2);}
	virtual void printClass(ostream& stream) {stream << "Class: Trapeze" << endl;}

	friend ostream& operator <<(ostream& stream, Trapeze& trapeze);

private:
	Point makeCenter();
};

Trapeze::Trapeze(Point p1, Point p2, Point p3, Point p4, Color color): Shape(Point(0,0), color) {
	Line l12 = Line(p1, p2), l34 = Line(p3, p4),
	     l13 = Line(p1, p3), l24 = Line(p2, p4),
	     l14 = Line(p1, p4), l23 = Line(p2, p3);

	if ((p1.x == p2.x && p2.x == p3.x && p3.x == p4.x) ||
 	    (p1.y == p2.y && p2.y == p3.y && p3.y == p4.y))
 		throw logic_error("Bad trapeze");

 	if (l12.getTan() == l34.getTan()) {
 	 	b1 = l12;
 	 	b2 = l34;
 	} else if (l13.getTan() == l24.getTan()) {
 	 	b1 = l13;
 	 	b2 = l24;
 	} else if (l14.getTan() == l23.getTan()) {
 	 	b1 = l14;
 	 	b2 = l23;
 	} else 
 	 	throw logic_error("Bad trapeze");
	
	center = makeCenter();
}

Point Trapeze::makeCenter() {
	return Point((b1.p1.x + b1.p2.x + b2.p1.x + b2.p2.x)/4.0,
		     (b1.p1.y + b1.p2.y + b2.p1.y + b2.p2.y)/4.0);
}

ostream& operator <<(ostream& stream, Trapeze& trapeze) {
	stream << dynamic_cast<Shape&>(trapeze) 
		   << "Длина меньшего основания: " << trapeze.getSmallBase().getLength() << endl
		   << "Длина большего основания: " << trapeze.getBigBase().getLength()   << endl;
}
