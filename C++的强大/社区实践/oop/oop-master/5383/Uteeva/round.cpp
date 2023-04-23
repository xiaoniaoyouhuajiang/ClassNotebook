#include "stdafx.h"
#include "round.h"
#include <cmath> 
#include <vector>

Round::Round (double radius, const Point &center, const Color &color) : Shape(center, color) {
	this->setRadius(radius);
	Id = ID;
	ID++;
}

void Round::rotate(double angle) {}

void Round::ScaleFigure(double scale) {
	if (scale > 0) {
		radius = radius*scale;
	}
	else {
		throw std::invalid_argument("Неправильный коэфициент! \n");
	}
}



void Round::setRadius(double radius) {
	if (radius > 0) {
		this->radius = radius;
	}
	else {
		throw std::invalid_argument("Некорректный радиус! \n");
	}
}

double Round::getRadius() {
	return radius;
}



bool Round::isPointInsideOfFigure(const Point &other) const {
	double l = pow(other.x - center.x, 2) + pow(other.y - center.y, 2);
	return l <= pow(radius, 2);
}

bool Round::isInsideOfAnother(const Shape &other) const {
	const int POINT_QUANITY = 64;
	
	double angleInRadians = (360 / POINT_QUANITY) / 180 * 3.14;
	double c = cos(angleInRadians);
	double s = sin(angleInRadians);
	double x = center.x + radius;
	double y = center.y;
	double rx, ry;

	for (int i = 0; i < POINT_QUANITY; ++i) {
		if (!other.isPointInsideOfFigure(Point(x, y))) {
			return false;
		}
		rx = x - center.x;
		ry = y - center.y;
		x = center.x + rx * c - ry * s;
		y = center.y + rx * s + ry * c;
	}

	return true;
}


