#include "shape.h"

sqTriangle::sqTriangle(Point const & mainPointToMove, Point const & leftTop, double length)
{
	this->mainPointToMove = mainPointToMove;
	this->leftTop = leftTop;
	this->length = length;
	myColor();
	ID += 1;
}
void sqTriangle::move_to(Point const & newPoint)
{
	this->leftTop.x -= mainPointToMove.x - newPoint.x;
	this->leftTop.y -= mainPointToMove.y - newPoint.y;
	this->mainPointToMove = newPoint;
}
void sqTriangle::rotate(double angle)
{
	double x_new, y_new;
	x_new = this->mainPointToMove.x + (this->leftTop.x - this->mainPointToMove.x)*cos(angle) - (this->leftTop.y - this->mainPointToMove.y)*sin(angle);
	y_new = this->mainPointToMove.y + (this->leftTop.x - this->mainPointToMove.x)*sin(angle) + (this->leftTop.y - this->mainPointToMove.y)*cos(angle);
	this->leftTop.x = x_new;
	this->leftTop.y = y_new;
}
void sqTriangle::scale(double k)
{
	double x_new, y_new;
	x_new = this->mainPointToMove.x + abs(this->leftTop.x - this->mainPointToMove.x)*k;
	y_new = this->mainPointToMove.y + abs(this->leftTop.y - this->mainPointToMove.y)*k;
	this->leftTop.x = x_new;
	this->leftTop.y = y_new;
	this->length *= k;
}