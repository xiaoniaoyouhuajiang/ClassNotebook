#include "square.h"

Square::Square(double random_range)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<double> vertex(-random_range, random_range);
    std::uniform_real_distribution<double> side(0, random_range);
    std::uniform_real_distribution<double> angle(0, 2*M_PI);
    std::uniform_int_distribution<unsigned int> color(0, 255);

    Point2d p(vertex(gen), vertex(gen));
    Color c(color(gen), color(gen), color(gen));

    *this = Square(p, side(gen), angle(gen));
    setColor(c);
}

void Square::print(std::ostream &os) const
{
    os << "[Square]" << std::endl;
    os << "side = " << leftSide << std::endl;

    Polygon::print(os);
}
