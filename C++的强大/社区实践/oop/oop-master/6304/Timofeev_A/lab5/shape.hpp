#ifndef SHAPE_H
#define SHAPE_H
#include "basis.h"
	class Shape {
	public:
		Shape(double _x = 0, double _y = 0) : x(_x), y(_y), angle(0), RGB()
		{
			points.push_back(Point(_x, _y));
		}

		virtual ~Shape()
		{
		}

		virtual void ChangeCoordinates(double new_x, double new_y) = 0;

		virtual void Rotate(double new_angle) = 0;

		virtual void Scale(double factor) = 0;

		virtual void SetColour(int r, int g, int b) = 0;

		virtual Colour GetColour() = 0;

		virtual ostream& operator<<(ostream &stream) const = 0;

		virtual Point GetCenter() const = 0;

		virtual void SetPerimetr() = 0;

		virtual double GetPerimetr() const = 0;

	protected:
		double x;
		double y;
		double angle;
		Colour RGB;
		vector<Point> points;
		double perimetr;
	};


#endif //SHAPE_H

