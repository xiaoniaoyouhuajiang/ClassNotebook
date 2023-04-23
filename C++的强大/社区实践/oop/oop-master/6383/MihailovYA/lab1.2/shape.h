#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

class Shape 
{ 
public: 
virtual void moveWithCoordinates(double x,double y) = 0; 
virtual void rotateWithAngle(double a) = 0; 
virtual void changeScale(double k) = 0; 
virtual void setColor(double r,double g,double b) = 0; 
 
Shape(){
_x=0;
_y=0;
_angle = 0; 
_scale = 1; 
_array_rgb[0] = 0;//default black 
_array_rgb[1] = 0; 
_array_rgb[2] = 0; 
}
protected:
double _x,_y;
double _angle,_scale; 
double _array_rgb[3]; 
}; 
#endif
