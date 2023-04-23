#include <iostream>
#include <cstdlib>
#include "Shape.h"
#include "Ellipse.h"
#include "Parallelogram.h"
#include "SectorEllipse.h"

using namespace std;

void test1() {
	Ellipse E1{};
	Ellipse E2(5.0, 7.0, 3.1, 2.0);
	Ellipse E3(0.0, -3.0, 10.6, 10.3, "Black");
	cout << E1 << E2 << E3 << endl;
	E1.Movement(-134.2, 32.0);
	E1.setColour("Orange");
	E2.Rotation(78.0);
	E3.Scaling(5.0);
	cout << endl << E1 << E2 << E3 << endl;
}

void test2() {
	Parallelogram P1{};
	Parallelogram P2(3.4, 8.3, 76.9, 2.5, 35);
	Parallelogram P3(0.0, -45.5, 15.6, 11.8, -77, "Pink");
	cout << P1 << P2 << P3 << endl;
	P1.Movement(0.2, 11.0);
	P1.setColour("Blue");
	P2.Rotation(-340.0);
	P3.Scaling(4.0);
	cout << endl << P1 << P2 << P3 << endl;
}

void test3() {
	SectorEllipse S1{};
	SectorEllipse S2(-54.9, -48.3, 5.5, 5.5, 31.0, 90.0);
	SectorEllipse S3(-5.0, 3.0, 34.5, 65.98, -56, -34, "Yellow");
	cout << S1 << S2 << S3 << endl;
	S1.Movement(56.8, -117.56);
	S1.setColour("Red");
	S2.Rotation(0.0);
	S3.Scaling(-43);
	cout << endl << S1 << S2 << S3 << endl;
}

int main()
{
	test1();
	test2();
	test3();
	system("pause");
    return 0;
}

