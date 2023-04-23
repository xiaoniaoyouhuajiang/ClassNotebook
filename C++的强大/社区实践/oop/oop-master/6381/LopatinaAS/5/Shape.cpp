#include "Shape.h"
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

Dot* Shape::dots1() const { // геттер для координат
	return dots_;
}

void Shape::set_dots(Dot* dots) { // сеттер для координат
	this->dots_ = dots;
}

std::string Shape::get_color() const{
	return this->color;
}

void Shape::set_color(string color_sh){
	this->color = color_sh;
}

void Shape::set_perimetr(int per) { 
	this->prm = per;
}

int Shape::get_perimetr() const{
	return this->prm;
}

int Shape::currentId = 1;