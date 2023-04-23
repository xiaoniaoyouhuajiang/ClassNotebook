#include "stdafx.h"
#include "RegPentagon.h"
#include <cmath> 
#include <vector>

RegPentagon::RegPentagon(const Point &center, const Point &point, const Color &color) : Pentagon(color) {
	this->center = center;
	this->radius = sqrt(pow((point.x - center.x), 2) + pow((point.y - center.y), 2));
	double angleInRadius = (360 / 5) / 180 * 3.14;
	std::vector<Point> pointArr;
	pointArr.push_back(point);
	for (int i = 1; i < 5; i++) {
		double a = pointArr[i - 1].x - center.x;
		double b = pointArr[i - 1].y - center.y;
		double x = a * cos(angleInRadius) - b * sin(angleInRadius) + center.x;
		double y = a * sin(angleInRadius) + b * cos(angleInRadius) + center.y;
		pointArr.push_back(Point(x, y));
	}
	this->points = pointArr;
	Id = ID;
	ID++;
}


double RegPentagon::getRadius() const {
	return radius;
}
