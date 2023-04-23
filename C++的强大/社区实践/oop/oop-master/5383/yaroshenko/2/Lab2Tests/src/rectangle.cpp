#include "rectangle.h"

Rectangle::Rectangle(const Point2d &vertex, double _upperSide, double _leftSide, double angle) :

    Polygon({ vertex,
              Point2d(vertex.x + _upperSide, vertex.y),
              Point2d(vertex.x, vertex.y - _leftSide),
              Point2d(vertex.x + _upperSide, vertex.y - _leftSide) }),

    upperSide(_upperSide),
    leftSide(_leftSide)

{
    if (upperSide <= 0)
        throw std::invalid_argument("upperSide should be non-negative");
    if (leftSide <= 0)
        throw std::invalid_argument("leftSide should be non-negative");

    rotate(angle);
}

Rectangle::Rectangle(double random_range)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<double> vertex(-random_range, random_range);
    std::uniform_real_distribution<double> side(0, random_range);
    std::uniform_real_distribution<double> angle(0, 2*M_PI);
    std::uniform_int_distribution<unsigned int> color(0, 255);

    Point2d p(vertex(gen), vertex(gen));
    Color c(color(gen), color(gen), color(gen));

    *this = Rectangle(p, side(gen), side(gen), angle(gen));
    setColor(c);
}


double Rectangle::area() const
{
    return (upperSide * leftSide);
}


double Rectangle::perimeter() const
{
    return (2 * (upperSide + leftSide));
}


void Rectangle::scale(double scale)
{
    upperSide *= scale;
    leftSide *= scale;

    Polygon::scale(scale);
}


double Rectangle::getUpperSide() const
{
    return upperSide;
}


double Rectangle::getLeftSide() const
{
    return leftSide;
}


void Rectangle::split(Rectangle* rect, Triangle* part1, Triangle* part2)
{
    if (rect)
    {
        *part1 = Triangle(rect->vertices[0], rect->vertices[1], rect->vertices[2]);
        *part2 = Triangle(rect->vertices[1], rect->vertices[2], rect->vertices[3]);

        delete rect;
    }
    else
    {
        throw std::invalid_argument("nullptr");
    }
}

void Rectangle::print(std::ostream &os) const
{
    os << "[Rectangle]" << std::endl;
    os << "upperSide = " << upperSide << ", " << "leftSide = " << leftSide << std::endl;

    Polygon::print(os);
}
