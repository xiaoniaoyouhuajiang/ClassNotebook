#pragma once
#include "stdafx.h"
#include <iostream>
#include "string"
#include "math.h"
#include <map>

using namespace std;

//enum ProjectionType { X = 0, Y = 1 };
/*enum color_type { red, orange, yellow, green, blue, violet, white, black };

static map <color_type, char*> map_of_colour = {
	{ red, "Red" },
	{ orange, "Orange" },
	{ yellow, "Yellow" },
	{ green, "Green" },
	{ blue, "Blue" },
	{ violet, "Violet" },
	{ white, "White" },
	{ black, "Black" }
};*/

class Shape {
protected:
	//my_color color;
	//color_type color = white;
	static  int ID;
	int X = 0, Y = 0;
	int Angle = 0; 
	double Scale = 1; 
	string Color = "Белый";
	/*struct Colorr {
		unsigned r, g, b;//color(255, 0, 255)
	};*/
public:
	
	Shape() {
		std::cout << "Shape created" << std::endl;
	};
	bool equalProjection(const Shape& other) const//, const ProjectionType projection
	{
		double Pr1 = this->FindProjection();
		double Pr2 = other.FindProjection();
		if (Pr1 == Pr2) return true;
		else return false;
	}
	virtual double const FindProjection() const =0;
	virtual ~Shape();
	virtual void MoveFigure(int, int); 
	virtual void TurnFigure(int) ; 
	virtual void ScaleFigure(double) ; 
	
	virtual string GetColorFigure() ; 
	virtual void SetColorFigure(string) ; 

	friend ostream&operator<<(ostream&, const Shape&); //stream
};