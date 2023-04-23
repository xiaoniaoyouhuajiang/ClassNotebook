#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#define PI 3.14159265358979323846264338279502884197169399375

using namespace std;

struct Point
{
	double x;
	double y;
};

class Shape 
{
protected:
	Point Center;
	string Colour;
	int Angle;

public:
	virtual void move(double x, double y) = 0;
	virtual void scale(double coef) = 0;
	virtual void turn(int angle) = 0;
	virtual ~Shape(){};
	void chooseOption();
		
	Point getCenter();
	
	void setColour(string colour);
	
	string getColour();
		
	virtual void printInfo(ostream& out) = 0; 
	friend std::ostream& operator<<(std::ostream& outStream, Shape& shape) {
		shape.printInfo(outStream);
		return outStream;
	}
};

class Ellipse :public Shape
{
	double R1;//длина первого радиуса
	double R2;//длина второго радиуса

	public:

		Ellipse(double x0, double y0, double a, double b, string colour);
		~Ellipse() = default;
		void printInfo(ostream& out);
		void move(double x, double y);

		void turn(int angle);
		
	
		void scale(double coeff);

};

class Trapeze: public Shape
{
protected:
	Point RightTop;
	Point RightBottom;
	Point LeftTop;
	Point LeftBottom;
	double dif1;
	double dif2;
	double height;
	double lenght;
	double dia;// = sqrt(pow(halfA,2)+pow(halfB,2));
	double corner;// = atan(((b/2)/(a/2)));//*180/PI);
	
public:
	Trapeze(double a, double b, double h, int ang, string colour);
	void move(double x, double y);
	void turn(int angle);
	void scale(double coeff);
	void printInfo(ostream& out);
	~Trapeze() = default;
};

class IsoscelesTrapeze : public Trapeze 
{
	public:
	IsoscelesTrapeze(double a, double b, double h, string colour); 

	void printInfo(ostream& out);
};