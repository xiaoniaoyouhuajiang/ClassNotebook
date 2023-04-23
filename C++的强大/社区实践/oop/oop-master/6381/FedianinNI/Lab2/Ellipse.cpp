#include "Ellipse.h"

Ellipse::Ellipse(double x0, double y0, double a, double b){
	X0 = x0;
	Y0 = y0;
	R1 = a;
	R2 = b;
}

Ellipse::Ellipse(double x0, double y0, double a, double b, std::string colour) {
	X0 = x0;
	Y0 = y0;
	R1 = a;
	R2 = b;
	Colour = colour;
}

Ellipse::~Ellipse(){
}

void Ellipse::Scaling(double zoom) {
	if (zoom > 0.0) {
		R1 *= zoom;
		R2 *= zoom;
		std::cout << "The shape number = " << NUMBER << " has been scaled to: " << zoom << std::endl;
	}
	else
		std::cout << "The shape NUMBER = " << NUMBER << " has not been scaled to: " << zoom << "  (" << zoom << " <= 0)" << std::endl;
}

void Ellipse::print(std::ostream &os) const{
	os << std::endl;
	os << "Figure: Ellipse(Number = " << NUMBER << ")" << std::endl;
	os << "Colour: " << getColour() << std::endl;
	os << "Coordinates of the center: (" << X0 << "," << Y0 << ")" << std::endl;
	os << "First radius: " << R1 << std::endl;
	os << "Second radius: " << R2 << std::endl;
	os << "Angle of rotation: " << Angle << std::endl;
	os << std::endl;
}