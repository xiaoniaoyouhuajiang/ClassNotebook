#include "stdafx.h"

#include "Trapeze.h" 

void Trapeze::zoom(double n) {
	prepare_for_zoom(n);
	height *= n;
	base1 *= n;
	base2 *= n;
	upperOffset *= n;
}

void Trapeze::printOUT(ostream& out) {
	out << "***Create a Trapeze***" << endl;
	out << "Center: (" << center.x << ", " << center.y << ")" << endl;
	out << "Height: " << height << endl << "Upper base: " << base2 << endl << "Lower base: " << base1 << endl << "Offset: " << upperOffset << endl;
	out << "Main points:" << endl;
	for (const auto& i : points) {
		out << "(" << i.x << ", " << i.y << ")\n";
	}
	out << "Color: " << color << endl;
	out << "Angle: " << angle << endl;
}
