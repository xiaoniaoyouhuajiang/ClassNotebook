#include "figure.h"


size_t figure::count = 0;

figure::figure(const Color &color) : m_id(count++), alpha(0), m_color(color), num(1) {}
figure::figure() : figure(Color()) {}

void figure::setAngle(double a)
{
    alpha = a;
}
double figure::getAngle()
{
    return alpha;
}

void figure::setColor(const Color color)
{
	m_color = color;
}

Color figure::getColor() const
{
	return m_color;
}


size_t figure::getId() const
{
	return m_id;
}


std::ostream &operator<< (std::ostream &os, figure &f)
{
	f.print(os);
	return os;
}

