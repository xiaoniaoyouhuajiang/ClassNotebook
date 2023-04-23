#include "Point.h"
#include <iostream>
using namespace std;

Point::Point()
{
	x = 0;
	y = 0;
}
	
Point::Point(double x0, double y0)
{
	x = x0;
	y = y0;
}

void Point::ShowPoint()
{
	cout << "Координаты точки x = " << x << endl;
	cout << "Координаты точки y = " << y << endl;
}