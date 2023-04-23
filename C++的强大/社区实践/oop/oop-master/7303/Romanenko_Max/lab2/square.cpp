#include "square.h"


    Square::Square(const Point& p, double side)
        :Shape(p)
    {
        points.push_back(Point(p.x-side/2,p.y+side/2));
        points.push_back(Point(p.x+side/2,p.y-side/2));
    }
    std::ostream& operator<< (std::ostream& out, const Square& square) {

        out << "----Square----" << std::endl << "Side: " << fabs(square.points.at(0).x - square.points.at(1).x) << std::endl;
        out << (Shape&)square;
        return out;
    }
