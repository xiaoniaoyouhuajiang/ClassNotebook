#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;
# define M_PI         3.14159265358979323846

struct Dot 
{
	double x; 
	double y;
};

struct Color 
{
	unsigned short rgbRed; 
	unsigned short rgbGreen;
	unsigned short rgbBlue;
	Color(unsigned short r, unsigned short g,
		unsigned short b) 
	{
		rgbRed = r; 
		rgbGreen = g;
		rgbBlue = b;
	}
};

class Shape 
{
protected: 
	Color color; 
	int angle; 
	vector<Dot> dots;
public:
	Shape(int dotsSize) : 
		color(0, 0, 0), angle(0)  
	{
		dots.resize(dotsSize);
	}

	void changeColor(Color m_color)  
	{
		color = m_color;
	}
	Color getColor() const 
	{
		return color;
	}
	void rotateFigure(int deg) 
	{
		angle += deg; 
		angle %= 360;  
		double rad = angle * M_PI / 180;
		for (auto& current_dot : dots) 
									   
		{
			double tmpx = current_dot.x*cos(rad) - current_dot.y*sin(rad);
			double tmpy = current_dot.y*cos(rad) + current_dot.x*sin(rad);
			current_dot.x = tmpx;
			current_dot.y = tmpy;
		}
	}
	void changePosition(double x, double y) 
	{
		for (auto& current_dot : dots)
		{
			current_dot.x += x; 
			current_dot.y += y;
		}
	}

	virtual double getSquare() = 0; 
	virtual void scaling(double factor) = 0; 
	virtual void info(std::ostream& out) = 0;
	virtual ~Shape() {} 

protected:
	friend ostream& operator<<(ostream& out, Shape& shape) 
	{
		shape.info(out); 
		return out;
	}

	void scalingDots(double& factor)  
	{
		factor = fabs(factor); 
		for (auto& current_dot : dots)
		{
			current_dot.x *= factor; 
			current_dot.y *= factor;
		}
	}
};

class Triangle : public Shape 
{
protected:
	double a;
	double b;
	double c;
public:
	Triangle(Dot d1, Dot d2, Dot d3) : 
		Shape(3)  
	{
		dots[0] = d1; 
		dots[1] = d2;
		dots[2] = d3;

		a = sqrt((d1.x - d2.x)*(d1.x - d2.x) + (d1.y - d2.y)*(d1.y - d2.y)); 
		b = sqrt((d2.x - d3.x)*(d2.x - d3.x) + (d2.y - d3.y)*(d2.y - d3.y));
		c = sqrt((d1.x - d3.x)*(d1.x - d3.x) + (d1.y - d3.y)*(d1.y - d3.y));

	}
	void scaling(double factor)  
	{
		scalingDots(factor);
		a *= factor;
		b *= factor;
		c *= factor;
	}
	double getSquare() 
	{
		double p = (a + b + c) / 2.0;
		return sqrt(p*(p - a)*(p - b)*(p - c));
	}
	void info(std::ostream& out) 
	{
		out << "Information\n";
		out << "Triagle:\n";
		out << "List of points:\n";
		for (const auto& t : dots)
		{
			out << "(" << t.x << "," << t.y << ") ";
		}
		out << "\nColor: (" << color.rgbRed << "," << color.rgbGreen << "," << color.rgbBlue << ")\n";
		out << "A: " << a << " B: " << b << " C: " << c << "\n\n\n";

	}
};

class Parallelogram : public Shape
{
protected:
	double a;
	double b;
	double alpha;

public:
	Parallelogram(Dot centre, double a, double b, double alpha) : 
		Shape(4), a(a), b(b), alpha(alpha) 
	{
		double rad = alpha * M_PI / 180; 
		double h = a * sin(rad); 

		dots[0] = { centre.x - b / 2 - h / (2 * tan(rad)), centre.y - h / 2 }; 
		dots[1] = { centre.x - b / 2 + h / (2 * tan(rad)), centre.y + h / 2 };
		dots[2] = { centre.x + b / 2 + h / (2 * tan(rad)), dots[1].y };
		dots[3] = { centre.x + b / 2 - h / (2 * tan(rad)), dots[0].y };

	}
	void scaling(double factor)
	{
		scalingDots(factor);
		a *= factor;
		b *= factor;
	}
	double getSquare()
	{
		return a * b*sin(alpha * M_PI / 180); 
	}
	void info(std::ostream& out)
	{
		out << "Information\n";
		out << "Parallelogram:\n";
		out << "List of points:\n";
		for (const auto& t : dots)
		{
			out << "(" << t.x << "," << t.y << ") ";
		}
		out << "\nColor: (" << color.rgbRed << "," << color.rgbGreen << "," << color.rgbBlue << ")\n";
		out << "A: " << a << " B: " << b << "\n";
		out << "Angle: " << alpha << endl << endl << endl;
	}
};

class Romb : public Parallelogram 
{
public:
	Romb(Dot centre, double a, double alpha) :
		Parallelogram(centre, a, a, alpha) {};
	double getSquare()
	{
		return a * a*sin(alpha * M_PI / 180); 
	}
	void info(std::ostream& out)
	{
		out << "Information\n";
		out << "Romb:\n";
		out << "List of points:\n";
		for (const auto& t : dots)
		{
			out << "(" << t.x << "," << t.y << ") ";
		}
		out << "\nColor: (" << color.rgbRed << "," << color.rgbGreen << "," << color.rgbBlue << ")\n";
		out << "A: " << a << "\n";
		out << "Angle: " << alpha << endl << endl << endl;
	}
};
int main()
{
	Color Red(255, 0, 0);
	Color Green(0, 255, 0);

	Triangle a({0,0}, {10,0}, {5,5}); 
	cout << a; 
	a.scaling(2); 
	a.changePosition(1, 1); 
	a.rotateFigure(13);  
	cout << a;

	a.changeColor(Red);

	Romb b({ 0,0 }, 10, 180);
	cout << b; 

	b.scaling(6);

	cout << b;
	Dot dotcentrePar = {0,5};
	//dotcentrePar.x = 0;
	//dotcentrePar.y = 5;
	Parallelogram s(dotcentrePar, 8, 6, 30);
	cout << s;
	s.changePosition(1, 1);
	cout << s;

	return 0;
}

