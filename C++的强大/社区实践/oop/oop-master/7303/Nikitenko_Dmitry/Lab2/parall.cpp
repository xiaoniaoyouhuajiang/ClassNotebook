#include "parall.h"

Parall::Parall() :
    Shape (), _sideAngle(45),
    _length(1), _sideLength(1)
{

    updateCoords();
}


Parall::Parall(double length,
               double sideLength, double sideAngle, double x,double y,
               Color& color, double angle) :
    Shape(x,y,color,angle)
{
    _sideAngle = sideAngle;
    _length = length;
    _sideLength = sideLength;
    _height = sideLength*sin(sideAngle*M_PI/180);
    updateCoords();
}

