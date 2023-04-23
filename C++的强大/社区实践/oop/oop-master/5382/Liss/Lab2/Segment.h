#pragma once
#include "stdafx.h"
#include "Shape.h"
using namespace std;

class Segment : public Shape
{
private:
	double Length ;
	int Id;
public:
	Segment(int, int, int, double, int, string);//, string
	Segment(int Length);
	
	virtual double const FindProjection() const;
	void SetLength(int);
	int GetLength();
	friend ostream&operator<<(ostream&a, const Segment&b) {		
		a << "ID of figure: id=" << b.Id << "\n";
		a << "Center of figure: x=" << b.X << "; y=" << b.Y << "\n";
		a << "Color: " << b.Color << "\n";
		a << "Angle: fi=" << b.Angle << "\n";
		a << "Scale: delta=" << b.Scale << "\n";
		a << "Leight: Side=" << b.Length*b.Scale << "\n";
		
		return a;
	}
	~Segment();
};
