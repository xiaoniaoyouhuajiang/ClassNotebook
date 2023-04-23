#include "stdafx.h"
#include "Circle.h"


Circle::Circle() : Shape(1), rad(0)
{
}

Circle::Circle(int x, int y, int r, Color clr) : Circle(Point(x,y), r, clr)
{
}

void Circle::Enter()
{
	cout << "Enter center point: ";
	cin >> pts[0];
	cout << "Enter radius: ";
	cin >> rad;
	cout << "Enter color: ";
	col.Enter();
}

void Circle::Out()
{
	cout << pts[0] << " - " << rad << "; " << col << endl;
}

void Circle::Rand(int min, int max)
{
	pts[0].Rand(min, max);
	rad = (min + rand() % (max - min));
	col.Rand();
}

void Circle::Scale(int c)
{
	Scale(c, GetCenterPoint());
}

void Circle::Scale(int c, Point cnt)
{
	Point d;
	d = pts[0] - cnt;
	d = d * c;
	pts[0] = cnt + d;
	rad = rad * c;
}

Circle::Circle(Point x, int r, Color clr) : Shape(1, clr), rad(r)
{
	pts[0] = x;
}


ostream & operator<<(ostream & os, Circle & s)
{
	os << s.pts[0] << " - " << s.rad << " " << s.col;
	return os;
}
