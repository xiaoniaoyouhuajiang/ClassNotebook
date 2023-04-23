#include "rectangle.h"
#include <iostream>
#include <math.h>

Rectangle::Rectangle(int width_r, int height_r)

{
	
	width = width_r;

	height = height_r;

	Center = Point(0, 0);

	A = Point(-width / 2, height / 2);

	B = Point(width / 2, height / 2);

	C = Point(width / 2, -height / 2);

	D = Point(-width / 2, -height / 2);

}

void Rectangle::set_length(double w, double h)

{

	width = w;

	height = h;

	Center = Point(0, 0);

	A = Point(-width / 2, height / 2);

	B = Point(width / 2, height / 2);

	C = Point(width / 2, -height / 2);

	D = Point(-width / 2, -height / 2);

	double angle = getAngle();

	turn(angle);

}

double Rectangle::getWidth()

{

	return width;

}

double Rectangle::getHeight()

{

	return height;

}

void Rectangle::scale(double num)

{
	/*A = Point(A.getX*num, A.getY*num);

	B = Point(B.getX*num, B.getY*num);

	C = Point(C.getX*num, C.getY*num);

	D = Point(D.getX*num, D.getY*num);*/

	set_length(getWidth()*num, getHeight()*num);

}

void Rectangle::turn(double angle)

{

	double temp_x1 = A.getX();

	double temp_y1 = A.getY();

	double temp_x2 = B.getX();

	double temp_y2 = B.getY();

	double temp_x3 = C.getX();

	double temp_y3 = C.getY();

	double temp_x4 = D.getX();

	double temp_y4 = D.getY();

	A.setX((temp_x1 - Center.getX())*cos(angle) - (temp_y1 - Center.getY())*sin(angle) + Center.getX());

	if (A.getX() > -0.001 && A.getX() < 0.001) A.setX(0);

	A.setY((temp_x1 - Center.getX())*sin(angle) + (temp_y1 - Center.getY())*cos(angle) + Center.getY());

	if (A.getY() > -0.001 && A.getY() < 0.001) A.setY(0);

	B.setX((temp_x2 - Center.getX())*cos(angle) - (temp_y2 - Center.getY())*sin(angle) + Center.getX());

	if (B.getX() > -0.001 && B.getX() < 0.001) B.setX(0);

	B.setY((temp_x2 - Center.getX())*sin(angle) + (temp_y2 - Center.getY())*cos(angle) + Center.getY());

	if (B.getY() > -0.001 && B.getY() < 0.001) B.setY(0);

	C.setX((temp_x3 - Center.getX())*cos(angle) - (temp_y3 - Center.getY())*sin(angle) + Center.getX());

	if (C.getX() > -0.001 && C.getX() < 0.001) C.setX(0);

	C.setY((temp_x3 - Center.getX())*sin(angle) + (temp_y3 - Center.getY())*cos(angle) + Center.getY());

	if (C.getY() > -0.001 && C.getY() < 0.001) C.setY(0);

	D.setX((temp_x4 - Center.getX())*cos(angle) - (temp_y4 - Center.getY())*sin(angle) + Center.getX());

	if (D.getX() > -0.001 && D.getX() < 0.001) D.setX(0);

	D.setY((temp_x4 - Center.getX())*sin(angle) + (temp_y4 - Center.getY())*cos(angle) + Center.getY());

	if (D.getY() > -0.001 && D.getY() < 0.001) D.setY(0);

}
void Rectangle::sdvig(double num1,double num2){
	
	double temp_x1 = A.getX();

	double temp_y1 = A.getY();

	double temp_x2 = B.getX();

	double temp_y2 = B.getY();

	double temp_x3 = C.getX();

	double temp_y3 = C.getY();

	double temp_x4 = D.getX();

	double temp_y4 = D.getY();
	A.setY(temp_y1 + num2);
	B.setY(temp_y2 + num2);
	C.setY(temp_y3 + num2);
	D.setY(temp_y4 + num2);
	A.setX(temp_x1 + num1);
	B.setX(temp_x2 + num1);
	C.setX(temp_x3 + num1);
	D.setX(temp_x4 + num1);
}




double Rectangle::distance(int x, int y){

	double temp_x1 = A.getX();

	double temp_y1 = A.getY();

	double temp_x2 = B.getX();

	double temp_y2 = B.getY();

	double temp_x3 = C.getX();

	double temp_y3 = C.getY();

	double temp_x4 = D.getX();

	double temp_y4 = D.getY();

	double dis1, dis2, dis3, dis4;
	dis1 = sqrt(pow(x - temp_x1, 2) + pow(y - temp_y1, 2));
	dis2 = sqrt(pow(x - temp_x2, 2) + pow(y - temp_y2, 2));
	dis3 = sqrt(pow(x - temp_x3, 2) + pow(y - temp_y3, 2));
	dis4 = sqrt(pow(x - temp_x4, 2) + pow(y - temp_y4, 2));
	double arr[4] = { dis1, dis2, dis3, dis4 };
	double min;

	min = arr[0];

	for (int i = 1; i < 4; ++i)

		if (arr[i] < min) min = arr[i];
	minDistance = min;
	return min;
}


void Rectangle::print(std::ostream &os)

{
	os << "Номер фигуры" << ' ' << Figure::m_id << std::endl;

	os << "Координаты точки A = (" << A.getX() << " , " << A.getY() << ")" << std::endl;

	os << "Координаты точки B = (" << B.getX() << " , " << B.getY() << ")" << std::endl;

	os << "Координаты точки C = (" << C.getX() << " , " << C.getY() << ")" << std::endl;

	os << "Координаты точки D = (" << D.getX() << " , " << D.getY() << ")" << std::endl;

	os <<"расстояние от заданной точки до ближайшей вершины фигуры"<<' '<< Figure::minDistance << std::endl;

	
}