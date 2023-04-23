#include "stdafx.h"
#include "Point.h"

Point::Point(double X=0, double Y=0){
	x = X;
	y = Y;
}
void Point::setCoord(double X, double Y){
	x = X;
	y = Y;
}
void Point::setX(double X){
	x = X;
}
void Point::setY(double Y){
	y = Y;
}
/*double* Point::getCoord(){
	double *p = new double[2];
	p[0] = x;
	p[1] = y;
	return p;
}*/
double Point::getX()const {
	return x;
}
double Point::getY()const {
	return y;
}