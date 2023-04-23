#include "isoscelestriangle.h"


    isoscelesTriangle::isoscelesTriangle(const Point& p1, const Point& p2, const Point& p3)
        :Shape(Point((p1.x+p2.x+p3.x)/3, (p1.y+p2.y+p3.y)/3))
    {
        points.push_back(p1);
        points.push_back(p2);
        points.push_back(p3);
        sides.push_back(sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y)));
        sides.push_back(sqrt((p2.x - p3.x)*(p2.x - p3.x) + (p2.y - p3.y)*(p2.y - p3.y)));
        sides.push_back(sqrt((p3.x - p1.x)*(p3.x - p1.x) + (p3.y - p1.y)*(p3.y - p1.y)));
        double a = sides.at(0);
        double b = sides.at(1);
        double c = sides.at(2);
        if ((a+b)<=c || (a+c)<=b || (c+b)<= a){
            throw std::logic_error("Not a triangle");
        }
        if (!((a==b)||(a==c)||(b==c)))
            throw std::logic_error("Not a isosceles triangle");


    }
    std::ostream& operator<< (std::ostream& out, const isoscelesTriangle& iTr) {

        out << "----Isosceles triangle----" << std::endl << "Sides: ";

        out << iTr.sides.at(0) << "x" << iTr.sides.at(1) << "x" << iTr.sides.at(2) << std::endl;
        out << (Shape&)iTr;
        return out;
    }

