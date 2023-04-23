#include "pch.h"
#include <math.h>
#include "ellipse.h"

void Ellipse::set_crd()
{
	crd.clear();
	crd.push_back({ centre.x - a / 2, centre.y });
	crd.push_back({ centre.x, centre.y + b / 2 });
	crd.push_back({ centre.x + a / 2, centre.y });
	crd.push_back({ centre.x, centre.y - b / 2 });
	rotate(angle);
}

Ellipse::Ellipse(double _a, double _b, Point cntr, double angl) : Shape(cntr)
{
	a = _a;
	b = _b;
	angle = angl;
	set_crd();
}

void Ellipse::move(Point new_cntr)
{
	centre.x = new_cntr.x;
	centre.y = new_cntr.y;
	set_crd();
}

void Ellipse::rotate(double angl)
{
	angle = angl;

	double _x, _y;
	for (unsigned i = 0; i < crd.size(); ++i)
	{
		_x = crd[i].x;
		_y = crd[i].y;
		crd[i].x = (_x - centre.x) * cos(angle) - (_y - centre.y) * sin(angle) + centre.x;
		crd[i].y = (_x - centre.x) * sin(angle) + (_y - centre.y) * cos(angle) + centre.y;
	}

}

void Ellipse::scale(double k)
{
	a *= k;
	b *= k;
	set_crd();
}

void Ellipse::print(std::ostream& out)
{
	out << "Stape type: ellipse\n";
	out << "a: " << a << std::endl;
	out << "b: " << b << std::endl;
}

Ellipse::~Ellipse()
{
	a = 0;
	b = 0;
}
