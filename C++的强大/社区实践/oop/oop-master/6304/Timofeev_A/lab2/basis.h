#ifndef BASIS_H
#define BASIS_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <complex>

using namespace std;

typedef complex<double>  PentVertex;


class Point {
public:
	Point();

	Point(double _x, double _y);

	void Set_X(double _x);

	void Set_Y(double _y);

	double Get_X() const;

	double Get_Y() const;

private:
	double x;
	double y;
};

class Colour {
public:
	Colour(const int red = 0, const int green = 0, const int blue = 0);

	void SetColour(int _Red, int _Green, int _Blue);

	int GetRed() const;

	int GetGreen()const;

	int GetBlue()const;

private:
	int Red;
	int Green;
	int Blue;
};

ostream& operator<<(ostream &stream, const Colour& rgb);

ostream& operator<<(ostream &stream, const Point& p);

Point operator+(const Point& lhs, const Point& rhs);

Point operator-(const Point& lhs, const Point& rhs);

#endif //BASIS_H