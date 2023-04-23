#include "Shape.h"

Parallelogramm::Parallelogramm(Point center, int _l, int _L)
{
	this->center = center;
	this->l= l;
	this->L = L;
	this->color.r = 0;
	this->color.g = 0;
	this->color.b = 0;
}

void Parallelogramm::move(Point newCenter)
{
	this->center = newCenter;
}

void Parallelogramm::turn(double angle)
{ 
	cout << "Введите угол поворота";
	cin >> angle;
	cout << "Вы повернули параллелограм на" << angle;
}

void Parallelogramm::changesize(double k)
{
	this->l = this->l*k;
	this->L = this->L*k;
}
double const Parallelogramm::leftx() const
{
	double leftx = fabs(this->L - this->l);
	return leftx;
}
