#include "Parallelogram.h"

Parallelogram::Parallelogram() {
	X0 = 0.0;
	Y0 = 0.0;
	D1 = 1.0;
	D2 = 1.0;
	AngleBetweenDiagonal = 90.0;
}

Parallelogram::Parallelogram(double x0, double y0, double a, double b, double angle) {
	X0 = x0;
	Y0 = y0;
	D1 = a;
	D2 = b;
	AngleBetweenDiagonal = angle;
	if (AngleBetweenDiagonal >= 360.0) {
		while (AngleBetweenDiagonal >= 360.0)
			AngleBetweenDiagonal -= 360.0;
	}
	if (AngleBetweenDiagonal< 0.0) {
		while (AngleBetweenDiagonal < 0.0)
			AngleBetweenDiagonal += 360.0;
	}
}

Parallelogram::Parallelogram(double x0, double y0, double a, double b, double angle, std::string colour) {
	X0 = x0;
	Y0 = y0;
	D1 = a;
	D2 = b;
	AngleBetweenDiagonal = angle;
	if (AngleBetweenDiagonal >= 360.0) {
		while (AngleBetweenDiagonal >= 360.0)
			AngleBetweenDiagonal -= 360.0;
	}
	if (AngleBetweenDiagonal< 0.0) {
		while (AngleBetweenDiagonal < 0.0)
			AngleBetweenDiagonal += 360.0;
	}
	Colour = colour;
}

Parallelogram::~Parallelogram() {

}

void Parallelogram::Scaling(double zoom) {
	if (zoom > 0.0) {
		D1 *= zoom;
		D2 *= zoom;
		std::cout << "The shape ID = " << ID << " has been scaled to: " << zoom << std::endl;
	}
	else
		std::cout << "The shape ID = " << ID << " has not been scaled to: " << zoom << "  (" << zoom << " <= 0)" << std::endl;
}
