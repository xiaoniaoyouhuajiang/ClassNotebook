#pragma once

#include "circle.h"
#include "fundament.h"

#include <ostream>

#define MAKE_RADIUS(a, b) 2*sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2))

using namespace std;

class Sector: public Circle {
	Point out;
	double angle;

public:
	explicit Sector(Point center, Point out, double angle, 
			Color color = Color(0, 0, 0)): Circle(center, MAKE_RADIUS(center, out), color), out(out), angle(angle)
														{checkAngle(angle);}

	virtual void setPos(Point p) override {fundament::movePoints(center, p, out);}
	virtual void setPos(double x, double y) override {setPos(Point(x, y));}
	void setAngle(double angle) {checkAngle(angle); this->angle = angle;}

	double getAngle() const {return angle;}
												//	Out отдаляется от Center в k раз
	virtual void scale(double k) override {fundament::pullOutFromCenter(center, k, out); Circle::scale(k);}
	virtual void rotate(double angle) override {fundament::rotate(center, angle, out);} //	Угол в радианах.
	virtual void printClass(ostream& stream) {stream << "Class: Sector" << endl;}

	friend ostream& operator <<(ostream& stream, Sector& sector);

private:
	void checkAngle(double a) {if (!a) throw logic_error("Bad angle");}
};

ostream& operator <<(ostream& stream, Sector& sector) {
	stream << dynamic_cast<Circle&>(sector)
	       << "Координаты вспомогательной точки (x, y): " << sector.out.x << " " << sector.out.y << endl
	       << "Угол: " << sector.getAngle() 			   			     << endl;
};
