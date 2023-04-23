#pragma once

#include <cmath>
#include <ostream>

using namespace std;

using uc = unsigned char;

namespace fundament { 
struct Color {
	uc red, green,blue;

	Color(uc red, uc green, uc blue): red(red), green(green), blue(blue) {}
};

struct Point {
	double x, y;

	Point(double x, double y): x(x), y(y) {}
};

struct Line {
	Point p1, p2;

	Line(Point p1, Point p2): p1(p1), p2(p2) {}
	Line(): p1(Point(0, 0)), p2(Point(0,0)) {}

	double getLength() const {return sqrt(pow(abs(p1.x - p2.x), 2) + pow(abs(p1.y - p2.y), 2));}
	double getTan() const {return (p1.y - p2.y) / (p1.x - p2.x);}
};

void rotate(Point center, double angle) {}

template <typename Type, typename... Types>
void rotate(Point center, double angle, Type &out, Types&... outs) {	//	Угол в радианах.
    if (angle > 0) 	// Поворот out по часовой стрелке вокруг center.
    	out = Point((out.x - center.x)*cos(angle) - (out.y - center.y)*sin(angle) + center.x,
                    (out.x - center.x)*sin(angle) + (out.y - center.y)*cos(angle) + center.y);
    else if (angle < 0)	// Поворот out против часовой стрелке вокруг center.
        out = Point((out.x - center.x)*cos(angle) + (out.y - center.y)*sin(angle) + center.x,
                   -(out.x - center.x)*sin(angle) + (out.y - center.y)*cos(angle) + center.y);
    rotate(center, angle, outs...);
}

void movePoints(Point& center, Point& new_center) {center = new_center;}

template <typename Type, typename... Types>
void movePoints(Point& center, Point& new_center, Type& other, Types&... others) {
	other = Point(other.x + new_center.x - center.x, other.y + new_center.y - center.y);
	movePoints(center, new_center, others...);
}

void pullOutFromCenter(Point center, double k) {}

template <typename Type, typename... Types>
void pullOutFromCenter(Point center, double k, Type& out, Types&... outs) {	//	Out отдаляется от Center в k раз
	if (k <= 0)
		throw logic_error("Bad scale");

	if (center.y >= out.y)
		out.y = center.y - abs(center.y - out.y)*k;
    	else
    		out.y = center.y + abs(center.y - out.y)*k;

	if (center.x >= out.x)
		out.x = center.x - abs(center.x - out.x)*k;
    	else
    		out.x = center.x + abs(center.x - out.x)*k;

    pullOutFromCenter(center, k, outs ...);
}

bool operator ==(Point p1, Point p2) {return p1.x == p2.x && p1.y == p2.y;}
}
