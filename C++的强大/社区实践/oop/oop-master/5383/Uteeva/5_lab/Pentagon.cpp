#include "Pentagon.h"
#include <cmath> 
#include <vector>
#include <algorithm>


Pentagon::Pentagon(const Point &p1, const Point &p2, const Point &p3, const Point &p4, const Point &p5, const Color &color) : Pentagon(color) {
	vector<Point> pointArr = { p1, p2, p3, p4, p5 };
	double centerX = (p1.x + p2.x + p3.x + p4.x + p5.x) / 5;
	double centerY = (p1.y + p2.y + p3.y + p4.y + p5.y) / 5;
	center = Point(centerX, centerY);

	if (pointArr.size() != 5) {
		throw std::invalid_argument("Некорректные координаты!");
	}
	this->points = pointArr;
	Id = ID;
	ID++;

}

Pentagon::Pentagon(const Color &color) :
	Shape(Point(0, 0), color), points{ Point(0, 0), Point(1, 0), Point(2, 1), Point(2, 2), Point(1, 1) } {
}


void Pentagon::rotate(double angle) {
	for (int i = 0; i < 5; i++)
	{
		double a = points[i].x;
		double b = points[i].y;
		points[i].x = a * cos(angle) - b * sin(angle);  //исп. матрица поворота
		points[i].y = a * sin(angle) + b * cos(angle);
	}
}

void Pentagon::ScaleFigure(double scale) {
	if (scale > 0) {
		for (int i = 1; i < 5; i++)
		{
			points[i].x = points[0].x + fabs(points[i].x - points[0].x)*scale;
			points[i].y = points[0].y + fabs(points[i].y - points[0].y)*scale;
		}
	}
	else {
		throw std::invalid_argument("Некорректный коэфициент! \n");
	}
}

std::ostream &operator<< (std::ostream &os, Shape &f)
{
	f.print(os);
	return os;
}

void Pentagon::print(std::ostream &os)
{
	os << "[Pentagon]" << std::endl;
	os << "Id: " << Id << std::endl;
	os << "Center( x , y ): ( " << center.x << " , " << center.y << " )" << std::endl;
	os << std::endl;
}

void Pentagon::Move(double dx, double dy) {
	Shape::Move(dx, dy);
	for (int i = 0; i < 5; ++i) {
		points[i].x += dx;
		points[i].y += dy;

	}
}

bool Pentagon::isPointInsideOfFigure(const Point &other) const {
	double square = this->getSquare();
	double thisSquare = countSquareForPoint(other);
	double ds = fabs(square - thisSquare);
	return ds < square*0.01;

}

bool Pentagon::isInsideOfAnother(const Shape &other) const {
	for (int i = 0; i < 5; ++i) {
		if (!other.isPointInsideOfFigure(points[i])) {
			return false;
		}
	}
	return true;
}



double Pentagon::getSquare() const {
	return countSquareForPoint(center);
}

double Pentagon::countSquareForPoint(const Point &other) const {
	double S = triangleS(other, points[0], points[5 - 1]);
	for (int i = 0; i < 5 - 1; ++i) {
		S = S + triangleS(other, points[i], points[i + 1]);
	}
	return S;
}


