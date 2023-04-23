#include "circle.h"
#include "sector.h"
#include "trapeze.h"

#include <iostream>
#include <cmath>

#define DEG_TO_RAD(x) x/180.0* M_PI

using namespace std;

void change(Shape& shape) {
	shape.setColor(Color(0, 255, 0));
	shape.setPos(-5, -4);
	shape.scale(2);
	shape.rotate(DEG_TO_RAD(30));	 
}
int main() {

	Circle circle(Point(5,4), 5, Color(12, 12, 12));
	Sector sector(Point(5,4), Point(3, 2), 30, Color(12, 12, 12));
	Trapeze trapeze(Point(1,1), Point(2,5), Point(7,5), Point(11,1), Color(12, 12, 12));

	cout << "============================" << endl;

	circle.printClass(cout);
	cout << endl << "Before:" << endl << circle << endl;
	change(circle);
	cout << "After:" << endl << circle;

	cout << "============================" << endl;

	sector.printClass(cout);
	cout << endl << "Before:" << endl << sector << endl;
	change(sector);
	cout << "After:" << endl << sector;

	cout << "============================" << endl;

	trapeze.printClass(cout);
	cout << endl << "Before:" << endl << trapeze << endl;
	change(trapeze);
	cout << "After:" << endl << trapeze;

	cout << "============================" << endl;

	return 0;
}
