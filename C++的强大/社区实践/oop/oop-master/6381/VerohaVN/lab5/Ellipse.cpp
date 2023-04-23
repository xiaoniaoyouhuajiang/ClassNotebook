#include "stdafx.h"
#include "Ellipse.h" 

void Ellipse::zoom(double n) {
	radiusX *= n;
	radiusY *= n;

	points.clear();
	points.push_back(Point((center.x - radiusX), center.y));
	points.push_back(Point(center.x, (center.y + radiusY)));
	points.push_back(Point((center.x + radiusX), center.y));
	points.push_back(Point(center.x, (center.y - radiusY)));
}

void Ellipse::printOUT(ostream& out) {
	out << "***Create an Ellipse***" << endl;
	out << "Center: (" << center.x << ", " << center.y << ")" << endl;
	out << "Radius lengths: " << radiusX << " , " << radiusY << endl;
	out << "Main points:" << endl;
	for (const auto& i : points) {
		out << "(" << i.x << ", " << i.y << ")\n";
	}
	out << "Color: " << color << endl;
	out << "Angle: " << angle << endl;
}