#include "Square.h"
#include <iostream>


bool Square::is_square(const std::vector<Dot>& v) {
	double k_1, k_2, k_3, k_4;
	k_1 = fabs((v[1].y - v[0].y) / (v[1].x - v[0].x));
	k_3 = fabs((v[3].y - v[2].y) / (v[3].x - v[2].x));
	k_2 = fabs((v[2].y - v[1].y) / (v[2].x - v[1].x));
	k_4 = fabs((v[3].y - v[0].y) / (v[3].x - v[0].x));

	if ((k_1 == k_3) && (k_2 == k_4)) {
		return true;
	}
	return false;

}

void Square::print(std::ostream& OS) const {
	OS << "SQUARE" << std::endl;
	OS << "Color: " << color.R << " " << color.G << " " << color.B << std::endl;
	OS << "id: " << id << std::endl;
}