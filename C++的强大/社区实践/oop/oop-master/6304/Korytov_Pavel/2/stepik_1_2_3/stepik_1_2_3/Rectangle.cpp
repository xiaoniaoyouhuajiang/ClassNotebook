#include "stdafx.h"
#include "Rectangle.h"

Rectangle::Rectangle() : Shape(4)
{
}

Rectangle::Rectangle(Point lu, Point rd, Color clr): Shape(4, clr){
    Point ld(lu.GetX(), rd.GetY());
    Point ru(rd.GetX(), lu.GetY());
    this->pts[0] = lu;
    this->pts[1] = ld;
    this->pts[2] = ru;
    this->pts[3] = rd;
}

Rectangle::Rectangle(int lux, int luy, int rdx, int rdy, Color clr) : Rectangle(Point(lux, luy), Point(rdx, rdy), clr){
}

Rectangle::Rectangle(Point lu, Point ld, Point ru, Point rd, Color clr): Shape(4, clr){
    this->pts[0] = lu;
    this->pts[1] = ld;
    this->pts[2] = ru;
    this->pts[3] = rd;
}

Rectangle::Rectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, Color clr)
   : Rectangle(Point(x1, y1), Point(x2, y2), Point(x3, y3), Point(x4, y4), clr) {}

void Rectangle::Enter(){
    cout << "Enter left up point: ";
    cin >> this->pts[0];
    cout << "Enter left down point: ";
    cin >> this->pts[1];
    cout << "Enter right up point: ";
    cin >> this->pts[2];
    cout << "Enter right down point: ";
    cin >> this->pts[3];
}

void Rectangle::Rand(int min, int max)
{
	Point lu, rd, delta;
	lu.Rand(min, max);
	delta.Rand(min, max);
	rd = lu + delta;
	Point ld(lu.GetX(), rd.GetY());
	Point ru(rd.GetX(), lu.GetY());
	this->pts[0] = lu;
	this->pts[1] = ld;
	this->pts[2] = ru;
	this->pts[3] = rd;
}

bool Rectangle::isValid(){
    Line a(LeftUp(), LeftDown());
    Line b(LeftUp(), RightUp());
    Line c(LeftDown(), RightDown());
    Line d(RightUp(), RightDown());
    bool res = 1;
	res = ((a.Length() == d.Length()) && (b.Length() == c.Length()));
    res = res && (a.ScalarMult(b) == 0);
    res = res && (b.ScalarMult(d) == 0);
    res = res && (c.ScalarMult(d) == 0);
    res = res && (d.ScalarMult(b) == 0);
    return res;
}