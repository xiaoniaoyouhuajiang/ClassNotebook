#include "SectorEllipse.h"


SectorEllipse::SectorEllipse(){
	X0 = 0.0;
	Y0 = 0.0;
	R1 = 1.0;
	R2 = 1.0;
	Angle1 = 0.0;
	Angle2 = 360.0;
}

SectorEllipse::SectorEllipse(double x0, double y0, double a, double b, double angle1, double angle2) {
	X0 = x0;
	Y0 = y0;
	R1 = a;
	R2 = b;
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

SectorEllipse::SectorEllipse(double x0, double y0, double a, double b, double angle1, double angle2, std::string colour) {
	X0 = x0;
	Y0 = y0;
	R1 = a;
	R2 = b;
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

SectorEllipse::~SectorEllipse(){

}
