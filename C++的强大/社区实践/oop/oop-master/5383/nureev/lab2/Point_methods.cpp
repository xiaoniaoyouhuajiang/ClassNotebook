#include "point.h"

double Point::getX()

{

	return X;

}

double Point::getY()

{

	return Y;

}

void Point::setX(double x)

{

	X = x;

}

void Point::setY(double y)

{

	Y = y;

}

Point::Point(double InitX, double InitY)

{

	X = InitX;

	Y = InitY;

}

Point::Point()

{

	X = 0.0;

	Y = 0.0;

}