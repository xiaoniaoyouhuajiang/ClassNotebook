#include "Shape.h"

SegEl::SegEl(Point center, Point left, Point right)
{
	this->center = center;
	this->left = left;
	this->right = right;
	this->color.r = 0;
	this->color.g = 0;
	this->color.b = 0;
}

void SegEl::move(Point newCenter)
{
	this->left.x -= center.x - newCenter.x;
	this->left.y -= center.y - newCenter.y;
	this->center = newCenter;
}

void SegEl::turn(double angle)
{
	double x_new, y_new,x_new1, y_new1;
	x_new = this->center.x + (this->left.x - this->center.x)*cos(angle) - (this->left.y - this->center.y)*sin(angle);
	y_new = this->center.y + (this->left.x - this->center.x)*sin(angle) + (this->left.y - this->center.y)*cos(angle);
	x_new1 = this->center.x + (this->right.x - this->center.x)*cos(angle) - (this->right.y - this->center.y)*sin(angle);
	y_new1 = this->center.y + (this->right.x - this->center.x)*sin(angle) + (this->right.y - this->center.y)*cos(angle);
	this->left.x = x_new;
	this->left.y = y_new;
	this->right.x = x_new1;
	this->right.y = y_new1;
}

void SegEl::changesize(double k)
{
	double x_new, y_new;
	x_new = this->center.x + abs(this->left.x - this->center.x)*k;
	y_new = this->center.y + abs(this->left.y - this->center.y)*k;
	this->left.x = x_new;
	this->left.y = y_new;
}

double const SegEl::leftx() const
{
	double l;
	l = this->right.x - this->left.x;
	return l;
}