//
// Created by katier on 12.03.18.
//

#include "Ellipse.h"
Ellipse::Ellipse (Colour colour,double angle, Point center,double a,double b):Shape(colour),angle(angle),center(center),a(a),b(b){};
void Ellipse:: scale(double k) {
    a*=k;
    b*=k;
}
void Ellipse:: move (Point toNewCenter) {
    center = toNewCenter;
}
void Ellipse::rotate(double angle)  {
    this->angle +=angle;
}
void Ellipse::roteteAroundZero(double angle){
    center.x = center.x*cos(angle) - center.y*sin(angle);
    center.y = center.x*sin(angle) + center.y*cos(angle);
    this->angle +=angle;
}
void Ellipse::print (std::ostream& os)  {
    os<<"\nEllipse\nid = "<<getId()<<"\na = "<<a<<"\nb = "<<b<<"\nangle = "<<angle<<"\nCenter:\n"<<center<<"Colour:\nblue = "
      <<getColour().blue<<"\ngreen = "<<getColour().green<<"\nred = " <<getColour().red<<std::endl;
}
