#include "stdafx.h"
#include "Pentagon.h"
Pentagon::Pentagon(double y, double x, double side, double scale, int angle, string color) :Side(side) {

	MoveFigure(x, y);
	setColorFigure(color);
	setAngle(angle);
	setScale(scale);
	init();

};
Pentagon::Pentagon(double side) :Side(side) {

	setId(ID);
	ID++;
};

void Pentagon::init(){
	vector<Point> point;
	double R = Side*sin(54 * getKoeff()) / sin(72 * getKoeff()) * getScale();
	for (int i = 0; i < 5; i++){
		double tempX, tempY;
		tempX = R * cos((90 + 72 * i + getAngle()) * getKoeff()) + getX();
		tempY = R * sin((90 + 72 * i + getAngle()) * getKoeff()) + getY();
		tempX = round(tempX * 1000) / 1000;
		tempY = round(tempY * 1000) / 1000;
		point.push_back(Point(tempX, tempY));
	}
	setPoints(point);
}
