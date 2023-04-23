#include "circle.h"


circle::circle(const point& center, double radius, const Color& color) :
    figure(color), center(center), radius(radius) {}

circle::circle(const circle& other) : circle(other.center, other.radius, other.color) {}

circle& circle::operator=(const circle& other) {
    center = other.center;
    color = other.color;
    radius = other.radius;
    return *this;
}

void circle::scale(double num) {
    radius *= num;
}

void circle::turn(double alpha) {
}

void circle::shift(double x, double y) {
    center += point(x, y);
}

void circle::distance(double x, double y) {
    return max((point(x, y) - center).len(), 0.);
}

void circle::print(std::ostream& os) {
    os << "Центр круга находится в точке " << center.getX() << ' ' << center.getY() << "\n";
    os << "Радиус равен " << radius << "\n";
}
