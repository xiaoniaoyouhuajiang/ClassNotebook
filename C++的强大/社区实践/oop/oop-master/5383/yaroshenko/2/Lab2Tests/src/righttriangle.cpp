#include "righttriangle.h"

RightTriangle::RightTriangle(const Point2d &vertex, double leftSide, double downSide, double angle) :

    Triangle(vertex,
             Point2d(vertex.x + leftSide, vertex.y),
             Point2d(vertex.x, vertex.y + downSide) )
{
    rotate(angle);
}

RightTriangle::RightTriangle(double random_range)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<double> vertex(-random_range, random_range);
    std::uniform_real_distribution<double> side(0, random_range);
    std::uniform_real_distribution<double> angle(0, 2*M_PI);
    std::uniform_int_distribution<unsigned int> color(0, 255);

    Point2d p(vertex(gen), vertex(gen));
    Color c(color(gen), color(gen), color(gen));

    *this = RightTriangle(p, side(gen), angle(gen));
    setColor(c);
}


double RightTriangle::area() const
{
    return (0.5 * a * b);
}

void RightTriangle::print(std::ostream &os) const
{
    os << "[RightTriangle]" << std::endl;
    os << "a = " << a << ", b = " << b << ", c = " << c << std::endl;

    Polygon::print(os);
}
