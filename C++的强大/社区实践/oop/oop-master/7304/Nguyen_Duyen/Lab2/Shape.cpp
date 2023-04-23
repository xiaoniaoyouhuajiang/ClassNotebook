#include "Shape.h"

Shape::Shape(){
}

Shape::Shape(Point A, double var_angle, Color& c){
	center.setX(A.getX());
	center.setY(A.getY());
	this->angle = var_angle;
	this->color = Color(c);
}

double Shape::getAngle() const{
	return angle;
}

Color Shape::getColor() const{
	return color;
}

void Shape::setAngle(double angle){
	this->angle = angle;
}

void Shape::setColor(Color &c){
	this->color = c;
}

void Shape::move(Point newCenter){
	for (int i = 0; i < peaks.size(); i++) {
		double newX = peaks[i].getX() + (newCenter.getX() - center.getX());
		double newY = peaks[i].getY() + (newCenter.getY() - center.getY());
		peaks[i].setX(newX);
		peaks[i].setY(newY);
	}
	center = newCenter;
}

void Shape::rotate(double angle){
	this->angle += angle;
	double rad = this->angle * pi / 180;
	for (int i = 0; i < peaks.size(); i++) {
		double x = peaks[i].getX() - center.getX();
		double y = peaks[i].getY() - center.getY();
		peaks[i].setX(x*cos(rad) - y * sin(rad) + center.getX());
		peaks[i].setY(x*sin(rad) + y * cos(rad) + center.getY());
	}
}

Shape::~Shape(){}
