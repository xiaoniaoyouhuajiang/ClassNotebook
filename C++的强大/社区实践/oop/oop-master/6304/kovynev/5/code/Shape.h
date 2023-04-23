#pragma once

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
# define M_PI           3.14159265358979323846

namespace stepik
{
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
			unsigned short height)
		{
			rgbRed = r;
			rgbGreen = g;
			rgbBlue = height;
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

	class Rectangle : public Shape
	{
	protected:
		double width;
		double height;
		double perimeter;
	public:
		Rectangle(const Dot& centerDot, double m_width, double m_height) :
			Shape(4), width(m_width), height(m_height)
		{
			dots[0] = { centerDot.x + width / 2, centerDot.y + height / 2 };
			dots[1] = { centerDot.x + width / 2, centerDot.y - height / 2 };
			dots[2] = { centerDot.x - width / 2, centerDot.y - height / 2 };
			dots[3] = { centerDot.x - width / 2, centerDot.y + height / 2 };
			perimeter = 2 * (width + height);
		}
		void scaling(double factor)
		{
			scalingDots(factor);
			width *= factor;
			height *= factor;
			perimeter *= factor;
		}
		double getSquare()
		{
			return width * height;
		}
		void info(std::ostream& out)
		{
			out << "############################### INFO ###############################\n";
			out << "Rectangle:\n";
			out << "List of points:\n";
			for (const auto& t : dots)
			{
				out << "(" << t.x << "," << t.y << ") ";
			}
			out << "\nColor: (" << color.rgbRed << "," << color.rgbGreen << "," << color.rgbBlue << ")\n";
			out << "Width: " << width << " Height: " << height << "\n";
			out << "Perimeter: " << perimeter << endl;
			out << "####################################################################\n";
		}
	};

	class Circle : public Shape
	{
	protected:
		double radius;
		double length;
	public:
		Circle(Dot centerDot, double r) :
			Shape(1), radius(r)
		{
			dots[0] = centerDot;
			length = 2 * M_PI * radius;
		}
		void scaling(double factor)
		{
			length *= abs(factor);
			radius *= abs(factor);
		}
		double getSquare()
		{
			return M_PI * radius* radius;
		}
		void info(std::ostream& out)
		{
			out << "############################### INFO ###############################\n";
			out << "Circle:\n";
			out << "Center: (" << dots[0].x << "," << dots[0].y << ")\n";
			out << "Color: (" << color.rgbRed << "," << color.rgbGreen << "," << color.rgbBlue << ")\n";
			out << "Radius: " << radius << "\n";
			out << "Length: " << length << endl;
			out << "####################################################################\n";
		}
	};

	class Trapeze : public Shape
	{
	protected:
		double upperside;
		double downside;
		double rightside;
		double leftside;
		double height;

	public:
		Trapeze(Dot dot1, Dot dot2, Dot dot3, Dot dot4)
			: Shape(4)
		{
			dots[0] = dot1;
			dots[1] = dot2;
			dots[2] = dot3;
			dots[3] = dot4;

			upperside = sqrt((dot1.x - dot2.x)*(dot1.x - dot2.x) + (dot1.y - dot2.y)*(dot1.y - dot2.y));
			rightside = sqrt((dot2.x - dot3.x)*(dot2.x - dot3.x) + (dot2.y - dot3.y)*(dot2.y - dot3.y));
			downside = sqrt((dot3.x - dot4.x)*(dot3.x - dot4.x) + (dot3.y - dot4.y)*(dot3.y - dot4.y));
			leftside = sqrt((dot4.x - dot1.x)*(dot4.x - dot1.x) + (dot4.y - dot1.y)*(dot4.y - dot1.y));

			double temp = ((downside - upperside)*(downside - upperside) +
				leftside * leftside - rightside * rightside) / (2 * (downside - upperside));
			height = sqrt(leftside*leftside - temp * temp);
		}
		void scaling(double factor)
		{
			scalingDots(factor);
			upperside *= factor;
			downside *= factor;
			rightside *= factor;
			leftside *= factor;
			height *= factor;
		}
		double getSquare()
		{
			return (upperside + downside) * height / 2.0;
		}
		void info(std::ostream& out)
		{
			out << "############################### INFO ###############################\n";
			out << "Trapeze:\n";
			out << "List of points:\n";
			for (const auto& t : dots)
			{
				out << "(" << t.x << "," << t.y << ") ";
			}
			out << "\nColor: (" << color.rgbRed << "," << color.rgbGreen << "," << color.rgbBlue << ")\n";
			out << "Upperside: " << upperside << " Downside: " << downside << "\n";
			out << "Rightside: " << rightside << " Leftside: " << leftside << "\n";
			out << "Height: " << height << endl;
			out << "####################################################################\n";
		}

	};
}
