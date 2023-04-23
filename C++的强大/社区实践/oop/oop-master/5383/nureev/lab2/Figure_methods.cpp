#include "figure.h"
size_t Figure::count = 0;

double Figure::getAngle()

{

	return alpha;

}



Figure::Figure()

{
	m_id = count++;

	alpha = 0;


}

size_t Figure::getId() const
{
	return m_id;
}

void Figure::setAngle(double a)

{

	alpha = a;

}

std::ostream &operator<< (std::ostream &os, Figure &f)
{
	f.print(os);
	return os;
}

void Figure::setColor(const Color color)
{
	m_color = color;
}

Color Figure::getColor() const
{
	return m_color;
}