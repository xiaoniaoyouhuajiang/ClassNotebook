#pragma once
#include "Vectors.hpp"
#include <iostream>

class Shape
{
public:
	Shape() : Pos({0,0,0}), Angle(0), Color({0,0,0})
	{
		static int _ID = 0;
		++_ID;
		ID = _ID;
	}
	virtual ~Shape() = default;
	const V3i& getColor() const;
	const V3d& getPos() const;
	double getAngle() const;
	int getID() const;
	void setColor(const V3i& newColor);
	virtual void setPos(const V3d& newPos);
	void setAngle(double newAngle);
	virtual void scale(double sc) = 0;
	virtual void print() const = 0;
	friend std::ostream& operator<<(std::ostream& ostr, const Shape& s);
protected:
	V3d Pos;
	double Angle;
	V3i Color;

private:
	int ID;
};
