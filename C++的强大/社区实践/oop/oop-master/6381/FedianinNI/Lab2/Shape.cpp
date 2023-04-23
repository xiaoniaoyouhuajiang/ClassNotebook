#include "Shape.h"

int Shape::number = 1;

Shape::Shape(){
	NUMBER = number;
	number++;
	Colour = "White";
	Angle = 0.0;
}

Shape::~Shape() {
}

void Shape::Rotation(double angle) {
	Angle = angle;
	if (Angle >= 360.0) {
		while (Angle >= 360.0)
			Angle -= 360.0;
	}
	if (Angle < 0.0) {
		while (Angle < 0.0)
			Angle += 360.0;
	}
	std::cout << "The shape number = "<< NUMBER <<" has been rotated by an angle: " << angle << " degree" << std::endl;
}

void Shape::setColour(std::string colour) {
	Colour = colour;
	std::cout << "The shape number = " << NUMBER << " has been colored in: " << colour << std::endl;
}

std::string Shape::getColour() const {
	return Colour;
}

void Shape::Movement(double x, double y) {
	X0 = x;
	Y0 = y;
	std::cout << "The shape Number = " << NUMBER << " has been moved to a point: (" << x << "," << y << ")" <<std::endl;
}

std::ostream &operator << (std::ostream &os, const Shape &shape){
	shape.print(os);
	return os;
}