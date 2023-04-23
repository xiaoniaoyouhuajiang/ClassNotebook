#include "Trapezoid.h"
#include <math.h>
#include <iostream>

Dot* Trapezoid::getCentre() {
	return this->centre;
}

void Trapezoid::setCentre(double x, double y) {
	this->centre->set_x(x);
	this->centre->set_y(y);
}

Trapezoid::Trapezoid(double shortX, double shortY, double longX, double longY, unsigned short_width, unsigned long_width, std::string color_sh) {
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
	this->set_color(color_sh);
	int per = perimetr();
	this->set_perimetr(per);

	this->centre = new Dot();
	this->setCentre(
		(longX + shortX + (short_width + long_width) / 2) / 2, 
		(shortY + longY) / 2 
	);
	id = currentId;
	currentId++;
}

void Trapezoid::print () const {
	std::cout << "This is a trapezoid. ID: " << id << std::endl;
	std::cout << "The dots of the upper base: " << std::endl;
	std::cout << "(" << dots1()[1].x1() << ";" << dots1()[1].y1() << ")";
	std::cout << "(" << dots1()[2].x1() << ";" << dots1()[2].y1() << ")" << std::endl;
	std::cout << "The dots of the lower base: " << std::endl;
	std::cout << "(" << dots1()[0].x1() << ";" << dots1()[0].y1() << ")";
	std::cout << "(" << dots1()[3].x1() << ";" << dots1()[3].y1() << ")" << std::endl;
	std::cout << "The color: " << get_color() << std::endl;
	std::cout << "Perimetr: " << get_perimetr()<< std::endl;
}

void Trapezoid::rotation(double angle) {
	double rad = angle * (3.1415926535 / 180);
	double x, y;
	for (int i = 0; i < 4; i++) {
		x = dots1()[i].x1() - centre->x1();
		y = dots1()[i].y1() - centre->y1();
		dots1()[i].set_x(x * cos(rad) - y * sin(rad) + centre->x1());
		dots1()[i].set_y(x * sin(rad) + y * cos(rad) + centre->y1());
	}
}

void Trapezoid::scaling(double k) {
	for (int i = 1; i < 4; i++) {
		dots1()[i].set_x(dots1()[0].x1() + fabs(dots1()[i].x1() - dots1()[0].x1())*k);
		dots1()[i].set_y(dots1()[0].y1() + fabs(dots1()[i].y1() - dots1()[0].y1())*k);
	}
}

void Trapezoid::centreMove(double x_plus, double y_plus) {
	setCentre(centre->x1() + x_plus, centre->y1() + y_plus);
}

void Trapezoid::move(double x_plus, double y_plus) {
	for (int i = 0; i < 4; i++) {
		dots1()[i].set_x(dots1()[i].x1() + x_plus);
		dots1()[i].set_y(dots1()[i].y1() + y_plus);
	}
	setCentre(x_plus, y_plus);
}

int Trapezoid::perimetr() {
	int a[4];
	a[0] = sqrt((dots1()[1].x1() -  dots1()[0].x1())*(dots1()[1].x1() -  dots1()[0].x1()) + (dots1()[1].y1() -  dots1()[0].y1())*(dots1()[1].y1() -  dots1()[0].y1())); 
	a[1] = dots1()[2].x1() -  dots1()[1].x1();
	a[2] = sqrt((dots1()[2].x1() -  dots1()[3].x1())*(dots1()[2].x1() -  dots1()[3].x1()) + (dots1()[2].y1() -  dots1()[3].y1())*(dots1()[2].y1() -  dots1()[3].y1()));
	a[3] = dots1()[3].x1() -  dots1()[0].x1();
	return a[0]+a[1]+a[2]+a[3];
}