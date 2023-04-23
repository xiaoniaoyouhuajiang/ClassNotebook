#pragma once
#include "shape.h"
#include "rectangle.h"

class Square : public Rectangle
{
public:
	Square();
	~Square();
	Square(const Point & top, const double x);	
	Square(const Point & top, const double x, std::string red, std::string green, std::string blue);		
	Square(const Square & other);
	bool isItNotSquare() const;
	void scale(double coef = 1);
	void rotate(double angle = 0);							
	void move(const Point & p);	
	void try_catch_square();
private: 
	void out(std::ostream & out_) const override;
};