#include "Trapezium.h"
#include "Shape.h"

#include <iostream>
void Trapezium::print(std::ostream& OS) const {
	OS << "TRAPEZIUM" << std::endl;
	OS << "Color: " << color.R << " " << color.G << " " << color.B << std::endl;
	OS << "id: " << id << std::endl;
}
bool Trapezium::is_trapezium(const std::vector<Dot>& v) {

	double k_1, k_2, k_3, k_4;

	k_1 = (v[1].y - v[0].y) / (v[1].x - v[0].x);
	k_3 = (v[3].y - v[2].y) / (v[3].x - v[2].x);
	k_2 =(v[2].y - v[1].y) / (v[2].x - v[1].x);
	k_4 = (v[3].y - v[0].y) / (v[3].x - v[0].x);

	//xor 
	 k_1 = (k_1 == (-std::numeric_limits<double>::infinity()) ? (std::numeric_limits<double>::infinity()) : k_1);
	 k_2 = (k_2 == (-std::numeric_limits<double>::infinity()) ? (std::numeric_limits<double>::infinity()) : k_2);
	 k_3 = (k_3 == (-std::numeric_limits<double>::infinity()) ? (std::numeric_limits<double>::infinity()) : k_3);
	 k_4 = (k_4 == (-std::numeric_limits<double>::infinity()) ? (std::numeric_limits<double>::infinity()) : k_4);

	if(((k_1==k_3)&&(!(k_2==k_4))) || ((k_1 != k_3) && (!(k_2 != k_4))))
	{
		return true;
	}
	return false;

}