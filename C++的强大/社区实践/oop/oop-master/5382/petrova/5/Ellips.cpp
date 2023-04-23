
#include "Shape.h"

Ellips::Ellips(Point center, int _R, int _r)
{
	this->center = center;
	this->R=_R;
	this->r = _r;
	this->left = left;
	this->color.r = 0;
	this->color.g = 0;
	this->color.b = 0;
}

void Ellips::move(Point newCenter)
{
		this->left.x = this->center.x - this->R;
		this->left.y = this->center.y;
		this->left.x -= center.x - newCenter.x;
		this->left.y -= center.y - newCenter.y;
		this->center = newCenter;
}

void Ellips::turn(double angle)
{	
	double x_new, y_new;
	this->left.x = this->center.x - this->R;
	this->left.y = this->center.y;
	x_new = this->center.x + (this->left.x - this->center.x)*cos(angle) - (this->left.y - this->center.y)*sin(angle);
	y_new = this->center.y + (this->left.x - this->center.x)*sin(angle) + (this->left.y - this->center.y)*cos(angle);
	this->left.x = x_new;
	this->left.y = y_new;
}

void Ellips::changesize(double k)
{
	R = R*k;
	r = r*k;
}

 
double const Ellips::leftx() const
{
	double l;
	l = this->center.x - this->R;
	return l;
}

