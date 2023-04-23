#ifndef PENTAGON_H_INCLUDED
#define PENTAGON_H_INCLUDED

#include "shape.h"

class Pentagon : public Shape 
{ 
private: 
//double radiusDescribed,radiusInscribed,side; 
double _x1,_x2,_x3,_x4,_x5;
double _y1,_y2,_y3,_y4,_y5;
double sides[5];

public: 

Pentagon(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4,double x5,double y5) : _x1(x1), _y1(y1),_x2(x2), _y2(y2),_x3(x3), _y3(y3),_x4(x4), _y4(y4),_x5(x5), _y5(y5) 
{ 
//side = 1.17557*R; //(x-x1)/(x2-x1)=(y-y1)/(y2-y1)
//radiusInscribed = 0.688191*side;
int f = (_x3-_x1)/(_x2-_x1)-(_y3-_y1)/(_y2-_y1);
if(f==0) std::cout << "Three points on one line!!!"<<std::endl; 
f = (_x4-_x2)/(_x3-_x2)-(_y4-_y2)/(_y3-_y2);
if(f==0) std::cout << "Three points on one line!!!"<<std::endl;
f = (_x5-_x3)/(_x4-_x3)-(_y5-_y3)/(_y4-_y3);
if(f==0) std::cout << "Three points on one line!!!"<<std::endl;
f = (_x1-_x4)/(_x5-_x4)-(_y1-_y4)/(_y5-_y4);
if(f==0) std::cout << "Three points on one line!!!"<<std::endl;

sides[0]=sqrt((_x2-_x1)*(_x2-_x1)+(_y2-_y1)*(_y2-_y1));
sides[1]=sqrt((_x3-_x2)*(_x3-_x2)+(_y3-_y2)*(_y3-_y2));
sides[2]=sqrt((_x4-_x3)*(_x4-_x3)+(_y4-_y3)*(_y4-_y3));
sides[3]=sqrt((_x5-_x4)*(_x5-_x4)+(_y5-_y4)*(_y5-_y4));
sides[4]=sqrt((_x1-_x5)*(_x1-_x5)+(_y1-_y5)*(_y1-_y5));

} 
void moveWithCoordinates(double x, double y) override 
{ 
_x = x; 
_y = y; 
} 
void rotateWithAngle(double a) override 
{ 
_angle = a; 
int angleRad=(_angle*3.1415926535897)/180;
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
_y5=_x5e*sin(angleRad)+_y5*cos(angleRad);
} 
void changeScale(double k) override 
{ 
_scale = k; 
for(int i=0;i<5;i++)
sides[i]*=_scale;
//radiusDescribed *= _scale; 
//radiusInscribed *= _scale; 
//side *= _scale; 
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

friend std::ostream& operator<<(std::ostream& os,const Pentagon& rp)
{
os << "Info for shape:Pentagon." << std::endl; 
os << "Coordinates:" << rp._x << "," << rp._y << std::endl; 
os << "Scale:" << rp._scale << std::endl; 
//std::cout << "Described circle radius:" << radiusDescribed << std::endl; 
os << "Angle:" << rp._angle << std::endl; 
os << "Points:" <<"(" <<rp._x1<<","<<rp._y1 <<")" << std::endl;
os <<"(" <<rp._x2<<","<<rp._y2 <<")" << std::endl;
os <<"(" <<rp._x3<<","<<rp._y3 <<")" << std::endl;
os <<"(" <<rp._x4<<","<<rp._y4 <<")" << std::endl;
os <<"(" <<rp._x5<<","<<rp._y5 <<")" << std::endl; 
os << "Sides of pentagon:" << rp.sides[0]<<","<< rp.sides[1]<<","<< rp.sides[2]<<","<< rp.sides[3]<<","<< rp.sides[4]<<"." << std::endl; 
os << "Color(RGB):" << rp._array_rgb[0] << "," << rp._array_rgb[1]
<< "," << rp._array_rgb[2] << std::endl; 
os << std::endl;  
return os;
}
  
};
#endif 
