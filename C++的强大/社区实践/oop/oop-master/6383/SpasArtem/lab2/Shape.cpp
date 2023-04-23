#include "Shape.h"
#include <math.h>
using namespace std;

void Shape::move(double new_x, double new_y)
{
	double dx = new_x - centre.getX();
	double dy = new_y - centre.getY();
	for (int i = 0; i < vertex.size(); i++)
	{
		vertex[i].setX(vertex[i].getX() + dx);
		vertex[i].setY(vertex[i].getY() + dy);
	}
	centre.setX(new_x);
	centre.setY(new_y);
}

void Shape::turn(double angle)
{
	for (int i = 0; i < vertex.size(); i++)
	{
		vertex[i].setX(vertex[i].getX()*cos(angle) - vertex[i].getY()*sin(angle));
		vertex[i].setY(vertex[i].getX()*sin(angle) + vertex[i].getY()*cos(angle));
	}
}