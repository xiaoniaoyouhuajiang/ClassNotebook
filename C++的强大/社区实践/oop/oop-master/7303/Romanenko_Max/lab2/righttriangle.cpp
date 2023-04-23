#include "righttriangle.h"


    rightTriangle::rightTriangle(const Point& p, double kat1, double kat2)
        :Shape(p)
    {
        sides.push_back(kat1);
        sides.push_back(kat2);
        sides.push_back(sqrt(kat1*kat1 + kat2*kat2));
        points.push_back(p);
        points.push_back(Point(p.x+kat1,p.y));
        points.push_back(Point(p.x,p.y+kat2));
    }

    std::ostream& operator<< (std::ostream& out, const rightTriangle& rTr) {

        out << "----right triangle----" << std::endl << "Sides: ";
        out << rTr.sides.at(0) << "x" << rTr.sides.at(1) << "x" << rTr.sides.at(2) << std::endl;
        out << (Shape&)rTr;
        return out;
    }
