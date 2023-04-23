#include "Shape.hpp"

std::ostream & operator<<(std::ostream & out, const Point& point)
{
	out << "(" << point.m_x << ","
		<< point.m_y << ")";

	return out;
}

std::ostream & operator<<(std::ostream & out, const std::vector<Point>& points)
{
	for (const auto& point : points)
	{
		out << point << ", ";
	}

	return out;
}

bool operator==(const Point& lhs, const Point& rhs)
{
	return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y;
}

std::ostream & operator<<(std::ostream & out, const what & type)
{
	switch (type)
	{
	case CIRCLE:
		out << "Circle";
		break;
	case SQUARE:
		out << "Square";
		break;
	case TRIANGLE:
		out << "Triangle";
		break;
	default:
		break;
	}

	return out;
}

std::ostream & operator<<(std::ostream & out, const rot_angle & angle)
{
	switch (angle)
	{
	case NIL:
		out << "0 gradus";
		break;
	case RIGHT90:
		out << "90 gradus on right";
		break;
	case RIGHT180:
	case LEFT180:
		out << "180 gradus on right or left";
		break;
	case LEFT90:
		out << "90 gradus on left";
		break;
	default:
		break;
	}
	return out;
}

Shape::Shape(std::string color, double size)
	: m_color(color)
	, m_size(size)
{
}

std::string Shape::get_color() const
{
	return m_color;
}

void Shape::set_color(std::string color)
{
	m_color = color;
}