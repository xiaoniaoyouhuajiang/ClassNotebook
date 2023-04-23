#pragma once
#include "polygon.h"

class Rectangle : public Polygon
{
public:
	Rectangle();
	~Rectangle();
	Rectangle(const Point & top, double a, double b);
	Rectangle(const Point & top, double a, double b, std::string red, std::string green, std::string blue);
	Rectangle(const Rectangle & other);
	Rectangle & operator = (const Rectangle & other);
	double get_a() const;
	double get_b() const;
	double & get_a();
	double & get_b();
	double perimeter() const;
	double area() const;
	void scale(double coef = 1);
	void rotate(double angle = 0);							
	void move(const Point & p);	
	bool isItNotRectangle() const;
	void try_catch_rectangle();
	void swap(Rectangle & other);
protected:
	double a;
	double b; 								// длины сторон	
	void out(std::ostream & out_) const override;
};