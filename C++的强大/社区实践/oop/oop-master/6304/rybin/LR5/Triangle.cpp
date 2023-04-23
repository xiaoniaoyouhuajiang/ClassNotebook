#include "Shape.hpp"
#include <cmath>

what Triangle::id() const
{
	return what(TRIANGLE);
}

Triangle::Triangle(std::string color, double size, Point bottom_left)
	: Shape(color, size)
	, m_angle(NIL)
{
	m_points.resize(3);
	move(bottom_left);
}

void Triangle::move(Point to_move)
{

	switch (m_angle)
	{
	case NIL:
		m_points[0] = to_move;

		m_points[1].m_x = m_points[0].m_x + m_size * 1.0 / 2.0;
		m_points[1].m_y = m_points[0].m_y + m_size * sqrt(3.0) / 2.0;

		m_points[2].m_x = m_points[0].m_x + m_size;
		m_points[2].m_y = m_points[0].m_y;

		break;
	case RIGHT90:
		m_points[0] = to_move;

		m_points[1].m_x = m_points[0].m_x;
		m_points[1].m_y = m_points[0].m_y + m_size;

		m_points[2].m_x = m_points[0].m_x + m_size * sqrt(3.0) / 2.0;
		m_points[2].m_y = m_points[0].m_y + m_size / 2.0;

		break;
	case RIGHT180:
	case LEFT180:
		m_points[0] = to_move;

		m_points[1].m_x = m_points[0].m_x - m_size / 2.0;
		m_points[1].m_y = m_points[0].m_y + m_size * sqrt(3.0) / 2.0;

		m_points[2].m_x = m_points[0].m_x + m_size / 2.0;
		m_points[2].m_y = m_points[0].m_y + m_size * sqrt(3.0) / 2.0;

		break;
	case LEFT90:
		m_points[0] = to_move;

		m_points[1].m_x = m_points[0].m_x - m_size * sqrt(3.0) / 2.0;
		m_points[1].m_y = m_points[0].m_y + m_size / 2.0;

		m_points[2].m_x = m_points[0].m_x;
		m_points[2].m_y = m_points[0].m_y + m_size;

		break;
	default:
		break;
	}
}

void Triangle::zoom(double coef)
{
	if (coef > 0)
	{
		m_size *= coef;
		move(m_points[0]);
	}
	else
	{
		return;
	}
}

void Triangle::rotate(rot_angle angle)
{
	m_angle = angle;

	switch (m_angle)
	{
	case NIL:
		break;
	case RIGHT90:
		move({ m_points[0].m_x, m_points[0].m_y - m_size });
		break;
	case RIGHT180:
	case LEFT180:
		move({ m_points[0].m_x - m_size / 2.0, m_points[0].m_y - m_size });
		break;
	case LEFT90:
		move(m_points[0]);
	default:
		break;
	}
}

std::ostream & Triangle::operator<<(std::ostream & out) const
{
	out << "type: " << id() << "\n"
		<< "color: " << m_color << "\n"
		<< "angle: " << m_angle << "\n"
		<< "points: " << m_points << "\n"
		<< "size:" << m_size << "\n\n";

	return out;
}

double Triangle::area() const
{
	return m_size * m_size * sqrt(3) / 4.0;
}