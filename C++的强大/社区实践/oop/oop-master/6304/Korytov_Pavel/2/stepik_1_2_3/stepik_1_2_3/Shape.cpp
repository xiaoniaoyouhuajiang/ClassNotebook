#include "stdafx.h"
#include "Shape.h"

Shape::~Shape()
{
	if (dts) {
		dts = 0;
		delete[] pts;
	}
	col.~Color();
}

Point * Shape::it()
{
	if (pos < dts) {
		return &pts[pos++];
	}
	else {
		pos = 0;
		return nullptr;
	}
}

void Shape::Enter()
{
	for (int i = 0; i < dts; i++) {
		cout << "Enter point #" << i << ": ";
		cin >> pts[i];
	}
	col.Enter();
}

void Shape::Out() {
	Point* ptr;
	while (ptr = it()) {
		cout << *ptr << ", ";
	}
	cout << col << endl;
}

void Shape::Rand(int min, int max) {
	while (Point* ptr = it()) {
		ptr->Rand(min, max);
	}
	col.Rand();
}

//Geometry

Point Shape::GetCenterPoint() {
	Point res;
	Point* ptr;
	while (ptr = it()) {
		res = res + *ptr;
	}
	res = res / dts;
	return res;
}

void Shape::Rotate(int deg) {
	Rotate(deg, GetCenterPoint());
}

void Shape::Rotate(int deg, Point cnt)  //Default rotate
{
	Point* ptr;
	double rad = deg*M_PI / 180;
	Point d;
	Point nd;
	while (ptr = it()) {
		d = *ptr - cnt;
		nd.SetX(d.GetX()*cos(rad) + d.GetY()*sin(rad));
		nd.SetY(d.GetY()*cos(rad) + d.GetX()*sin(rad));
		*ptr = nd + cnt;
	}
}

void Shape::Move(Point delta) {
	while (Point* ptr = it()) {
		*ptr = *ptr + delta;
	}
}

void Shape::MoveAtCoords(Point newp) {
	MoveAtCoords(newp, GetCenterPoint());
}

void Shape::MoveAtCoords(Point newp, Point cnt) {
	Point* ptr;
	Point d;
	while (ptr = it()) {
		d = *ptr - cnt;
		*ptr = d + newp;
	}
}

void Shape::Scale(int c) {
	Scale(c, GetCenterPoint());
}

void Shape::Scale(double c, Point cnt) {
	Point d;
	while (Point* ptr = it()) {
		d = *ptr - cnt;
		d = d * c;
		*ptr = cnt + d;
	}
}

ostream & operator<<(ostream & os, Shape & s)
{
	while (Point* ptr = s.it()) {
		os << *ptr << ", ";
	}
	os << s.col;
	return os;
}

