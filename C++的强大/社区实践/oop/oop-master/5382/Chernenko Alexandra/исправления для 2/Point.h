#pragma once
#include "stdafx.h"
class Point{
private:
	double x, y;
public:
	Point(double, double);
	void setCoord(double, double);
	void setX(double);
	void setY(double);
	/*double* getCoord();*/
	double getX() const;
	double getY() const;
	bool operator ==(Point const & b) const
	{
		if (x == b.getX() && y == b.getY()) return true;
		else return false;
	}

};
