#include "Shape.h"

int Shape::id = 1;

Shape::Shape(){
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
	std::cout << "The shape ID = "<< ID <<" has been rotated by an angle: " << angle << " degree" << std::endl;
}

void Shape::setColour(std::string colour) {
	Colour = colour;
	std::cout << "The shape ID = " << ID << " has been colored in: " << colour << std::endl;
}

std::string Shape::getColour() const {
	return Colour;
}
