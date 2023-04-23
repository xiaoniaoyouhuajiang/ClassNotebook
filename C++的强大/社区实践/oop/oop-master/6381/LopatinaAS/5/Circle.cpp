#include "Circle.h"
#include <iostream>

Circle::Circle(unsigned radius, Dot* center, std::string color_sh) : radius(radius), angle(0) {
	this->set_dots(center);
	this->set_color(color_sh);
	int per = perimetr();
	this->set_perimetr(per);
	id = currentId;
	currentId++;
}

void Circle::print() const {
	std::cout << "This is a circle. ID: " << id << std::endl;
	std::cout << "The centre: " << (*dots1()).x1() << ";" << (*dots1()).y1() << std::endl;
	std::cout << "The radius: " << radius << std::endl;
	std::cout << "The angle: " << angle << std::endl;
	std::cout << "The color: " << get_color() << std::endl;
	std::cout << "Perimetr: " << get_perimetr()<< std::endl;
}

void Circle::set_angle(unsigned angle){
	this->angle = angle % 360;
}

int Circle::get_angle(){
	return this->angle;
}

void Circle::rotation(double angle){
	this->set_angle(this->get_angle() + angle);
}

void Circle::scaling(double k) {
	radius = radius*k;
	dots1()->set_x(dots1()->x1()*k);
	dots1()->set_y(dots1()->y1()*k);
}

void Circle::move(double x_plus, double y_plus) {
	dots1()->set_x(dots1()->x1() + x_plus);
	dots1()->set_y(dots1()->y1() + y_plus);
}

int Circle::perimetr() {
	return 2*3.14*radius;
}