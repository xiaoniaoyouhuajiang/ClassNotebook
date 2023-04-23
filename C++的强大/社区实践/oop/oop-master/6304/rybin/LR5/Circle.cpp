#include "Shape.hpp"

Circle::Circle(std::string color, double radius, Point center)
	: Shape(color, radius)
	, m_center(center)
{
}

what Circle::id() const
{
	return what(CIRCLE);
}

void Circle::move(Point to_move)
{
	if (m_center == to_move)
	{
		return;
	}
	else
	{
		m_center = to_move;
	}
}

void Circle::rotate(rot_angle angle)
{
	;
}

void Circle::zoom(double coef)
{
	if (coef > 0)
	{
		m_size *= coef;
	}
	else
	{
		return;
	}
}

std::ostream & Circle::operator<<(std::ostream & out) const
{
	out << "type: " << id() << "\n"
		<< "color: " << m_color << "\n"
		<< "center: " << m_center << "\n"
		<< "radius: " << m_size << "\n\n";

	return out;
}

double Circle::area() const
{
	return 3.14 * m_size * m_size;
	
}