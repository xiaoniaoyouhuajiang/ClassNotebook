#include "RadiusVector.h"

RadiusVector::RadiusVector(double x, double y) :
  x_coord(x), y_coord(y)
{
}

RadiusVector::RadiusVector(const RadiusVector &other)
{
    x_coord = other.getX();
    y_coord = other.getY();
}

RadiusVector& RadiusVector::operator=(const RadiusVector& other)
{
    if (this != &other)
    {
        x_coord = other.getX();
        y_coord = other.getY();
    }
    return *this;
}

void RadiusVector::setX(double x)
{
    x_coord = x;
}

void RadiusVector::setY(double y)
{
    y_coord = y;
}

double RadiusVector::getX() const
{
    return x_coord;
}

double RadiusVector::getY() const
{
    return y_coord;
}

double RadiusVector::length() const
{
    return sqrt(x_coord*x_coord + y_coord*y_coord);
}

RadiusVector& RadiusVector::operator+=(const RadiusVector &other)
{
    x_coord += other.getX();
    y_coord += other.getY();
    return *this;
}

RadiusVector& RadiusVector::operator-=(const RadiusVector &other)
{
    x_coord -= other.getX();
    y_coord -= other.getY();
    return *this;
}

RadiusVector& RadiusVector::operator*=(double coeff)
{
    x_coord *= coeff;
    y_coord *= coeff;
    return *this;
}

//-----------------------------------------------
RadiusVector operator+(const RadiusVector &first, const RadiusVector &second)
{
    return RadiusVector(first.getX() + second.getX(), first.getY() + second.getY());
}

RadiusVector operator-(const RadiusVector &first, const RadiusVector &second)
{
    return RadiusVector(first.getX() - second.getX(), first.getY() - second.getY());
}

RadiusVector operator*(const RadiusVector &vector, double coeff)
{
    return RadiusVector(vector.getX() * coeff, vector.getY() * coeff);
}

RadiusVector operator*(double coeff, const RadiusVector &vector)
{
    return vector * coeff;
}

ostream& operator<<(ostream &os, const RadiusVector &vector)
{
    os << "(" << vector.x_coord << ", " << vector.y_coord << ")";
    return os;
}
