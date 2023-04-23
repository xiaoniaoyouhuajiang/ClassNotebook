#include "ellipse.h"
double Ellipse::getPerimetr() const
{
    return 4 * ( M_PI * aHalfAxis * bHalfAxis + ( bHalfAxis - aHalfAxis ) ) / ( aHalfAxis + bHalfAxis );
}
double Ellipse::getArea()
{
    return M_PI * aHalfAxis * bHalfAxis;
}

int Ellipse::intersect(Shape &s2) const
{
    int intersectCount = 0;
    double x, y;
    bool inside = false;

    // проверка на совпадающую фигуру
    Ellipse* e = dynamic_cast<Ellipse*>(&s2);
    if (e)
    {
        if (match(*e))
            // фигуры совпадают
            return -1;
    }

    for(double t = -M_PI; t < M_PI; t+=epsStep)
    {
        x = aHalfAxis * cos(t) + center_coordinates.x;
        y = bHalfAxis * sin(t) + center_coordinates.y;

        Point p(x, y);

        if(s2.isPointOnBorder(p))
        {
            if (!inside)
            {
                inside = true;
                intersectCount++;
            }
        }
        else
        {
            if (inside)
                inside = false;
        }
    }

    // если начальная точка является точкой пересечения, мы посчитали ее два раза
    x = aHalfAxis * cos(-M_PI) + center_coordinates.x;
    y = bHalfAxis * sin(-M_PI) + center_coordinates.y;
    if (s2.isPointOnBorder(Point(x, y)))
        intersectCount--;


    return intersectCount;
}
void Ellipse::scale(double scale)
{
    aHalfAxis *= scale;
    bHalfAxis *= scale;
}
void Ellipse::print(std::ostream &os)
{
    os<<"Ellipse"<<std::endl;
    os<<"Id: "<<id<<std::endl;
    os<<"Center( x , y ): ( "<<center_coordinates.x<<" , "<<center_coordinates.y<<" )"<<std::endl;
    os<<"Maximum Half Axis: "<<bHalfAxis<<std::endl;
    os<<"Minimum Half Axis: "<<aHalfAxis<<std::endl;
    os<<"Perimetr: "<<getPerimetr()<<std::endl;
    os<<"Area: "<<getArea()<<std::endl;
}

bool Ellipse::isPointOnBorder(const Point &p) const
{
    Point r = p;
    r.rotate(current_angle);
    double dx = (r.x - center_coordinates.x) / aHalfAxis;
    double dy = (r.y - center_coordinates.y) / bHalfAxis;
    bool borderFlag = fabs(pow(dx, 2) + pow(dy, 2) - 1) < 1.5*eps;
    return borderFlag;
}

bool Ellipse::match(const Ellipse &e) const
{
    bool bCenter = (center_coordinates == e.center_coordinates);
    bool a_ = AreSame(aHalfAxis, e.aHalfAxis);
    bool b_ = AreSame(bHalfAxis, e.bHalfAxis);

    return (bCenter && a_ && b_);
}
