#include "shape.h"

class Square : public Shape
{
private:
	Point leftTop;
	double length;
public:
	Square(Point center, Point leftTop); //: Shape()
	void move_to(Point newCenter);
	void rotate(double angle);
	void scale(double k);
};