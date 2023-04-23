#pragma once
#include "polygon.h"

class Triangle : public Polygon
{
public:
	Triangle();
	~Triangle();
	Triangle(const Point & p_1, const Point & p_2, const Point & p_3);
	Triangle(const Point & p_1, const Point & p_2, const Point & p_3, std::string red, std::string green, std::string blue);
	Triangle(const Triangle & other);
	Triangle & operator = (const Triangle & other);
	double get_a() const;
	double get_b() const;
	double get_c() const;
	double & get_a();
	double & get_b();
	double & get_c();
	void scale(double coef = 1);
	void rotate(double angle = 0);							
	void move(const Point & p);										
	double perimeter() const;
	double area() const;
	bool isItNotTriangle() const;
	void try_catch_triangle();
protected:
	double a;
	double b;
	double c; 									// длины сторон треугольника
	void out(std::ostream & out_) const override;
	void swap(Triangle & other);
};