#include "shape.h"

unsigned long Shape::global_ID = 0;

void Shape::set_color(const Color &color) {
	this->color.set(color.red, color.green, color.blue);
}

Color Shape::get_color() const {
	return color;
}

void Shape::set_pos(const Point &point) {
	this->pos.set(point.x, point.y);
}

Point Shape::get_pos() const {
	return pos;
}

double Shape::get_angle() const {
	return angle;
}
unsigned long Shape::get_ID() const{
	return ID;
}

std::ostream& operator <<(std::ostream &out, const Shape &shape) {
	out << "Center position: (" << shape.get_pos().x << "; " << shape.get_pos().y << ")\n";
	out << "Angle: " << shape.get_angle() << "\n";
	out << "Color: (" << (int)shape.get_color().red << "; " << (int)shape.get_color().green
		<< "; " << (int)shape.get_color().blue << ")\n";
	out<< "ID: " << shape.ID<<"\n";
	return out;
}

Shape::Shape(const Point& p, const Color& c,double _angle) :
	pos(p), color(c), angle(_angle),ID(global_ID) {
		global_ID++;
}
