#include "Vector.h"

#include <cmath>

Vector::Vector(double x, double y)
  : x{x}, y{y}
{ }

Vector& Vector::operator+=(Vector const& other)
{
  x += other.x;
  y += other.y;
  return *this;
}

Vector& Vector::operator-=(Vector const& other)
{
  x -= other.x;
  y -= other.y;
  return *this;
}

Vector& Vector::operator*=(double other)
{
  x *= other;
  y *= other;
  return *this;
}

Vector& Vector::operator/=(double other)
{
  x /= other;
  y /= other;
  return *this;
}

Vector Vector::operator-() const
{
  Vector tmp{*this};
  tmp.x = -tmp.x;
  tmp.y = -tmp.y;
  return tmp;
}

bool Vector::operator==(Vector const& other) const
{
  return x == other.x && y == other.y;
}

bool Vector::operator!=(Vector const& other) const
{
  return !(*this == other);
}


double Vector::operator*(Vector const& rhs) const
{
  return x * rhs.x + y * rhs.y;
}


double Vector::length() const
{
  return std::sqrt(x * x + y * y);
}

Vector operator+(Vector const& lhs, Vector const& rhs)
{
  return Vector{lhs} += rhs;
}

Vector operator-(Vector const& lhs, Vector const& rhs)
{
  return Vector{lhs} -= rhs;
}

Vector operator*(Vector const& lhs, double rhs)
{
  return Vector{lhs} *= rhs;
}

Vector operator*(double lhs, Vector const& rhs)
{
  return rhs * lhs;
}

Vector operator/(Vector const& lhs, double rhs)
{
  return Vector{lhs} /= rhs;
}

std::ostream& operator<<(std::ostream& os, Vector const& other)
{
  return os << '(' << other.x << ", " << other.y << ')';
}

std::istream& operator>>(std::istream& is, Vector& other)
{
  Vector tmp;
  is >> std::ws;
  if (is.peek() == '(')
  {
    
    if (is.ignore(1) >> std::ws >> tmp.x >> std::ws)
    {
      if (is.peek() == ',')
      {
        if (is.ignore(1) >> std::ws >> tmp.y >> std::ws)
        {
          if (is.peek() == ')')
          {
            is.ignore(1);
            other = tmp;
            return is;
          }
        }
      }
    }
  }
  is.setstate(std::ios::failbit);
  return is;
}
