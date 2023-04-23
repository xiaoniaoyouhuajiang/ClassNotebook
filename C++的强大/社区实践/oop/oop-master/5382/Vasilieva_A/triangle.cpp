#include "shape.h"

Triangle::Triangle(Point const & mainPointToMove, Point const & left, double length)
{
	cout << "≈сли вы ввели отрицательную длину, то  катет/высота треугольника будут достроены по часовой стрелке от первого катета." << endl;
	this->mainPointToMove = mainPointToMove;
	this->leftTopPoint = left;
	this->length = length;
	myColor();
	ID += 1;
}
void Triangle::moveTo(Point const & newPoint)
{
	this->leftTopPoint.x -= mainPointToMove.x - newPoint.x;
	this->leftTopPoint.y -= mainPointToMove.y - newPoint.y;
	this->mainPointToMove = newPoint;
}
void Triangle::rotate(double angle)
{
	double x_new, y_new;
	x_new = this->mainPointToMove.x + (this->leftTopPoint.x - this->mainPointToMove.x)*cos(angle) - (this->leftTopPoint.y - this->mainPointToMove.y)*sin(angle);
	y_new = this->mainPointToMove.y + (this->leftTopPoint.x - this->mainPointToMove.x)*sin(angle) + (this->leftTopPoint.y - this->mainPointToMove.y)*cos(angle);
	this->leftTopPoint.x = x_new;
	this->leftTopPoint.y = y_new;
}
void Triangle::scale(double k)
{
	double x_new, y_new;
	x_new = this->mainPointToMove.x + abs(this->leftTopPoint.x - this->mainPointToMove.x)*k;
	y_new = this->mainPointToMove.y + abs(this->leftTopPoint.y - this->mainPointToMove.y)*k;
	this->leftTopPoint.x = x_new;
	this->leftTopPoint.y = y_new;
	this->length *= k;
}