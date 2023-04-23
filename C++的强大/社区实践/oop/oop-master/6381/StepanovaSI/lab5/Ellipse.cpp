#include "Ellipse.h"

Ellipse::Ellipse() {
	X0 = 0.0;
	Y0 = 0.0;
	R1 = 1.0;
	R2 = 1.0;
};

Ellipse::Ellipse(double x0, double y0, double a, double b) {
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

Ellipse::~Ellipse() {
}

void Ellipse::Scaling(double zoom) {
	if (zoom > 0.0) {
		R1 *= zoom;
		R2 *= zoom;
		std::cout << "The shape ID = " << ID << " has been scaled to: " << zoom << std::endl;
	}
	else
		std::cout << "The shape ID = " << ID << " has not been scaled to: " << zoom << "  (" << zoom << " <= 0)" << std::endl;
}
