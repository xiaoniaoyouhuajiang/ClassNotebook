#include "round.h"
double Round::getArea()
{
    double s = M_PI * pow(radius, 2);
    return s;
}
double Round::getPerimetr() const
{
    double l = 2 * M_PI * radius;
    return l;
}
void Round::print(std::ostream &os)
{
    os<<"Round"<<std::endl;
    os<<"Id: "<<id<<std::endl;
    os<<"Center( x , y ): ( "<<center_coordinates.x<<" , "<<center_coordinates.y<<" )"<<std::endl;
    os<<"Radius: "<<radius<<std::endl;
    os<<"Perimetr: "<<getPerimetr()<<std::endl;
    os<<"Area: "<<getArea()<<std::endl;
}

bool Round::isPointOnBorder(const Point &p) const
{
    Point r = p;
    r.rotate(-current_angle);
    double dx = (r.x - center_coordinates.x);
    double dy = (r.y - center_coordinates.y);
    bool borderFlag = fabs(pow(dx, 2) + pow(dy, 2) - pow(radius, 2)) < eps;
    return borderFlag;
}
