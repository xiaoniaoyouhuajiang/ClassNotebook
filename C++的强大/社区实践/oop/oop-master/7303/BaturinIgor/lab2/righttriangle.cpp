#include "righttriangle.h"

rightTriangle::rightTriangle() : a(0), b(0), c(0)
{

}

rightTriangle::rightTriangle(Point& center ,Point& p1, Point& p2, Point& p3)
    : center(center)
    , p1(p1)
    , p2(p2)
    , p3(p3)
{
    a = p1.length(p2);
    b = p2.length(p3);
    c = p3.length(p1);
    if ((int)a != (int)b && (int)a != (int)c) { std::cout << "ERROR"; exit(0); }
}

rightTriangle::rightTriangle(rightTriangle& other)
    : a(other.a), b(other.b), c(other.c)
    , p1(other.p1), p2(other.p2), p3(other.p3)
    , coefficient(other.coefficient), center(other.center)
{

}

rightTriangle::rightTriangle(Color& color) : Shape(color)
{

}

void rightTriangle::scale(double coefficient) {
    this->coefficient = coefficient;
    this->p2.x = (int)(this->p2.x-this->p1.x) * coefficient;
    this->p2.y = (int)(this->p2.y-this->p1.y) * coefficient;
    this->p3.x = (int)(this->p3.x-this->p1.x) * coefficient;
    this->p3.y = (int)(this->p3.y-this->p1.y) * coefficient;
    a *= coefficient;
    b *= coefficient;
    c *= coefficient;
}

void rightTriangle::rotate(double angle) {
    p1.rotate(angle);
    p2.rotate(angle);
    p3.rotate(angle);
}

void rightTriangle::move(const Point& center) {
    double old_center_coordinates_x = this->center.x;
    double old_center_coordinates_y = this->center.y;
    this->p1.x = this->p1.x + center.x - old_center_coordinates_x;
    this->p1.y = this->p1.y + center.y - old_center_coordinates_y;
    this->p2.x = this->p2.x + center.x - old_center_coordinates_x;
    this->p2.y = this->p2.y + center.y - old_center_coordinates_y;
    this->p3.x = this->p3.x + center.x - old_center_coordinates_x;
    this->p3.y = this->p3.y + center.y - old_center_coordinates_y;
    this->center.x = center.x;
    this->center.y = center.y;
}

std::ostream& operator << (std::ostream &print, rightTriangle& rightTriangle) {
    print << "Current center coordinates: A(" << rightTriangle.center.x << ", " << rightTriangle.center.y
          << ")\nCurrent points coordinates: P1(" << rightTriangle.p1.x << ", " << rightTriangle.p1.y << "), "
          << "P2(" << rightTriangle.p2.x << ", " << rightTriangle.p2.y << "), " << "P3(" << rightTriangle.p3.x << ", "
          << rightTriangle.p3.y << ")" << std::endl << "Current lengths of the sides of the rightTriangle: a - "
          << int(rightTriangle.a) << ", b - " << (int)rightTriangle.b << ", c - " << (int)rightTriangle.c << std::endl
          << "Current ID: " << rightTriangle.global_id << std::endl
          << "Current color: (" << rightTriangle.color.red << ", " << rightTriangle.color.green << ", " << rightTriangle.color.blue << ")" << std::endl;
    return print;
}