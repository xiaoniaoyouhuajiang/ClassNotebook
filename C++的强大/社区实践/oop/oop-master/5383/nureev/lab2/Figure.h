#pragma once
#include <string>

using namespace std;

struct Color
{
	unsigned char r, g, b;

	Color(unsigned char _r = 0, unsigned char _g = 0, unsigned char _b = 0) : r(_r), g(_g), b(_b) {}
};
class Figure

{

private:

	double Angle, alpha, num;

protected:
	virtual void print(std::ostream &os) = 0;

	Color m_color;

	static size_t count;

	size_t m_id;

	

public:
	double minDistance = 0;

	// Установить и получить цвет фигуры
	void setColor(const Color color);

	Color getColor() const;


	Figure();

	Figure(double InitX, double InitY,string color);

	double getAngle();

	void setAngle(double alpha);
	
	virtual void scale(double num){}

	virtual void turn(double angle){}

	virtual void sdvig(double num1, double num2){}

	virtual double distance(int x, int y){ return minDistance; }

	friend std::ostream &operator << (std::ostream &os, Figure &f);

	size_t getId() const;

	

};