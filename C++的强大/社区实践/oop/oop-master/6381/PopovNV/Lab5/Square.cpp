#include "Square.h"

Square::Square(double x0, double y0, double Side){
	X0 = x0;
	Y0 = y0;
	side = Side;
}

Square::Square(double x0, double y0, double Side, std::string colour){
	X0 = x0;
	Y0 = y0;
	side = Side;
	Colour = colour;
}
			  
Square::~Square(){}

double Square::square(){
	return side*side;
}

void Square::scaling(double zoom){
	if(zoom > 0.0){
		side *= zoom;
		std::cout << "The shape number = " << number << " has been scaled to: " << zoom << std::endl;
	}
	else
		std::cout << "The shape number = " << number << " has not been scaled to: " << zoom << "  (" << zoom << " <= 0)" << std::endl;
}

void Square::print(std::ostream &os) const{
	os << std::endl;
	os << "Figure: Square(Number = " << number << ")" << std::endl;
	os << "Colour: " << getColour() << std::endl;
	os << "Coordinates of the center: (" << X0 << "," << Y0 << ")" << std::endl;
	os << "Size of side: " << side << std::endl;
	os << "Angle of rotation: " << Angle << std::endl;
	os << "Square is " << side*side << std::endl;
	os << std::endl;
}