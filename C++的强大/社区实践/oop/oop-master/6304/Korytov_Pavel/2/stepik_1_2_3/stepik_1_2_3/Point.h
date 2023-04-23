#ifndef POINT
#define POINT

#include "stdafx.h"
#include <iostream>

using namespace std;
class Point {
public:
	Point(int xs = 0, int ys = 0) : x(xs), y(ys) {}
	Point(const Point& p) : x(p.x), y(p.y) {}
	~Point() = default;
	Point& Rand(int min, int max);
	//Copy-and-swap
	friend void swap(Point& first, Point& second);
	Point& operator=(Point p);
	Point(Point&& p);
	//Arithmetics
	friend Point operator+(Point & p1, Point & p2);
	friend Point operator-(Point & p1, Point & p2);
	Point& operator/(double i);
	Point& operator*(double i);
	//In-out
	friend ostream& operator<<(ostream& os, const Point& p);
	friend istream& operator >> (istream& is, Point& p);
	//Get, Set
	int GetX() { return x; }
	int GetY() { return y; }
	void SetX(int xs) { x = xs; }
	void SetY(int ys) { y = ys; }
private:
	int x;
	int y;
};

#endif // POINT