#include "shapes.h"
#include <cstdio>
#include <cmath>
#include <iostream>

std::ostream &operator<<(std::ostream &s, const Dot& dot) { // вывод в поток
    s << "x: " << dot.x << " y: " << dot.y;
    return s;
}

double Dot::x1() const { // геттер для х
	return x;
}

void Dot::set_x(double x) { // сеттер для х
	this->x = x;
}

double Dot::y1() const { // геттер для у
	return y;
}

void Dot::set_y(double y) { // сеттер для у
	this->y = y;
}

int Color::r1() { // геттер для красного
	return transform(r_);
}
 
void Color::set_r(char r) { // сеттер для красного
	this->r_ = r;
}

int Color::g1() { // геттер для зеленого
	return transform(g_);
}

void Color::set_g(char g) { // сеттер для зеленого
	this->g_ = g;
}

int Color::b1() { // геттер для синего
	return transform(b_);
}

void Color::set_b(char b) { // сеттер для синего
	this->b_ = b;
}

int Color::transform(char c) { // преобразование char в int
	if (c == 0)
		return 0;
	if (c > 0)
		return c;
	return 256 + c;
}

std::ostream &operator<<(std::ostream &s, Color& color) { // вывод в поток
	s << "r: " << color.r1() << " g: " << color.g1() << " b: " << color.b1() <<std:: endl;
	return s;
}

Dot* Shape::dots1() const { // геттер для координат
	return dots_;
}

void Shape::set_dots(Dot* dots) { // сеттер для координат
	this->dots_ = dots;
}

Color* Shape::color1() const { // геттер для цвета
	return color_;
}

void Shape::set_color(Color* color) {
	this->color_ = color;
}
 
void Shape::move(double x_plus, double y_plus) {
	for (int i = 0; i < 4; i++){
		dots1()[i].set_x(dots1()[i].x1()+x_plus); 
		dots1()[i].set_y(dots1()[i].y1()+y_plus); 
	}
}

int Shape::currentId = 1;

Circle::Circle(unsigned radius, Dot* center, Color* color): radius(radius) {
	this->set_dots(center);
	this->set_color(color);
	id = currentId;
	currentId++;
}

std::ostream &operator<<(std::ostream &s, const Circle &circle) {
  	s << "This is a circle. ID: " << circle.id << std::endl;
	s << "The centre: " << *(circle.dots1()) << std::endl;
	s << "The radius: " << circle.radius << std::endl;
	s << "The color: " << *(circle.color1());
    return s;
}

void Circle::rotation(double angle) {} 

void Circle::scaling(double k) { 
    radius = radius*k;
}

Rectangle::Rectangle(double x, double y, unsigned width, unsigned height, class Color* color): width(width), height(height) { // widgh - ширина, height - длина
	Dot* dots = new Dot[4];
	dots[0].set_x(x); // левая нижняя вершина
	dots[0].set_y(y);
	dots[1].set_x(x); // левая верхняя вершина
	dots[1].set_y(y+height); 
	dots[2].set_x(x+width); // правая верхняя вершина 
	dots[2].set_y(y+height);
	dots[3].set_x(x+width); // правая нижняя вершина
	dots[3].set_y(y); 
	
	
	this->set_dots(dots);
	this->set_color(color);
	id = currentId;
	currentId++;
}

std::ostream &operator<<(std::ostream &s, const  Rectangle& rectangle) {
	s << "This is a rectangle. ID: " << rectangle.id << std::endl;	
	s << "Bottom left: " << rectangle.dots1()[0] << std::endl;
	s << "Top left: " << rectangle.dots1()[1] << std::endl;
	s << "Top right: " << rectangle.dots1()[2] << std::endl;
	s << "Bottom right: " << rectangle.dots1()[3] << std::endl;
	s << "The color: " << *(rectangle.color1());
	return s;
}

void Rectangle::rotation(double angle) {
	int a, b;
	for (int i = 0; i < 4; i++) {
		a = dots1()[i].x1();
		b = dots1()[i].y1();
        dots1()[i].set_x(a * cos(angle) - b * sin(angle));
		dots1()[i].set_y(a * sin(angle) + b * cos(angle));
    }
} 

void Rectangle::scaling(double k) { 
   for (int i = 1; i < 4; i++) {
        dots1()[i].set_x(dots1()[0].x1() + fabs(dots1()[i].x1() - dots1()[0].x1())*k);
        dots1()[i].set_y(dots1()[0].y1() + fabs(dots1()[i].y1() - dots1()[0].y1())*k);
    }
}

Trapezoid::Trapezoid(double shortX, double shortY, double longX, double longY, unsigned short_width, unsigned long_width, Color* color){
	height = abs(longY - shortY);
	Dot* dots = new Dot[4];
	dots[0].set_x(longX); // нижняя левая точка
	dots[0].set_y(longY);
	dots[1].set_x(shortX); // верхняя левая точка
	dots[1].set_y(shortY);
	dots[2].set_x(shortX + short_width); // верхняя правая точка
	dots[2].set_y(shortY);
	dots[3].set_x(longX + long_width); // нижняя правая точка
	dots[3].set_y(longY);
	this->set_dots(dots);
	this->set_color(color);
	id = currentId;
	currentId++;
}

std::ostream &operator<<(std::ostream &s, const  Trapezoid& trapezoid) {
	s << "This is a trapezoid. ID: " << trapezoid.id << std::endl;	
	s << "The dots of the upper base: " << std::endl;
	s << trapezoid.dots1()[1] << std::endl;
	s << trapezoid.dots1()[2] << std::endl;
	s << "The dots of the lower base: " << std::endl;
	s << trapezoid.dots1()[0] << std::endl;
	s << trapezoid.dots1()[3] << std::endl;
	s << "The color: " << *(trapezoid.color1());
	return s;
}

void Trapezoid::rotation(double angle) {
	int a, b;
	for (int i = 0; i < 4; i++) {
		a = dots1()[i].x1();
		b = dots1()[i].y1();
        dots1()[i].set_x(a * cos(angle) - b * sin(angle));
        dots1()[i].set_y(a * sin(angle) + b * cos(angle));
    }
} 

void Trapezoid::scaling(double k) { 
   for (int i = 1; i < 4; i++) {
        dots1()[i].set_x(dots1()[0].x1() + fabs(dots1()[i].x1() - dots1()[0].x1())*k);
        dots1()[i].set_y(dots1()[0].y1() + fabs(dots1()[i].y1() - dots1()[0].y1())*k);
    }
}