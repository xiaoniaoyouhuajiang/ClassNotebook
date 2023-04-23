#pragma once
#include "stdafx.h"
#include "Shape.h"

class Ellips : public Shape
{
private:
	int  SmallAxle, BigAxle;
	int Id;
public:
	//enum ñolor { Black, White, Pink, Blue } col;
	Ellips(int, int, int, int, double, int, string);//, string
	Ellips(int, int);
	
	virtual double const FindProjection() const;
	int GetSAxle();
	int GetBAxle();
	void SetAxles(int, int);
	friend ostream&operator<<(ostream&a, const Ellips&b) {	
		a << "ID of figure: id=" << b.Id << "\n";
		a << "Center of figure: x=" << b.X << "; y=" << b.Y << "\n";
		a << "Color: " << b.Color << "\n";
		a << "Angle: fi=" << b.Angle << "\n";
		a << "Scale: delta=" << b.Scale << "\n";
		a << "Height of ellips=" << b.BigAxle*b.Scale << "  Width of ellips="<< b.SmallAxle*b.Scale <<"\n";
		
		return a;
	}
	~Ellips();
};