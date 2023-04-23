#include "stdafx.h"
#include "Rectangle.h"
Rectangle::Rectangle(double y, double x, double side1, double side2, double scale, int angle, string color) :SideX(side1), SideY(side2) {

	MoveFigure(x, y);
	setColorFigure(color);
	setAngle(angle);
	setScale(scale);
	init();
};
Rectangle::Rectangle(double side1, double side2) :SideX(side1), SideY(side2) {

	setId(ID);
	init();
	ID++;
};

void Rectangle::init(){
	vector<Point> point;
	
	double R=sqrt(SideX*SideX+SideY*SideY)/2*getScale();
	double startAngle = atan(SideY / SideX) + getAngle() * getKoeff();
	point=side(R, startAngle, point);
	startAngle += (M_PI - 2 * atan(SideY/ SideX));
	point = side(R, startAngle, point);
	startAngle += M_PI - (2 * atan(SideX / SideY));
	point = side(R, startAngle, point);
	startAngle +=( M_PI - 2 * atan(SideY / SideX));
	point = side(R, startAngle, point);
	setPoints(point);
}
vector<Point> Rectangle::side(double R, double startAngle, vector<Point> point) {
	double tempX, tempY;
	tempX = R * cos(startAngle)+getX() ;
	tempY = R * sin(startAngle) + getY();
	tempX = round(tempX * 1000) / 1000;
	tempY = round(tempY * 1000) / 1000;
	point.push_back(Point(tempX, tempY));
	return point;

}