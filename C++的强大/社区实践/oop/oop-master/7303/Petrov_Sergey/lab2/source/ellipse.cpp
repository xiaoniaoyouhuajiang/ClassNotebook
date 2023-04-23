#include "ellipse.h"

Ellipse::Ellipse(const Point& center, double a, double b, const Color& color)
    :Shape(center, color),
     a(a),
     b(b){}

Ellipse::Ellipse(const Ellipse& other)
    :Shape(other.pos, other.color),
     a(other.a),
     b(other.b){}

void Ellipse::move(const Point& p){
    pos = p;
}

void Ellipse::scale(double scale){
    a *= scale;
    b *= scale;
}

void Ellipse::turn(double angle){
    this->angle += angle;
}

double Ellipse::get_radius1() const{
    return a;
}


double Ellipse::get_radius2() const{
    return b;
}

std::ostream& operator<<(std::ostream& os, Ellipse& s){
    os << "---Ellipse---\n";
    os << (Shape&)s;
    os << "Radiuses: " << s.get_radius1() << " " << s.get_radius2() << '\n';
    os << "-------------\n";
}
