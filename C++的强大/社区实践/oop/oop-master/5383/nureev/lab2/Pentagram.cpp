#include "Pentagram.h"
#include <iostream>
#include <math.h>

using namespace std;
Pentagram::Pentagram(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5)

{

	//x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0, x3 = 0.0, y3 = 0.0, x4 = 0.0, y4 = 0.0, x5 = 0.0, y5 = 0.0;
	

	if (((x3 - x1) / (x2 - x1) == (y3 - y1) / (y2 - y1)) && ((x4 - x2) / (x3 - x2) == (y4 - y2) / (y3 - y2)) && ((x5 - x3) / (x4 - x3) == (y5 - y3) / (y4 - y3)) && ((x1 - x4) / (x5 - x4) == (y1 - y4) / (y5 - y4)) && ((x2 - x5) / (x1 - x5) == (y2 - y5) / (y1 - y5))){

		A = Point(x1, y1);

		B = Point(x2, y2);

		C = Point(x3, y3);

		D = Point(x4, y4);

		E = Point(x5, y5);
	}
	else 
		throw std::invalid_argument("Заданные точки не задают правильный пятиугольник");
	
}

void Pentagram::set_length(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5)

{
	Center = Point(0, 0);

	A = Point(x1, y1);

	B = Point(x2, y2);

	C = Point(x3, y3);

	D = Point(x4, y4);

	E = Point(x5, y5);
	lenght1 = sqrt(pow(x3 - x1, 2) + pow(y3 - y1, 2));

	lenght2 = sqrt(pow(x5 - x3, 2) + pow(y5 - y3, 2));

	lenght3 = sqrt(pow(x5 - x2, 2) + pow(y5 - y2, 2));

	lenght4 = sqrt(pow(x4 - x2, 2) + pow(y4 - y4, 2));

	lenght5 = sqrt(pow(x4 - x1, 2) + pow(y4 - y1, 2));



}



void Pentagram::scale(double num)

{

	set_length(A.getX()*num, A.getY()*num, B.getX()*num, B.getY()*num, C.getX()*num, C.getY()*num, D.getX()*num, D.getY()*num, E.getX()*num, E.getY()*num);

}

void Pentagram::turn(double angle)

{

	double temp_x1 = A.getX();

	double temp_y1 = A.getY();

	double temp_x2 = B.getX();

	double temp_y2 = B.getY();

	double temp_x3 = C.getX();

	double temp_y3 = C.getY();

	double temp_x4 = D.getX();

	double temp_y4 = D.getY();

	double temp_x5 = E.getX();

	double temp_y5 = E.getY();

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

	E.setX((temp_x5 - Center.getX())*cos(angle) - (temp_y5 - Center.getY())*sin(angle) + Center.getX());

	if (A.getX() > -0.001 && A.getX() < 0.001) A.setX(0);

	E.setY((temp_x5 - Center.getX())*sin(angle) + (temp_y5 - Center.getY())*cos(angle) + Center.getY());

	if (A.getY() > -0.001 && A.getY() < 0.001) A.setY(0);

}
void Pentagram::sdvig(double num1, double num2){

	double temp_x1 = A.getX();

	double temp_y1 = A.getY();

	double temp_x2 = B.getX();

	double temp_y2 = B.getY();

	double temp_x3 = C.getX();

	double temp_y3 = C.getY();

	double temp_x4 = D.getX();

	double temp_y4 = D.getY();

	double temp_x5 = D.getX();

	double temp_y5 = D.getY();

	A.setY(temp_y1 + num2);
	B.setY(temp_y2 + num2);
	C.setY(temp_y3 + num2);
	D.setY(temp_y4 + num2);
	E.setY(temp_y5 + num2);
	A.setX(temp_x1 + num1);
	B.setX(temp_x2 + num1);
	C.setX(temp_x3 + num1);
	D.setX(temp_x4 + num1);
	E.setX(temp_x5 + num1);
}



double Pentagram::distance(int x, int y){

	double temp_x1 = A.getX();

	double temp_y1 = A.getY();

	double temp_x2 = B.getX();

	double temp_y2 = B.getY();

	double temp_x3 = C.getX();

	double temp_y3 = C.getY();

	double temp_x4 = D.getX();

	double temp_y4 = D.getY();

	double temp_x5 = E.getX();

	double temp_y5 = E.getY();

	double dis1, dis2, dis3, dis4,dis5;
	dis1 = sqrt(pow(x - temp_x1, 2) + pow(y - temp_y1, 2));
	dis2 = sqrt(pow(x - temp_x2, 2) + pow(y - temp_y2, 2));
	dis3 = sqrt(pow(x - temp_x3, 2) + pow(y - temp_y3, 2));
	dis4 = sqrt(pow(x - temp_x4, 2) + pow(y - temp_y4, 2));
	dis5 = sqrt(pow(x - temp_x5, 2) + pow(y - temp_y5, 2));
	double arr[5] = { dis1, dis2, dis3, dis4,dis5 };
	double min;

	min = arr[0];

	for (int i = 1; i < 5; ++i)

		if (arr[i] < min) min = arr[i];
	minDistance = min;
	return min;
}
void Pentagram::print(std::ostream &os)

{
	os << "Номер фигуры" << ' ' << Figure::m_id << std::endl;

	os << "Координаты точки A = (" << A.getX() << " , " << A.getY() << ")" << std::endl;

	os << "Координаты точки B = (" << B.getX() << " , " << B.getY() << ")" << std::endl;

	os << "Координаты точки C = (" << C.getX() << " , " << C.getY() << ")" << std::endl;

	os << "Координаты точки D = (" << D.getX() << " , " << D.getY() << ")" << std::endl;

	os << "Координаты точки E = (" << E.getX() << " , " << E.getY() << ")" << std::endl;

	os << "расстояние от заданной точки до ближайшей вершины фигуры"<<' ' << Figure::minDistance << std::endl;




}