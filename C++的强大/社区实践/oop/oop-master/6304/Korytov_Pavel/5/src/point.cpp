#include "point.h"

void swap(Point & first, Point & second)
{
	swap(first.x, second.x);
	swap(first.y, second.y);
}

ostream & operator<<(ostream & os, const Point & p)
{
	os << "(" << p.x << "," << p.y << ")";
	return os;
}

istream & operator >> (istream & is, Point & p)
{
	is >> p.x >> p.y;
	return is;
}

Point operator+(const Point& p1, const Point& p2) {
	return Point(p1.GetX() + p2.GetX(), p1.GetY() + p2.GetY());
}

Point operator-(const Point& p1, const Point& p2) {
	return Point(p1.GetX() - p2.GetX(), p1.GetY() - p2.GetY());
}

Point& Point::Rand(int min, int max)
{
	this->x = (min + rand() % (max - min));
	this->y = (min + rand() % (max - min));
	return *this;
}

Point & Point::operator=(Point p)
{
	swap(*this, p);
	return *this;
}

Point::Point(Point && p)
{
	swap(*this, p);
}

Point & Point::operator/(double i)
{
	x = x / i;
	y = y / i;
	return *this;
}

Point & Point::operator*(double i)
{
	x = x * i;
	y = y * i;
	return *this;
}

bool operator==(const Point & a, const Point & b){
	return ((a.GetX() == b.GetX()) && (a.GetY() == b.GetY()));
}

double Point::GetPhi() const{
	if ((x == 0) && (y > 0)) return M_PI/2;
	if ((x == 0) && (y < 0)) return 3*M_PI/2;
	if ((x > 0) && (y >= 0)) return atan(y/x);
	if ((x > 0) && (y < 0)) return atan(y/x) + 2*M_PI;
	if (x < 0) return atan(y/x) + M_PI;
	return 0;
}

double Point::SetR(double R){
	double Phi = GetPhi();
	x = R * cos(Phi);
	y = R * sin(Phi);
}

double Point::SetPhi(double Phi){
	double R = GetR();
	x = R * cos(Phi);
	y = R * sin(Phi);
}

void Point::AdjustR(double mult){
	if (mult!=1){
		SetR(GetR()*mult);
	}
}

void Point::AdjustPhi(double angle){
	if (angle!=0){
		SetPhi(GetPhi() + angle);
	}
}
