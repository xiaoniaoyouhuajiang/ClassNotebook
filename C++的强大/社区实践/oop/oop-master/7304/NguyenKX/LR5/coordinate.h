#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
#include <sstream>

class Coordinate {
public:
    double x;
    double y;
    Coordinate(): x(0), y(0){}
    Coordinate(double x, double y) : x(x), y(y){}

    static Coordinate fromString(std::string s){
        std::stringstream ss(s);
        Coordinate c;
        ss>>c;
        return c;
    }
    friend std::ostream& operator<<(std::ostream &os, Coordinate &obj);
    friend std::istream& operator>>(std::istream &is, Coordinate &obj);

};

std::ostream& operator<<(std::ostream &os, Coordinate &obj);
std::istream& operator>>(std::istream &is, Coordinate &obj);
#endif // COORDINATE_H
