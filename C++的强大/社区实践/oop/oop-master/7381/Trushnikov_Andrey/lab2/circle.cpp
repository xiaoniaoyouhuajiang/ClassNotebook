#include "circle.h"

Circle::Circle(std::vector <Point> center,double radius, Colour colour):radius(radius){
    this->setColour(colour);
    this->setPoints(center);
}

double Circle::perimetr(){
    return 2*3.14*radius;
}

double Circle::area(){
    return 3.14*pow(radius,2);
}

void Circle::scale(double k){
    radius = radius*k;
}

void Circle::print(std::ostream& out){
    out << "Circle #" << id << ' ';
    out << colour;
    out << "P = " << perimetr() << " S = " << area();
    out << " center" << coord[0] << ' ';
    out << "radius = " << radius << std::endl;
}
