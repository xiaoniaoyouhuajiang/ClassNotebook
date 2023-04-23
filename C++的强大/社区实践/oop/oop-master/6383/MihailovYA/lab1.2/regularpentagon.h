#ifndef REGULARPENTAGON_H_INCLUDED
#define REGULARPENTAGON_H_INCLUDED

#include "circle.h"

class RegularPentagon : public Circle
{ 
private: 
//int point1
double side[5];

public: 
RegularPentagon(double r) : Circle(r)
{ 
radius=r;
for(int i=0;i<5;i++)
side[i]=1.17557*radius;

} 
void moveWithCoordinates(double x, double y) override 
{ 
_x = x; 
_y = y; 
}
void rotateWithAngle(double a) override 
{ 
_angle = a; 
/*int angleRad=(_angle*3.1415926535897)/180;
int _x1e=_x1;
_x1=_x1*cos(angleRad)-_y1*sin(angleRad);
_y1=_x1e*sin(angleRad)+_y1*cos(angleRad);
int _x2e=_x2;
_x2=_x2*cos(angleRad)-_y2*sin(angleRad);
_y2=_x2e*sin(angleRad)+_y2*cos(angleRad);
int _x3e=_x3;
_x3=_x3*cos(angleRad)-_y3*sin(angleRad);
_y3=_x3e*sin(angleRad)+_y3*cos(angleRad);
int _x4e=_x4;
_x4=_x4*cos(angleRad)-_y4*sin(angleRad);
_y4=_x4e*sin(angleRad)+_y4*cos(angleRad);
int _x5e=_x5;
_x5=_x5*cos(angleRad)-_y5*sin(angleRad);
_y5=_x5e*sin(angleRad)+_y5*cos(angleRad);*/
} 
void changeScale(double k) override 
{ 
_scale = k; 
for(int i=0;i<5;i++)
side[i]*=_scale;

radius*= _scale; 
 
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

friend std::ostream& operator<<(std::ostream& os,const RegularPentagon& rp)
{
os << "Info for shape:Regular Pentagon." << std::endl; 
os << "Coordinates:" << rp._x << "," << rp._y << std::endl; 
os << "Scale:" << rp._scale << std::endl; 
os << "Described circle radius:" << rp.radius<< std::endl; 
os << "Angle:" << rp._angle << std::endl; 
os << "Side of regular pentagon:" << rp.side[0]<< std::endl; 
os << "Color(RGB):" << rp._array_rgb[0] << "," << rp._array_rgb[1] << "," << rp._array_rgb[2] << std::endl; 
os << std::endl; 
return os;
}
 
};
#endif 
