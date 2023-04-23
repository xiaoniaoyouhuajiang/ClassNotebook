#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "shape.h"

class Circle : public Shape 
{ 
public:
double radius,lenght; 

Circle(double r) : Shape()
{ 
radius = r;
lenght=2*3.14*r;
} 
void moveWithCoordinates(double x,double y) override 
{ 
_x = x; 
_y = y; 
} 
void rotateWithAngle(double a) override 
{ 
_angle += a; 
} 
void changeScale(double k) override 
{ 
_scale = k; 
radius *= _scale; 
} 
void setColor(double r, double g, double b) override 
{ 
if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255)) 
{ 
_array_rgb[0] = r; 
_array_rgb[1] = g; 
_array_rgb[2] = b; 
} 
else { 
std::cout << "Error.Max.value for R,G or B is 255." << std::endl; 
std::cout << "Error.Min.value for R,G or B is 0." << std::endl; 
} 
} 

friend std::ostream& operator<<(std::ostream& os,const Circle& rp)
{
os << "Info for shape:Circle." << std::endl; 
os << "Coordinates:" << rp._x << "," << rp._y << std::endl; 
os << "Scale:" << rp._scale << std::endl; 
os << "Radius:" << rp.radius << std::endl;
os << "Length:" << rp.lenght << std::endl; 
os << "Angle:" << rp._angle << std::endl; 
os << "Color(RGB):" << rp._array_rgb[0] << "," << rp._array_rgb[1] << "," << rp._array_rgb[0] << std::endl; 
os << std::endl; 
return os;
}
 
}; 
#endif
