#include "Right_triangle.h"

Right_triangle::Right_triangle(double x0, double y0, double cath1, double cath2){
	X0 = x0;
	Y0 = y0;
	catheter_one = cath1;
	catheter_two = cath2;
}

Right_triangle::Right_triangle(double x0, double y0, double cath1, double cath2, std::string colour){
	X0 = x0;
	Y0 = y0;
	catheter_one = cath1;
	catheter_two = cath2;
	Colour = colour;
}

Right_triangle::~Right_triangle(){}

double Right_triangle::square(){
	return catheter_one * catheter_two / 2;
}

void Right_triangle::scaling(double zoom){
	if(zoom > 0.0){
		catheter_one *= zoom;
		catheter_two *= zoom;
		std::cout << "The shape number = " << number << " has been scaled to: " << zoom << std::endl;
	}
	else
		std::cout << "The shape number = " << number << " has not been scaled to: " << zoom << "  (" << zoom << " <= 0)" << std::endl;
}

void Right_triangle::print(std::ostream &os) const{
	os << std::endl;
	os << "Figure: Right triangle(Number = " << number << ")" << std::endl;
	os << "Colour: " << getColour() << std::endl;
	os << "Coordinates of the center: (" << X0 << "," << Y0 << ")" << std::endl;
	os << "Size of first catheter: " << catheter_one << std::endl;
	os << "Size of second catheter: " << catheter_two << std::endl;
	os << "Angle of rotation: " << Angle << std::endl;
	os << "Square is " << catheter_one * catheter_two / 2 << std::endl;
	os << std::endl;
}