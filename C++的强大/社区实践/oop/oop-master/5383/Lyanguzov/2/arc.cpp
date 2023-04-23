#include "arc.h"
void Arc::scale(double scale)
{
    radius *= scale;
}
double Arc::getArea()
{
    return 0;
}
double Arc::getPerimetr() const
{
    double n = fabs(startAngle - finishAngle);
    double l = (M_PI * radius / 180) * n;
    return l;
}
void Arc::print(std::ostream &os)
{
    os<<"Arc:"<<std::endl;
    os<<"Id: "<<id<<std::endl;
    os<<"Center( x , y ): ( "<<center_coordinates.x<<" , "<<center_coordinates.y<<" )"<<std::endl;
    os<<"Start Angle: "<<startAngle<<std::endl;
    os<<"Finish Angle: "<<finishAngle<<std::endl;
    os<<"Radius: "<<radius<<std::endl;
}

bool Arc::isPointOnBorder(const Point &p) const
{
    // x = cos(t) y = sin(t)
    Point r = p;
    r.rotate(-current_angle);
    double dx = r.x - center_coordinates.x;
    double dy = r.y - center_coordinates.y;
    bool borderFlag = fabs(pow(dx, 2) + pow(dy, 2) - pow(radius, 2)) < eps;
    double pointAngle = atan2(dy, dx);
    bool startAngleFlag = pointAngle >= startAngle;
    bool finishAngleFlag = pointAngle <= finishAngle;
    return (borderFlag && startAngleFlag && finishAngleFlag);
}

bool Arc::match(const Arc &other) const
{
    bool bCenter = (center_coordinates == other.center_coordinates);
    bool bRadius = AreSame(radius, other.radius);

    double s1 = fmod(startAngle + current_angle, 2*M_PI);
    double f1 = fmod(finishAngle + current_angle, 2*M_PI);
    double s2 = fmod(other.startAngle + other.current_angle, 2*M_PI);
    double f2 = fmod(other.finishAngle + other.current_angle, 2*M_PI);

    bool bAngle = !((s2 > f1) || (f2 < s1));

    return (bCenter && bRadius && bAngle);
}

int Arc::intersect(Shape &s2) const
{
    int intersectCount = 0;
    double x, y;
    bool inside = false;

    // проверка на совпадающую фигуру
    Arc* arc = dynamic_cast<Arc*>(&s2);
    if (arc)
    {
        if (match(*arc))
            // фигуры совпадают
            return -1;
    }

    // проверка на 0 радиус
    if (AreSame(radius, 0))
        return (s2.isPointOnBorder(center_coordinates) ? 1 : 0);

    // идем по фигуре с шагом epsStep и считаем, сколько точек попало в область s2
    for(double t = startAngle; t < finishAngle; t+=epsStep)
    {
        x = radius * cos(t) + center_coordinates.x;
        y = radius * sin(t) + center_coordinates.y;

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

    // если начальная и конечная точки совпадают, уменьшаем число точек, поскольку мы дважды посчитали одну и ту же точку
    double xstart = radius * cos(startAngle) + center_coordinates.x;
    double ystart = radius * sin(startAngle) + center_coordinates.y;
    double xfinish = radius * cos(finishAngle) + center_coordinates.x;
    double yfinish = radius * sin(finishAngle) + center_coordinates.y;

    if (AreSame(xstart, xfinish) && AreSame(ystart, yfinish) && s2.isPointOnBorder(Point(xstart, ystart)))
        intersectCount--;

    return intersectCount;
}
