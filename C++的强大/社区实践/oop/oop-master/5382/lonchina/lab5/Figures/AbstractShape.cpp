#include "AbstractShape.h"

void AbstractShape::setColor(std::string color)
{
    this->color = color;
}

std::string AbstractShape::getColor()
{
    return this->color;
}

int AbstractShape::getArea() const {
    return area;
}

bool AbstractShape::operator==(const AbstractShape &rhs) const {
    return area == rhs.area;
}

bool AbstractShape::operator!=(const AbstractShape &rhs) const {
    return !(rhs == *this);
}

bool AbstractShape::operator<(const AbstractShape &rhs) const {
    return area < rhs.area;
}

bool AbstractShape::operator>(const AbstractShape &rhs) const {
    return rhs < *this;
}

bool AbstractShape::operator<=(const AbstractShape &rhs) const {
    return !(rhs < *this);
}

bool AbstractShape::operator>=(const AbstractShape &rhs) const {
    return !(*this < rhs);
}
