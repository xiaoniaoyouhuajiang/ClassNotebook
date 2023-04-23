#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include "Point.h"
#include "Shape.h"
#include "Line.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"

using namespace std;

int main()
{
	srand(time(0));
	//----------------------------
	cout << "===|Base constructor test|===" << endl;
	Shape s(5);
	s.Rand(0, 100); 
	cout << s << endl;
	//----------------------------
	cout << "===|Base center test|===" << endl;
	cout << s.GetCenterPoint() << endl;
	//----------------------------
	cout << "===|Base rotate test|===" << endl;
	for (int i = 0; i <= 360; i = i + 90) {
		s.Rotate(90);
		cout << i << ": ";
		cout << s << endl;
	}
	//----------------------------
	cout << "===|Base move test|===" << endl;
	s.Move(Point(20, 20));
	cout << s << endl;
	//----------------------------
	cout << "===|Base move at coordinates test|===" << endl;
	s.MoveAtCoords(Point(1000, 1000));
	cout << s.GetCenterPoint() << endl;
	cout << s << endl;
	s.MoveAtCoords(Point(0, 0));
	cout << s.GetCenterPoint() << endl;
	s.Out();
	//----------------------------
	cout << "===|Base scale test|===" << endl;
	s.Scale(10);
	s.Out();
	//----------------------------
	cout << "===|Line test|===" << endl;
	Line l;
	l.Rand(0, 100);
	cout << l << endl;
	cout << l.Length() << endl;
	//----------------------------
	cout << "===|Line rotate test|===" << endl;
	l.RotateAroundStart(90);
	l.Out();
	l.RotateAroundEnd(90);
	l.Out();
	//----------------------------
	cout << "===|Rectangle test|===" << endl;
	Rectangle r;
	r.Rand(0, 100);
	cout << r << " " << r.isValid() << endl;
	//----------------------------
	cout << "===|Triangle test|===" << endl;
	Triangle t;
	t.Rand(0, 100);
	cout << t << endl;
	cout << t.GetCenterPoint() << endl;
	//----------------------------
	cout << "===|Triangle rotate test|===" << endl;
	t.Rotate(90);
	cout << t << endl;
	//----------------------------
	cout << "===|Circle test|===" << endl;
	Circle c;
	c.Rand(0, 100);
	cout << c << endl;
	//----------------------------
	cout << "===|Circle rotate test|===" << endl;
	c.Rotate(90);
	cout << c << endl;
	Point p = p.Rand(0, 100);
	c.Rotate(90, p);
	cout << p << ": " << c << endl;
	//----------------------------
	cout << "===|Circle scale test|===" << endl;
	c.Scale(10);
	cout << c << endl;
	p.Rand(0, 100);
	c.Scale(10, p);
	cout << p << ": " << c << endl;
	return 0;
}

