#pragma once

#ifndef OOP_Pentagon_H
#define OOP_Pentagon_H
#include "shapes.h"

class Pentagon : public Shape {

public:
	vector<Point> points;
	int Id;
	Pentagon(const Point &p1, const Point &p2, const Point &p3, const Point &p4, const Point &p5, const Color &color);
	Pentagon(const Color &color);

	void rotate(double angle) override;
	void ScaleFigure(double scale) override;
	friend ostream &operator<<(ostream &os, const Pentagon &pentagon) {
		os << static_cast<const Shape &>(pentagon) << " points: ";
		for (int i = 0; i < 5; ++i) {
			os << pentagon.points[i] << " ";
		}
		os << "ID фигуры: " << pentagon.Id;
		return os;
	}

	void Move(double dx, double dy) override;
	virtual bool isInsideOfAnother(const Shape &other) const override;
	virtual bool isPointInsideOfFigure(const Point &other) const override;
	virtual double getSquare() const;
	double countSquareForPoint(const Point &other) const;
	
};
#endif