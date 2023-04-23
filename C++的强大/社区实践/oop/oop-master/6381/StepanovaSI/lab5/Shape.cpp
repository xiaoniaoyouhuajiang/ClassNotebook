#include "Shape.h"

int Shape::id = 1;

Shape::Shape() {
	ID = id;
	id++;
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
	std::cout << "The shape ID = " << ID << " has been rotated by an angle: " << angle << " degree" << std::endl;
}

void Shape::setColour(std::string colour) {
	Colour = colour;
	std::cout << "The shape ID = " << ID << " has been colored in: " << colour << std::endl;
}

void Shape::Movement(double x, double y) {
	X0 = x;
	Y0 = y;
	std::cout << "The shape ID = " << ID << " has been moved to a point: (" << x << "," << y << ")" << std::endl;
}

std::string Shape::getColour() const {
	return Colour;
}

void Shape::printCentre() {
	std::cout << "The Shape ID = " << ID << " has the coordinates of the center: (" << X0 << "," << Y0 << ")" << std::endl;
}

double Shape::getX0() {
	return X0;
}

double Shape::getY0() {
	return Y0;
}

bool Shape::compareCentre(Shape* other) {
	return (X0 == other->getX0()) && (Y0 == other->getY0());
}
