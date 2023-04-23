#include "shape.h"

size_t Shape::count = 0;

Shape::Shape()
{
    m_id = count++;
}


void Shape::setColor(const Color color)
{
    m_color = color;
}


Color Shape::getColor() const
{
    return m_color;
}


size_t Shape::getId() const
{
    return m_id;
}

std::ostream& operator<< (std::ostream& os, const Shape& p)
{
    p.print(os);
    return os;
}
