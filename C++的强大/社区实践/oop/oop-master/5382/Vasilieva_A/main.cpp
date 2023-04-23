#include "shape.h"

int main()
{
	setlocale(LC_ALL, "rus");
	Point center(1,1), leftTopPoint(0, 2);
	//Square sq(center, leftTopPoint);
	Point new_center(2,3), new_leftTopPoint(0, 2);
	double length = 34.5;
	Point leftTopPoint1(1, 0);
	Point center1(0,1);
	sqTriangle sqtr1(Point(0, 0), Point(0, 1), 34.5);
	sqTriangle sqtr2(Point(0, 2), Point(3, 1), 12);
	bool x = isUnionOf(sqtr1, sqtr2);
	cout << x << endl;
//	cout << "Move completed" << endl;
//	sq.moveTo(new_center);
///	sq << cout;
//	cout << "-------------------------------------------------------------" << endl;
//	double length = 34.5;
////	sqTriangle tr();
//	myColor color(0.2, 0.7, 0.4);
//	sqTriangle tr(center, leftTopPoint, length);
//	isosTriangle ir(center, leftTopPoint, length);
//	tr.setColor(color);
//	tr << cout;
//	cout << "-------------------------------------------------------------" << endl;
//	Triangle a(new_center, new_leftTopPoint, length);
////	isUnionOf(tr,ir);
//	a << cout;
//	a.scale(3.0);
//	cout << "Scale completed" << endl;
//	a << cout;
//	
	return 0;
}