#include "shape.h"

Square::Square(Point  & center, Point & leftTopPoint) 
{
	this->mainPointToMove = center;
	this->leftTopPoint = leftTopPoint;
	myColor();
	ID += 1;
}

void Square::moveTo(Point const & newCenter) 
{
	this->leftTopPoint.x = leftTopPoint.x - (mainPointToMove.x - newCenter.x); 
	this->leftTopPoint.y = leftTopPoint.y - (mainPointToMove.y - newCenter.y); 
	this->mainPointToMove = newCenter;

}

void Square::rotate(double angle)
{
	double x_new, y_new;
	x_new = this->mainPointToMove.x + (this->leftTopPoint.x - this->mainPointToMove.x)*cos(angle) - (this->leftTopPoint.y - this->mainPointToMove.y)*sin(angle);
	y_new = this->mainPointToMove.y + (this->leftTopPoint.x - this->mainPointToMove.x)*sin(angle) + (this->leftTopPoint.y - this->mainPointToMove.y)*cos(angle);
	this->leftTopPoint.x = x_new;
	this->leftTopPoint.y = y_new;
}

void Square::scale(double k)
{
	double x_new, y_new;
	x_new = this->mainPointToMove.x + abs(this->leftTopPoint.x - this->mainPointToMove.x)*k;
	y_new = this->mainPointToMove.y + abs(this->leftTopPoint.y - this->mainPointToMove.y)*k;
	this->leftTopPoint.x = x_new;
	this->leftTopPoint.y = y_new;
}	