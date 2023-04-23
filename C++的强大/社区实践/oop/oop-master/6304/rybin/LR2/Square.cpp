#include "Shape.hpp"

Square::Square(std::string color, double size, Point bottom_left)
	: Shape(color, size)
{
	m_points.resize(4);
	move(bottom_left);
}

what Square::id() const
{
	return what(SQUARE);
}

void Square::move(Point to_move)
{
	m_points[0] = to_move;

	m_points[1].m_x = m_points[0].m_x;
	m_points[1].m_y = m_points[0].m_y + m_size;

	m_points[2].m_x = m_points[0].m_x + m_size;
	m_points[2].m_y = m_points[0].m_y + m_size;

	m_points[3].m_x = m_points[0].m_x + m_size;
	m_points[3].m_y = m_points[0].m_y;
}

void Square::rotate(rot_angle angle)
{
	switch (angle)
	{
	case RIGHT90:
		move({ m_points[0].m_x, m_points[0].m_y - m_size });
		break;
	case RIGHT180:
		move({ m_points[0].m_x - m_size, m_points[0].m_y - m_size });
		break;
	case LEFT90:
		move({ m_points[0].m_x - m_size, m_points[0].m_y });
		break;
	case LEFT180:
		move({ m_points[0].m_x - m_size, m_points[0].m_y - m_size });
		break;
	case NIL:
		break;
	default:
		break;
	}
}

void Square::zoom(double coef)
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

std::ostream & Square::operator<<(std::ostream & out) const
{
	out << "type: " << id() << "\n"
		<< "color: " << m_color << "\n"
		<< "points: " << m_points << "\n"
		<< "size:" << m_size << "\n\n";

	return out;
}