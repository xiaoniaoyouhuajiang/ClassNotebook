#include <string>
using namespace std;
#pragma once
class Shape
{
protected:
	double angle = 0;
	virtual void print(ostream& output) = 0;
public:
//	friend ostream& operator«(ostream& output, Shape& p);
	double area;
	virtual void ShowFigure() = 0; //Ïîêàçàòü
	virtual void Move(double x, double y) = 0;
	virtual void ChangeScale(int n) = 0;
	virtual void ChangeColor(string color) = 0;
	virtual void ChangeAngle(double a) = 0;
	//~Shape();
	//template <typename T, typename U>
	//double compareAreas(T figure1, U figure2, bool var);
	
	double static compareAreas(const Shape& figure1, const Shape& figure2)
	{
		if (figure1.area == figure2.area)
			return 3;
		if (figure1.area < figure2.area)
			return 2;
		if (figure1.area > figure2.area)
			return 1;
		return 0;
	}

};
