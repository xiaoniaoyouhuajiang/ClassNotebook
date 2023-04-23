#include "Curve.h"

Curve::Curve(double x0, double y0, double a, double angle1, double angle2) {
	X0 = x0;
	Y0 = y0;
	R = a;
	Angle1 = angle1;
	if (Angle1 >= 360.0) {
		while (Angle1 >= 360.0)
			Angle1 -= 360.0;
	}
	if (Angle1 < 0.0) {
		while (Angle1 < 0.0)
			Angle1 += 360.0;
	}

	Angle2 = angle2;
	if (Angle2 >= 360.0) {
		while (Angle2 >= 360.0)
			Angle2 -= 360.0;
	}
	if (Angle2 < 0.0) {
		while (Angle2 < 0.0)
			Angle2 += 360.0;
	}

	if (Angle2 < Angle1) {
		double temp = Angle1;
		Angle1 = Angle2;
		Angle2 = temp;
	}
}

Curve::Curve(double x0, double y0, double a, double angle1, double angle2, std::string colour) {
	X0 = x0;
	Y0 = y0;
	R = a;
	Angle1 = angle1;
	if (Angle1 >= 360.0) {
		while (Angle1 >= 360.0)
			Angle1 -= 360.0;
	}
	if (Angle1 < 0.0) {
		while (Angle1 < 0.0)
			Angle1 += 360.0;
	}

	Angle2 = angle2;
	if (Angle2 >= 360.0) {
		while (Angle2 >= 360.0)
			Angle2 -= 360.0;
	}
	if (Angle2 < 0.0) {
		while (Angle2 < 0.0)
			Angle2 += 360.0;
	}

	if (Angle2 < Angle1) {
		double temp = Angle1;
		Angle1 = Angle2;
		Angle2 = temp;
	}
	Colour = colour;
}

Curve::~Curve(){}

void Curve::print(std::ostream &os) const{
	os << std::endl;
	os << "Figure: Curve(Number = " << NUMBER << ")" << std::endl;
	os << "Colour: " << getColour() << std::endl;
	os << "Coordinates of the center: (" << X0 << "," << Y0 << ")" << std::endl;
	os << "Radius: " << R << std::endl;
	os << "Angle between the x-axis and the first side: " << Angle1 << std::endl;
	os << "Angle between the x-axis and the second side: " << Angle2 << std::endl;
	os << "Angle of rotation: " << Angle << std::endl;
	os << std::endl;
}