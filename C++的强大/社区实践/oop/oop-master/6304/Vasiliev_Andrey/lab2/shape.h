#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

double roundTo(double chislo)
{
	double result;
	long long iChislo;
	int k = (chislo>=0)?1:-1;
	iChislo = (long long) chislo;
	result=((long long) ((chislo - iChislo)*pow(10,3)+k*0.5))/pow(10,3);
	result += iChislo;
	return result;
}

inline double toRad(double deg)
{
	return deg*M_PI/180;
}

struct Color
{
	Color(int rr,int gg,int bb)
		:r{rr},g{gg},b{bb}
	{
		if(r <0 || r>255||g <0 || g>255||b <0 || b>255)
			throw invalid_argument("invalid color!");
	}

	int r, g, b;

};

ostream& operator<<(ostream& out, Color & p)
{
	out << "(" << p.r << ", " << p.g <<", "<<  p.b<< ")";
	return out;
}

struct Point
{
	Point(double xx, double yy)
		:x{xx},y{yy}{}

	Point& operator+=(const Point& b)
	{
		x+=b.x;
		y+=b.y;
		return *this;
	}

	double x, y;
};

Point operator +(const Point& a, const Point& b)
{
	Point k = a;
	k+=b;
	return k;
}

ostream& operator<<(ostream& out, Point & p)
{
	out << "(" << roundTo(p.x) << ", " << roundTo( p.y) << ")";
	return out;
}

class Shape
{

public:
	Shape(double w, double h, Color col = Color(255,255,255))
		:angle(0),color(col), width(w),height(h)
	{
		if(width <=0 || height<=0)
			throw invalid_argument("negative width is forbidden!");
	}

	void setColor(Color col){color = col;}
	void setColor(int r, int g, int b){color = Color(r,g,b);}

	Shape& move(Point m)
	{
		points[0] = m;
		updateCoord();
		return *this;
	}
	Shape& move(double x, double y){ return move(Point(x,y));}

	Shape& rotate(double ang)
	{
		angle+=toRad(ang);
		updateCoord();
		return *this;
	}

	Shape& scale(double sc)
	{
		width *= sc;
		height *= sc;
		updateCoord();
		return *this;
	}

	Color getColor(){return color;}

	virtual void printFigure(ostream & out)=0;

	virtual ~Shape(){}
protected:
	virtual void updateCoord()=0;

	vector<Point> points;
	double angle;
	Color color;
	double width, height;


};

ostream& operator<<(ostream& out, Shape & s)
{
	s.printFigure(out);
	return out;
}


class Square : public Shape
{
public:
	Square(Point BottomLeft,double width,Color col = Color(255,255,255))
		:Shape(width,width,col)
	{
		points.push_back(BottomLeft);
		points.push_back(BottomLeft + Point(width,0));
		points.push_back(BottomLeft + Point(width,width));
		points.push_back(BottomLeft + Point(0,width));
	}

	Square(double x, double y, double w ,Color col = Color(255,255,255))
		:Square(Point(x,y), w,col){}

	void printFigure(ostream& out) override
	{
		out << "This figure is square.\n\tCoordinates are: ";
		for(auto i:points)
			out << i << " ";
		out << "\n\tColor is " <<color <<"\n";

	}

protected:
	void updateCoord() override
	{
		points[1] = points[0] + Point(cos(angle)*width,sin(angle)*width);
		double len = sqrt(2)*width;
		points[2] = points[0] + Point(cos(angle+M_PI/4)*len,sin(angle+M_PI/4)*len);
		points[3] = points[0] + Point(cos(angle+M_PI/2)*width,sin(angle+M_PI/2)*width);
	}
};

class RightTriangle : public Shape
{
public:
	RightTriangle(Point LeftBottom, double w, double h,Color col = Color(255,255,255))
		:Shape(w,h,col)
	{
		points.push_back(LeftBottom);
		points.push_back(LeftBottom + Point(w,0));
		points.push_back(LeftBottom + Point(0,h));
	}
	RightTriangle(double x, double y, double w, double h,Color col = Color(255,255,255))
		:RightTriangle(Point(x,y), w,h,col){}

	void printFigure(ostream & out) override
	{
		out << "This figure is right triangle.\n\tCoordinates are: ";
		for(auto i:points)
			out << i << " ";
		out << "\n\tColor is " <<color<<"\n";
	}

protected:
	void updateCoord() override
	{
		points[1] = points[0] + Point(cos(angle)*width,sin(angle)*width);
		points[2] = points[0] + Point(cos(angle+M_PI/2)*height,sin(angle+M_PI/2)*height);
	}
};

class IsosTriangle : public Shape
{
public:
	IsosTriangle(Point LeftBottom, double w, double h,Color col = Color(255,255,255))
		:Shape(w,h,col)
	{
		points.push_back(LeftBottom);
		points.push_back(LeftBottom + Point(w,0));
		points.push_back(LeftBottom + Point(w/2,h));

	}
	IsosTriangle(double x, double y, double w, double h,Color col = Color(255,255,255))
		:IsosTriangle(Point(x,y), w,h,col){}

	void printFigure(ostream & out) override
	{
		out << "This figure is isosceles triangle.\n\tCoordinates are: ";
		for(auto i:points)
			out << i << " ";
		out << "\n\tColor is " <<color<<"\n";
	}

protected:
	void updateCoord() override
	{
		double edge_len = sqrt(pow(width/2,2) + pow(height,2));
		double add_angle = asin(height/edge_len);
		points[1] = points[0] + Point(cos(angle)*width,sin(angle)*width);
		points[2] = points[0] + Point(cos(angle+add_angle)*edge_len,sin(angle+add_angle)*edge_len);
	}
};

#endif // SHAPE_H
