#ifndef MATH_H
#define MATH_H

#pragma once

#include <iostream>
#include <cmath>

#define PI 3.141592 // 180 grad

using namespace std;

typedef unsigned char u_char;
typedef unsigned long ul;

class RGB
{
public:
    RGB(u_char red, u_char green, u_char blue) {mColor[0] = red; mColor[1] = green; mColor[2] = blue;}

    friend std::ostream& operator <<(std::ostream& stream, const RGB& color) {
        stream << "[" << static_cast<int>(color.mColor[0]) << ", " << static_cast<int>(color.mColor[1]) << ", " << static_cast<int>(color.mColor[2]) << "]";
        return stream;
    }
    u_char mColor[3];
};

class Coord
{
public:
    Coord(double x, double y)
        : X(x)
        , Y(y) {}

    Coord& operator +=(const Coord& vec) { X += vec.X; Y+= vec.Y; return *this; }
    Coord& operator *=(double factor) { X *= factor; Y*= factor; return *this; }

    static double Lenght(const Coord& p1, const Coord& p2) { return sqrt((p1.X - p2.X)*(p1.X - p2.X) + (p1.Y - p2.Y)*(p1.Y - p2.Y)); }

    void Rotate(double angle, const Coord& p0)
    {
      double x = X;
      X = p0.X + (x - p0.X)*cos(angle) - (Y - p0.Y)*sin(angle);
      Y = p0.Y + (Y - p0.Y)*cos(angle) + (x - p0.X)*sin(angle);
    }

    double X;
    double Y;
};

#endif // MATH_H
