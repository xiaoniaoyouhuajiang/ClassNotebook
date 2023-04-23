#include "Shape.h"

int Shape::ID = 0;

Shape::Shape(const Point &center, const Color &color) : center(center), color(color) {}

Point Shape::GetCenter() const {
	return center;
}

Color Shape::getColor() const {
	return color;
}


void Shape::SetColor(const Color &color) {

	this->color = color;
}

void Shape::Move(double dx, double dy) {
	center.x = center.x + dx;
	center.y = center.x + dy;
}

double Shape::Length(const Point &p1, const Point &p2) {
	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

double Shape::triangleS(const Point &p1, const Point &p2, const Point &p3) {
	double a = Length(p1, p2);
	double b = Length(p1, p3);
	double c = Length(p2, p3);
	double p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}


Shape::~Shape() {
}
