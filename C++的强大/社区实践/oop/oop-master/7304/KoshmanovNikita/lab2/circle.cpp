#include "pch.h"
#include "circle.h"


void Circle::set_crd()
{
	crd.clear();
	crd.push_back({ centre.x - radius, centre.y });
	crd.push_back({ centre.x, centre.y - radius });
	crd.push_back({ centre.x + radius, centre.y });
	crd.push_back({ centre.x, centre.y + radius });
}

Circle::Circle(double rd, Point cntr) : Shape(cntr)
{
	radius = rd;
	set_crd();
}

void Circle::move(Point new_cntr)
{
	centre.x = new_cntr.x;
	centre.y = new_cntr.y;
	set_crd();
}

void Circle::rotate(double)
{ /*...*/
}

void Circle::scale(double k)
{
	radius *= k;
	set_crd();
}

void Circle::print(std::ostream& out)
{
	out << "Stape type: circle\n";
	out << "Radius: " << radius << std::endl;
}

Circle::~Circle()
{
	radius = 0;
}
