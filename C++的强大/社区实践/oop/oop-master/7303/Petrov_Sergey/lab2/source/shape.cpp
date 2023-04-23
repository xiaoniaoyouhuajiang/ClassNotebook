#include "shape.h"

unsigned long long Shape::global_id = 0;

Shape::Shape(const Point&position, const Color& color)
    :pos(position),
     color(color),
     angle(0),
     id(global_id)
{
    global_id++;
}

void Shape::set_color(const Color& color){
    this->color.set(color.red, color.green, color.blue);
}

void Shape::set_pos(const Point& p){
    pos.set(p.x, p.y);
}

Point Shape::get_pos() const{
    return pos;
}

Color Shape::get_color() const{
    return color;
}

double Shape::get_angle() const{
    return angle;
}

unsigned long long Shape::get_id() const{
    return id;
}

std::ostream& operator<<(std::ostream& os, Shape& s){
    os << "Position: " <<"("<< (int)s.get_pos().x << ","
                    << (int)s.get_pos().y << ")" << '\n';
    os << "Color: " <<"("<< (int)s.get_color().red << ","
                    << (int)s.get_color().green << ","
                    << (int)s.get_color().blue << ")" << '\n';
    os << "Angle: " << s.get_angle() << '\n';
    os << "Id: " << s.get_id() << '\n';
    return os;
}
