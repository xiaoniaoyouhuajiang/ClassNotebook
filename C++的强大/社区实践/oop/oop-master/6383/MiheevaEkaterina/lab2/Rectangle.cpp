//
// Created by katier on 12.03.18.
//

#include "Rectangle.h"

Rectangle::Rectangle(Colour colour,Point p1, Point p2, Point p3, Point p4):Shape(colour),p1(p1),p2(p2),p3(p3),p4(p4){
    if(!isRectangle())throw "NOT RECTANGLE!!!";
}
Rectangle::Rectangle(Colour colour, double k1, double k2):
Rectangle(colour,Point(0.5*k1,0.5*k2),Point(0.5*k1,-0.5*k2),Point(-0.5*k1,-0.5*k2),Point(-0.5*k1,0.5*k2)){}

bool Rectangle:: isRectangle(){
    double s1 = (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
    double s2 = (p1.x - p3.x)*(p1.x - p3.x) + (p1.y - p3.y)*(p1.y - p3.y);
    double s3 = (p1.x - p4.x)*(p1.x - p4.x) + (p1.y - p4.y)*(p1.y - p4.y);
    double s4 = (p2.x - p3.x)*(p2.x - p3.x) + (p2.y - p3.y)*(p2.y - p3.y);
    double s5 = (p2.x - p4.x)*(p2.x - p4.x) + (p2.y - p4.y)*(p2.y - p4.y);
    double s6 = (p3.x - p4.x)*(p3.x - p4.x) + (p3.y - p4.y)*(p3.y - p4.y);
    if ((s1 == s6) && (s3 == s4) && (s2 == s5)) return  true;
    if ((s1 == s6) && (s2 == s5) && (s3 == s4)) return  true;
    return (s2 == s5) && (s3 == s4) && (s1 == s6);
}
void Rectangle::print  (std::ostream& os)  {
    os<<"\nRectangle\nid = "<<getId()<<"\nPoints:\np1 = "<<p1<<"p2 = "<<p2
      <<"p3 = "<<p3<<"p4= "<<p4<<"Colour:\nblue = "<<getColour().blue
      <<"\ngreen = "<<getColour().green<<"\nred = "<<getColour().red<<std::endl;
}

void Rectangle::scale(double k) {
    p1.x*=k;
    p1.y*=k;
    p2.x*=k;
    p2.y*=k;
    p3.x*=k;
    p3.y*=k;
    p4.x*=k;
    p4.y*=k;
}
void Rectangle::move(Point newCoord) {
    p1.x+=newCoord.x;
    p1.y+=newCoord.y;
    p2.x+=newCoord.x;
    p2.y+=newCoord.y;
    p3.x+=newCoord.x;
    p3.y+=newCoord.y;
    p4.x+=newCoord.x;
    p4.y+=newCoord.y;
}
void Rectangle::rotate (double angle)  {
    p1.x = p1.x*cos(angle) - p1.y*sin(angle);
    p1.y = p1.x*sin(angle) + p1.y*cos(angle);
    p2.x = p1.x*cos(angle) - p1.y*sin(angle);
    p2.y = p1.x*sin(angle) + p1.y*cos(angle);
    p3.x = p1.x*cos(angle) - p1.y*sin(angle);
    p3.y = p1.x*sin(angle) + p1.y*cos(angle);
    p4.x = p1.x*cos(angle) - p1.y*sin(angle);
    p4.y = p1.x*sin(angle) + p1.y*cos(angle);
}