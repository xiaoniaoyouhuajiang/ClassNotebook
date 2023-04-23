#pragma once
#include <iostream>
#include <string>

class Shape{
protected:
	double X0;
	double Y0;//координаты центра
	std::string Colour; //цвет
	int number; //номер фигуры
	double Angle; //угол поворота в градусах
public:
	static int Number; //счётчик
	Shape();
	~Shape();
	void movement(double, double); //перемещение
	void rotation(double); //вращение
	virtual void scaling(double) = 0; //масштабирование 
	void setColour(std::string); //установка цвета
	std::string getColour() const; //получение цвета
	virtual double square() = 0;
	virtual void print(std::ostream &) const = 0;
	friend std::ostream &operator << (std::ostream &, const Shape &);
};