#include "Shape.h"

int Shape::Number = 1;

Shape::Shape(){
	number = Number;
	Number++;
	Colour = "White";
	Angle = 0.0;
}

Shape::~Shape() {
}

void Shape::rotation(double angle) {
	Angle = angle;
	while (Angle >= 360.0)
		Angle -= 360.0;
	while (Angle < 0.0)
		Angle += 360.0;
	std::cout << "The shape number = " << number << " has been rotated by an angle: " << angle << " degree" << std::endl;
}

void Shape::setColour(std::string colour) {
	Colour = colour;
}

std::string Shape::getColour() const {
	return Colour;
}

void Shape::movement(double x, double y) {
	X0 = x;
	Y0 = y;
	std::cout << "The shape number = " << number << " has been moved to a point: (" << x << "," << y << ")" << std::endl;
}

std::ostream &operator << (std::ostream &os, const Shape &shape){
	shape.print(os);
	return os;
}