#pragma once
#include "stdafx.h"
#include "Shape.h"
class Pentagon : public Shape {
private:
	int  Side;
	int Id;
public:
	//static map<Color, std::string>{
	//WHITE, "white"
	//cout<< color_map[Color]
	Pentagon(int, int, int, double, int, string);//
	Pentagon(int);
	
	virtual double const FindProjection() const;
	int GetSide();
	void SetSide(int);
	friend ostream&operator<<(ostream&a, const Pentagon&b) {
		a << "ID of figure: id=" << b.Id << "\n";
		a << "Center of figure: x=" << b.X << "; y=" << b.Y << "\n";
//		a << "÷вет: " << colorMap[b.Color] << "\n";// написать функцию getColor FriendlyName (..name?){ static map[...., string]; return name?}
		a << "Color: " << b.Color << "\n";
		a << "Angle: fi=" << b.Angle << "\n";
		a << "Scale: delta=" << b.Scale << "\n";
		a << "Leight if pentagon: Side of pentagon=" << b.Side*b.Scale << "\n";
		
		return a;
	}
	~Pentagon();
};