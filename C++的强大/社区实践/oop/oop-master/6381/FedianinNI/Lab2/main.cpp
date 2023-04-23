#include <iostream>
#include <cstdlib>
#include "Shape.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Curve.h"

using namespace std;

void testShape() {
	Shape *ptr1 = new Ellipse(5.0, 7.0, 3.1, 2.0);
	cout << *ptr1;
	Shape *ptr2 = new Ellipse(0.0, -3.0, 10.6, 10.3, "Black");
	cout << *ptr2;
	ptr1->Movement(-134.2, 32.0);
	ptr2->setColour("Orange");
	ptr1->Rotation(78.0);
	ptr2->Scaling(5.0);
	cout << endl << *ptr1 << *ptr2;
}

void testEllipse() {
	Ellipse Ellipse1(5.0, 7.0, 3.1, 2.0);
	cout << Ellipse1;
	Ellipse Ellipse2(0.0, -3.0, 10.6, 10.3, "Black");
	cout << Ellipse2;
	Ellipse1.Movement(-134.2, 32.0);
	Ellipse2.setColour("Orange");
	Ellipse1.Rotation(78.0);
	Ellipse2.Scaling(5.0);
	cout << endl << Ellipse1 << Ellipse2;
}

void testCircle() {
	Circle Circle1{};
	cout << Circle1;
	Circle Circle2(4.0, 4.0, 35);
	cout << Circle2;
	Circle Circle3(0.0, -183.0, 10, "Grey");
	cout << Circle3;
	Circle1.Movement(0.2, 11.0);
	Circle1.setColour("Blue");
	Circle2.Rotation(-790.0);
	Circle3.Scaling(4.0);
	cout << endl << Circle1 << Circle2 << Circle3;
}

void testCurve() {
	Curve Curve1(-54.9, -48.3, 5.5, 31.0, 90.0);
	cout << Curve1;
	Curve Curve2(-5.0, 3.0, 65.98, -56, -34, "Yellow");
	cout << Curve2;
	Curve1.Movement(56.8, -117.56);
	Curve1.setColour("Red");
	Curve2.Rotation(1900.0);
	Curve2.Scaling(-43);
	cout << endl << Curve1 << Curve2;
}

int main()
{
	testShape();
	testEllipse();
	testCircle();
	testCurve();
    return 0;
}