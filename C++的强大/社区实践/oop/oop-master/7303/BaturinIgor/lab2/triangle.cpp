#include "triangle.h"

Triangle::Triangle() : a(0), b(0), c(0)
{

}

Triangle::Triangle(Point& center ,Point& p1, Point& p2, Point& p3)
    : center(center)
    , p1(p1)
    , p2(p2)
    , p3(p3)
{
    a = p1.length(p2);
    b = p2.length(p3);
    c = p3.length(p1);
}

Triangle::Triangle(Color& color) : Shape(color)
{

}

void Triangle::scale(double coefficient) {
    this->coefficient = coefficient;
    this->p2.x = (this->p2.x-this->p1.x) * coefficient;
    this->p2.y = (this->p2.y-this->p1.y) * coefficient;
    this->p3.x = (this->p3.x-this->p1.x) * coefficient;
    this->p3.y = (this->p3.y-this->p1.y) * coefficient;
    a *= coefficient;
    b *= coefficient;
    c *= coefficient;
}

void Triangle::rotate(double angle) {
    p1.rotate(angle);
    p2.rotate(angle);
    p3.rotate(angle);
}

void Triangle::move(const Point& center) {
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

std::ostream& operator << (std::ostream &print, Triangle& triangle) {
    print << "Current center coordinates: A(" << triangle.center.x << ", " << triangle.center.y
          << ")\nCurrent points coordinates: P1(" << triangle.p1.x << ", " << triangle.p1.y << "), "
          << "P2(" << triangle.p2.x << ", " << triangle.p2.y << "), " << "P3(" << triangle.p3.x << ", "
          << triangle.p3.y << ")" << std::endl << "Current lengths of the sides of the triangle: a - "
          << triangle.a << ", b - " << triangle.b << ", c - " << triangle.c << std::endl
          << "Current ID: " << triangle.global_id << std::endl
          << "Current color: (" << triangle.color.red << ", " << triangle.color.green << ", " << triangle.color.blue << ")" << std::endl;
    return print;
}