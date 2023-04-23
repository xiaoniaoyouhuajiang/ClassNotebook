#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;
double delta = 0.0001;

void rotatex(double &coord, const double tempx, const double centerx, const double radangle, const double tempy, const double centery){
	coord = centerx + (tempx - centerx)*cos(radangle) - (tempy - centery)*sin(radangle);
}

void rotatey(double &coord, const double tempx, const double centerx, const double radangle, const double tempy, const double centery){
	coord = centery + (tempx - centerx)*sin(radangle) + (tempy - centery)*cos(radangle);
}

void lineqquation(double x1, double x2, double y1, double y2, double &k, double &b){
	if (x2 == x1){ x1 = x1 + delta; x2 = x2 - delta; }
	k = (y2 - y1) / (x2 - x1);
	b = y2 - x1*k;
}

void intersectionpoint(double k1, double k2, double b1, double b2, double &x, double &y){
	if (k1 == k2){ k1 = k1 + delta; k2 = k2 - delta; }
	x = (b2 - b1) / (k1 - k2);
	y = k1*x + b1;
}
double getlx(double a, double centerx, double side){
	a = centerx - side / 2;
	return a;
}
double getrx(double a, double centerx, double side){
	a = centerx + side / 2;
	return a;
}
double getty(double a, double centery, double side){
	a = centery + side / 2;
	return a;
}
double getdy(double a, double centery, double side){
	a = centery - side / 2;
	return a;
}
bool compare(double x11, double x12, double y11, double y12, double x21, double x22, double y21, double y22, double x23, double x24, double y23, double y24){
	double k1 = 0, b1 = 0, k2 = 0, b2 = 0, x = 0, y = 0;
	lineqquation(x11, x12, y11, y12, k1, b1); // 1 сторона
	lineqquation(x21, x22, y11, y22, k2, b2);
	intersectionpoint(k1, k2, b1, b2, x, y);
	if (((x > x11) && (x<x12)) || ((x>x12) && (x<x11))) return true; // c 1
	lineqquation(x22, x23, y22, y23, k2, b2);
	intersectionpoint(k1, k2, b1, b2, x, y);
	if (((x > x11) && (x<x12)) || ((x>x12) && (x<x11))) return true; // c 2
	lineqquation(x23, x24, y23, y24, k2, b2);
	intersectionpoint(k1, k2, b1, b2, x, y);
	if (((x > x11) && (x<x12)) || ((x>x12) && (x<x11))) return true; // c 3
	lineqquation(x24, x21, y24, y21, k2, b2);
	intersectionpoint(k1, k2, b1, b2, x, y);
	if (((x > x11) && (x<x12)) || ((x>x12) && (x<x11))) return true; // c 4
	return false;
}

