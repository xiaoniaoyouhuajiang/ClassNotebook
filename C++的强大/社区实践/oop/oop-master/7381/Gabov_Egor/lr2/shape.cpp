#include "shape.h"

unsigned Shape::id = 0;
std::string Shape::defaultColor = "white";

std::ostream& operator<<(std::ostream& out, const Point& point){
    out << "X: " << point.x << " Y: " << point.y;
    return out;
}
std::ostream& operator<<(std::ostream& out, const Parallelogram& par){
    out << "PARALLELOGRAM" << std::endl;
    out << "CENTRE: " << par.centre << std::endl <<
           "D1: " << par.D1 << std::endl <<
           "D2: " << par.D2 << std::endl <<
           "COLOR: " << par.color << std::endl <<
           "ANGLE: " << par.angle << std::endl <<
           "PAR ANGLE: " << par.parAngle << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream& out, const Ellipse& el){
    out << "ELLIPSE" << std::endl;
    out << "CENTRE: " << el.centre << std::endl <<
           "D1: " << el.D1 << std::endl <<
           "D2: " << el.D2 << std::endl <<
           "COLOR: " << el.color << std::endl <<
           "ANGLE: " << el.angle << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream& out, const EllipseSector& elS){
    out << "ELLIPSESECTOR" << std::endl;
    out << "CENTRE: " << elS.centre << std::endl <<
           "D1: " << elS.D1 << std::endl <<
           "D2: " << elS.D2 << std::endl <<
           "COLOR: " << elS.color << std::endl <<
           "ANGLE: " << elS.angle << std::endl <<
           "SECTOR ANGLE: " << elS.sectorAngle << std::endl;
    return out;
}

double Parallelogram::calculatePerimeter(){
    return 2 * sqrt(pow(D1, 2) + pow(D2, 2) - 2 * D1 * D2 * std::cos(parAngle * PI / 180)) +
           2 * sqrt(pow(D1, 2) + pow(D2, 2) - 2 * D1 * D2 * std::cos((180 - parAngle) * PI / 180));
}

double Parallelogram::calculateArea(){
    return 0.5 * D1 * D2 * std::sin(parAngle * PI / 180);
}

double Ellipse::calculatePerimeter(){
    return 4 * ((PI * D1 * D2 + (D1 - D2)) / (D1 + D2));
}

double Ellipse::calculateArea(){
    return D1 * D2 * PI;
}

double EllipseSector::calculateArea(){
    return Ellipse::calculateArea() * sectorAngle / 180;
}

double EllipseSector::calculatePerimeter(){
    return Ellipse::calculatePerimeter() * sectorAngle / 180;
}
