#pragma once

#ifndef OOP_Round_H
#define OOP_Round_H
#include "shapes.h"

class Round : public Shape
{

private:
	double radius = 0;
public:
	int Id;
	Round(double radius, const Point &center, const Color &color);
    void rotate(double angle) override;
    void ScaleFigure(double scale) override;
	void setRadius(double radius);
	double getRadius();
	virtual bool isInsideOfAnother(const Shape &other) const override;
	virtual bool isPointInsideOfFigure(const Point &other) const override;
	friend ostream&operator<<(std::ostream &os, const Round &round) {
		os << static_cast<const Shape &>(round) << " radius: " << round.radius <<"ID фигуры: "<< round.Id;
		return os;
	}

		
};
#endif