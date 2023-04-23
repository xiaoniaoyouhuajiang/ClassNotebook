#include "Ellipse.h"
#include <math.h>


Ellipse::Ellipse(double x, double y, int rad1, int rad2, string color) : centre(x, y), rad1(rad1), rad2(rad2),
color(color)
{
	vertex.push_back(Point((centre.getX() - rad1), centre.getY()));
	vertex.push_back(Point(centre.getX(), (centre.getY() + rad2)));
	vertex.push_back(Point((centre.getX() + rad1), centre.getY()));
	vertex.push_back(Point(centre.getX(), (centre.getY() - rad2)));
}

void Ellipse::scale(double k)
{
	vertex[0].setX(vertex[0].getX() - (k - 1)*rad1);
	vertex[1].setY(vertex[1].getY() + (k - 1)*rad2);
	vertex[2].setX(vertex[2].getX() + (k - 1)*rad1);
	vertex[3].setY(vertex[3].getY() - (k - 1)*rad2);
	rad1 *= k;
	rad2 *= k;
}

ostream& operator << (ostream &out, Ellipse &el) {
	out << "Ellipse: color(" << el.color << "), centre( " << el.centre.getX() << "; " << el.centre.getY() << "), ";
	out << "rad1: " << el.rad1 << ", rad2: " << el.rad2 << endl;
	return out;
}


