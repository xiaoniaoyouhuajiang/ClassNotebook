#include "Rectangle.h"
#include <math.h>
#include <iostream>

Rectangle::Rectangle(double x, double y, unsigned width, unsigned height, std::string color_sh) : width(width), height(height) { 
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
	this->set_color(color_sh);
	int per = perimetr();
	this->set_perimetr(per);
	id = currentId;
	currentId++;
}

void Rectangle::print () const {
	std::cout << "This is a rectangle. ID: " << id << std::endl;
	std::cout << "(" << dots1()[1].x1() << ";" << dots1()[1].y1() << ")";
	std::cout << "(" << dots1()[2].x1() << ";" << dots1()[2].y1() << ")" << std::endl;
	std::cout << "(" << dots1()[0].x1() << ";" << dots1()[0].y1() << ")";
	std::cout << "(" << dots1()[3].x1() << ";" << dots1()[3].y1() << ")" << std::endl;
	std::cout << "The color: " << get_color()<< std::endl;
	std::cout << "Perimetr: " << get_perimetr()<< std::endl;
}

void Rectangle::move(double x_plus, double y_plus) {
	for (int i = 0; i < 4; i++) {
		dots1()[i].set_x(dots1()[i].x1() + x_plus);
		dots1()[i].set_y(dots1()[i].y1() + y_plus);
	}
}

void Rectangle::rotation(double angle) {
	double rad = angle * (3.1415926535 / 180);
	double x, y;
	double centreX = (dots1()[1].x1() + dots1()[3].x1()) / 2;
	double centreY = (dots1()[1].y1() + dots1()[3].y1()) / 2;
	for (int i = 0; i < 4; i++) {
		x = dots1()[i].x1() - centreX;
		y = dots1()[i].y1() - centreY;
		dots1()[i].set_x(x * cos(rad) - y * sin(rad) + centreX);
		dots1()[i].set_y(x * sin(rad) + y * cos(rad) + centreY);
	}
}

void Rectangle::scaling(double k) {
	for (int i = 1; i < 4; i++) {
		dots1()[i].set_x(dots1()[0].x1() + fabs(dots1()[i].x1() - dots1()[0].x1())*k);
		dots1()[i].set_y(dots1()[0].y1() + fabs(dots1()[i].y1() - dots1()[0].y1())*k);
	}
}

int Rectangle::perimetr() {
	int a[4];
	a[0] = dots1()[1].y1() -  dots1()[0].y1();
	a[1] = dots1()[2].x1() -  dots1()[1].x1();
	a[2] = dots1()[2].y1() - dots1()[3].y1();
	a[3] = dots1()[3].x1() -  dots1()[0].x1();
	return a[0]+a[1]+a[2]+a[3];
}