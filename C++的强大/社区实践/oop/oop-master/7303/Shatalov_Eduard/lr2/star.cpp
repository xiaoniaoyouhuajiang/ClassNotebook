#include "shape.h"
#include "star.h"
void Star::scale(double coefficient){
    s_radius *=coefficient;
    s_radius2 *=coefficient;
}


void Star::rotate(double angle){
   rotation_angle += angle;
   dot1x =this->s_x + cos(rotation_angle/180*M_PI)*s_radius;
   dot1y =this->s_y - sin(rotation_angle/180*M_PI)*s_radius;
}

