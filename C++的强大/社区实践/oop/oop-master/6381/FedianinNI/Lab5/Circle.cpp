#include "Circle.hpp"

Circle::Circle() { // Окружность с 0 радиусом (точка)
	X0 = 0.0;
	Y0 = 0.0;
	R = 0.0;
};

Circle::Circle(double x0, double y0, double a){
	X0 = x0;
	Y0 = y0;
	R = a;
}

Circle::Circle(double x0, double y0, double a, std::string colour) {
	X0 = x0;
	Y0 = y0;
	R = a;
	Colour = colour;
}

//Circle::~Circle(){}

void Circle::Scaling(double zoom) {
	if (zoom > 0.0) {
		R *= zoom;
		std::cout << "The shape number = " << NUMBER << " has been scaled to: " << zoom << std::endl;
	}
	else
		std::cout << "The shape number = " << NUMBER << " has not been scaled to: " << zoom << "  (" << zoom << " <= 0)" << std::endl;
}

void Circle::print(std::ostream &os) const{
	os << std::endl;
	os << "Figure: Circle(Number = " << NUMBER << ")" << std::endl;
	os << "Colour: " << getColour() << std::endl;
	os << "Coordinates of the center: (" << X0 << "," << Y0 << ")" << std::endl;
	os << "Radius: " << R << std::endl;
	os << "Angle of rotation: " << Angle << std::endl;
	os << std::endl;
}