class Shape{
protected:
	double centerx, centery; // координаты центра
	string color; // цвет 
public:
	double ltx, lty, ldx, ldy, rdx, rdy, rtx, rty; // координаты углов
	int angle; // угол на который повернута фигура
	Shape(double centerx, double centery, int angle, string color = "white") : centerx(centerx), centery(centery), angle(angle), color(color) {}
	virtual ~Shape() {}
	virtual void move(double newcenterx, double newcentery) = 0;
	void rotate(int newangle){ // www.abakbot.ru/online-2/91-rotate
		double radangle = newangle * 3.14 / 180;
		double templtx = ltx; double templdx = ldx; double temprtx = rtx; double temprdx = rdx; double templty = lty; double templdy = ldy; double temprty = rty; double temprdy = rdy;
		rotatex(ltx, templtx, centerx, radangle, templty, centery);
		rotatey(lty, templtx, centerx, radangle, templty, centery);
		rotatex(rtx, temprtx, centerx, radangle, temprty, centery);
		rotatey(rty, temprtx, centerx, radangle, temprty, centery);
		rotatex(ldx, templdx, centerx, radangle, templdy, centery);
		rotatey(ldy, templdx, centerx, radangle, templdy, centery);
		rotatex(rdx, temprdx, centerx, radangle, temprdy, centery);
		rotatey(rdy, temprdx, centerx, radangle, temprdy, centery);
		angle = (angle + newangle) % 360;
	};
	virtual void scale(int n) = 0;
	void setcolor(string newcolor) { // устанавливает новый цвет фигуры
		color = newcolor;
	}
	string getcolor() const { // возвращает текущий цвет фигуры
		return color;
	}
	virtual string gettype() const = 0;
	virtual double square() const = 0;
	virtual bool check(Shape& shape1, Shape& shape2){
		bool answer = false;
		answer = compare(shape1.ltx, shape1.ldx, shape1.lty, shape1.ldy, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		answer = compare(shape1.ldx, shape1.rdx, shape1.ldy, shape1.rdy, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		answer = compare(shape1.rdx, shape1.rtx, shape1.rdy, shape1.rty, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		answer = compare(shape1.rtx, shape1.ltx, shape1.rty, shape1.lty, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		return answer;
	}
	friend ostream& operator <<(ostream& os, const Shape& shape){ // оператор вывода
		string type = shape.gettype();
		os << endl << "Type: " << type << endl << endl;
		os << endl << "Current coords: " << "(" << shape.ltx << ";" << shape.lty << ")	(" << shape.ldx << ";" << shape.ldy << ")	(" << shape.rdx << ";" << shape.rdy << ")	(" << shape.rtx << ";" << shape.rty << ")" << endl;
		os << endl << "Current angle: " << shape.angle << endl;
		string temp = shape.getcolor();
		os << endl << "Current color: " << temp << endl << endl;
		return os;
	}
};


class Rectangle : public Shape{ // класс - прямоугольник
private:
	double width, height; // начальная ширина и высота прямоугольника
public:
	Rectangle(double width, double height, double centerx, double centery, int angle = 0, string color = "white") : Shape(centerx, centery, angle, color), width(width), height(height){ // прямоугольник задается через центр, высоту и ширину, потом высчитываются координаты углов
		ldx = ltx = getlx(ldx, centerx, width); rdx = rtx = getrx(rdx, centerx, width);
		lty = rty = getty(lty, centery, height); ldy = rdy = getdy(ldy, centery, height);
	}
	void move(double newcenterx, double newcentery){ // смещается центр, далее высчитываются углы
		centerx = newcenterx; centery = newcentery;
		ldx = ltx = getlx(ldx, centerx, width); rdx = rtx = getrx(rdx, centerx, width);
		lty = rty = getty(lty, centery, height); ldy = rdy = getdy(ldy, centery, height);
	}
	void scale(int n){ // увеличиваются стороны, далее высчитываются углы
		width *= n; height *= n;
		ldx = ltx = getlx(ldx, centerx, width); rdx = rtx = getrx(rdx, centerx, width);
		lty = rty = getty(lty, centery, height); ldy = rdy = getdy(ldy, centery, height);
	}
	string gettype()const { // возвращает тип фигуры
		string tmp = "Rectangle";
		return tmp;
	}
	double square() const override
	{
		return width*height;
	}
};

class Square : public Shape{ // класс - квадрат
private:
	double side; // размер стороны
public:
	Square(double side, double centerx, double centery, int angle = 0, string color = "white") : Shape(centerx, centery, angle, color), side(side) {// квадрат задается через центр и сторону, потом высчитываются координаты углов
		ldx = ltx = getlx(ldx, centerx, side); rdx = rtx = getrx(rdx, centerx, side);
		lty = rty = getty(lty, centery, side); ldy = rdy = getdy(ldy, centery, side);
	}
	void move(double newcenterx, double newcentery){ //аналогично с прямоугольником
		centerx = newcenterx; centery = newcentery;
		ldx = ltx = getlx(ldx, centerx, side); rdx = rtx = getrx(rdx, centerx, side);
		lty = rty = getty(lty, centery, side); ldy = rdy = getdy(ldy, centery, side);
	}
	void scale(int n){ //аналогично с прямоугольником
		side *= n;
		ldx = ltx = getlx(ldx, centerx, side); rdx = rtx = getrx(rdx, centerx, side);
		lty = rty = getty(lty, centery, side); ldy = rdy = getdy(ldy, centery, side);
	}
	string gettype() const { // возвращает тип фигуры
		string tmp = "Square";
		return tmp;
	}
	double square() const override
	{
		return side*side;
	}
};

class Ellipse : public Shape{ //класс - эллипс
private:
	double wradius, hradius;
public:
	Ellipse(double wradius, double hradius, double centerx, double centery, int angle = 0, string color = "white") : Shape(centerx, centery, angle, color), wradius(wradius), hradius(hradius){// эллипс задается через два радиуса: "ширины" и "высоты", потом высчитываются координаты крайних точен этих радиусов (эллипс мысленно поворачивается ~45 град влево)
		ltx = rdx = centerx; rtx = centerx + wradius; ldx = centerx - wradius;
		ldy = rty = centery; lty = centery + hradius; rdy = centery - hradius;
	}
	void move(double newcenterx, double newcentery){//аналогично с прямоугольником
		centerx = newcenterx; centery = newcentery;
		ltx = rdx = centerx; rtx = centerx + wradius; ldx = centerx - wradius;
		ldy = rty = centery; lty = centery + hradius; rdy = centery - hradius;
	}
	void scale(int n){ //аналогично с прямоугольником
		wradius *= n; hradius *= n;
		rtx = centerx + wradius; ldx = centerx - wradius;
		lty = centery + hradius; rdy = centery - hradius;
	}
	string gettype() const { // возвращает тип фигуры
		string tmp = "Ellipse";
		return tmp;
	}
	double square() const override
	{
		return wradius*hradius*3.14;
	}
};
