#pragma once
#include <iostream>
#include <string>

class Shape
{
protected:
	double X0;
	double Y0;//координаты центра
	std::string Colour;//цветф
	int ID;//идентификационный номер
	double Angle;//угол поворота в градусах
public:
	static int id;
	Shape();
	~Shape();
	void Movement(double, double);//перемещение в указанные координаты
	void Rotation(double);//вращение на заданный угол
	virtual void Scaling(double) = 0;//масштабирование 
	void setColour(std::string);//установка цвета
	void printCentre();
	std::string getColour() const;//получение цвета
	bool compareCentre(Shape*);
	double getX0();
	double getY0();
};