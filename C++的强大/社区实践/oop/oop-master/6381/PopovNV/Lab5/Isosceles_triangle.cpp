#include "Isosceles_triangle.h"
#include <cmath>

Isosceles_triangle::Isosceles_triangle(double x0, double y0, double Save_side, double angle){
	X0 = x0;
	Y0 = y0;
	save_side = Save_side;
	angle_between_save = angle;
	while(angle >= 180.0)
		angle -=180.0;
	while(angle < 0.0)
		angle +=180.0;
}

Isosceles_triangle::Isosceles_triangle(double x0, double y0, double Save_side, double angle, std::string colour){
	X0 = x0;
	Y0 = y0;
	save_side = Save_side;
	angle_between_save = angle;
	while(angle >= 180)
		angle -=180;
	while(angle < 0)
		angle +=180;
	angle_between_save = angle;
	Colour = colour;
}

Isosceles_triangle::~Isosceles_triangle(){}

double Isosceles_triangle::square(){
	return save_side * save_side * sin(angle_between_save * 3.14159265 / 180) / 2;
}

void Isosceles_triangle::scaling(double zoom){
	if(zoom > 0.0){
		save_side *= zoom;
		std::cout << "The shape number = " << number << " has been scaled to: " << zoom << std::endl;
	}
	else
		std::cout << "The shape number = " << number << " has not been scaled to: " << zoom << "  (" << zoom << " <= 0)" << std::endl;
}

void Isosceles_triangle::print(std::ostream &os) const{
	os << std::endl;
	os << "Figure: Isosceles triangle(Number = " << number << ")" << std::endl;
	os << "Colour: " << getColour() << std::endl;
	os << "Coordinates of the center: (" << X0 << "," << Y0 << ")" << std::endl;
	os << "Size of save sides: " << save_side << std::endl;
	os << "Angle between save sides: " << angle_between_save << std::endl;
	os << "Angle of rotation: " << Angle << std::endl;
	os << "Square is " << save_side * save_side * sin(angle_between_save * 3.14159265 / 180) / 2 << std::endl;
	os << std::endl;
}