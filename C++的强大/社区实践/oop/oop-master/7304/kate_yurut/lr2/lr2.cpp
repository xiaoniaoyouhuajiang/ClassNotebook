// Квадрат, Эллипс, Правильный пятиугольник

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#define PI            3.14159265358979323846

using namespace std;


class Point 
{
	public:
		double x;
		double y;
		Point(double x, double y) : x(x), y(y) {}
};


class Shape 
{
	public:
		Shape(double x, double y) :color("black"), center(x, y), angle(0) {}

		void setColor(string color) // установка цвета
		{
			this->color = color;
		}

		void reLocate(double x, double y) // перемещение в другие координаты (по центру)
		{
			for (auto& i : points) 
			{
				i.x += x - center.x;
				i.y += y - center.y;
			}
			center.x = x;
			center.y = y;
		}

		virtual void zoom(double n)=0;

		void prepare_for_zoom(double& n) // масштабирование каждой точки
		{
			if (n<0) 
			{
				n = abs(n);
			}
			for (auto& i : points) 
			{
				i.x *= n;
				i.y *= n;
			}
		}

		void turn(int angl) // поворот на угол
		{
			angl = angl % 360;
			angle += angl;
			double radian = angl*PI / 180;
			for (auto& i : points) 
			{
				double x_ = i.x*cos(radian) - i.y*sin(radian);
				double y_ = i.y*cos(radian) + i.x*sin(radian);
				i.x = x_;
				i.y = y_;
			}
		}

		virtual void printOUT(ostream& out) = 0; // печать информации о фигуре
 
		friend std::ostream& operator<<(std::ostream& outStream, Shape& shape) 
		{
			shape.printOUT(outStream);
			return outStream;
		}


	protected:
		string color;
		Point center;
		int angle;
		vector<Point> points;
};


class Square : public Shape 
{	
	double side;

	public:
		Square(Point center, double side) : Shape(center.x, center.y), side(side) 
		{
			points.push_back({ center.x - side / 2, center.y + side / 2 });
			points.push_back({ center.x + side / 2, center.y + side / 2 });
			points.push_back({ center.x + side / 2, center.y - side / 2 });
			points.push_back({ center.x - side / 2, center.y - side / 2 });
		}

		void zoom(double n) 
		{
			prepare_for_zoom(n);
			side *= n;
		}

		void printOUT(ostream& out) 
		{
			out << "Создан квадрат" << endl;
			out << "Координаты центра: (" << center.x << ", " << center.y << ")" << endl;
			out << "Длина стороны квадрата: " << side << endl;
			out << "Точки квадрата:" << endl;

			for (const auto& i : points) 
			{
				out << "(" << i.x << ", " << i.y << ")\n";
			}
			out << "Цвет: " << color << endl;
			out << "Угол: " << angle << endl;

		}
};


class Ellipse : public Shape
{
	int radiusX, radiusY;

	public:
		Ellipse(Point center, int radiusX, int radiusY) : Shape(center.x, center.y), radiusX(radiusX), radiusY(radiusY)
		{		
			points.push_back(Point((center.x - radiusX), center.y));
			points.push_back(Point(center.x, (center.y + radiusY)));
			points.push_back(Point((center.x + radiusX), center.y));
			points.push_back(Point(center.x, (center.y - radiusY)));

		//	for(int i=0;i<=360;i++)
        	//		points.insert(points.end(),Point(center.x + radiusX * cos(i*PI/180.0), center.y + radiusY * sin(i*PI/180.0)));
		}

		void zoom(double n) 
		{
			prepare_for_zoom(n);
			radiusX *= n;
			radiusY *= n;
		}

		void printOUT(ostream& out) 
		{
			out << "Создан эллипс" << endl;
			out << "Координаты центра: (" << center.x << ", " << center.y << ")" << endl;
			out << "Длины радиусов: " << radiusX << " , "<< radiusY<< endl;
			out << "Точки эллипса:" << endl;

			for (const auto& i : points) 
			{
				out << "(" << i.x << ", " << i.y << ")\n";
			}
			out << "Цвет: " << color << endl;
			out << "Угол: " << angle << endl;

		}
};


class Pentagon : public Shape 
{
	double side;

	public:
		Pentagon(Point center, double side) : Shape(center.x, center.y), side(side) 
		{
			double R = (sqrt(10)*sqrt(5+sqrt(5))/10)*side;
			points.push_back({ center.x, center.y + R });
			points.push_back({ center.x - sin(72*PI/180.0)*R, center.y + cos(72*PI/180.0)*R });
			points.push_back({ center.x + sin(72*PI/180.0)*R, center.y + cos(72*PI/180.0)*R });
			points.push_back({ center.x - sin(36*PI/180.0)*R, center.y - cos(36*PI/180.0)*R });
			points.push_back({ center.x + sin(36*PI/180.0)*R, center.y - cos(36*PI/180.0)*R });
		}

		void zoom(double n) 
		{
			prepare_for_zoom(n);
			side *= n;
		}

		void printOUT(ostream& out) 
		{
			out << "Создан правильный пятиугольник" << endl;
			out << "Координаты центра: (" << center.x << ", " << center.y << ")" << endl;
			out << "Длина стороны пятиугольника: " << side << endl;
			out << "Точки пятиугольника:" << endl;

			for (const auto& i : points) 
			{
				out << "(" << i.x << ", " << i.y << ")\n";
			}
			out << "Цвет: " << color << endl;
			out << "Угол: " << angle << endl;

		}
};


int main()
{
	Square sq({ 0,0 }, 2);
	cout << sq << endl;
	cout << "" << endl;
	cout << "after zooming +color" << endl;
	sq.zoom(2);
	sq.setColor("Green");
	cout << sq << endl;
	sq.turn(90);
	cout << "" << endl;

	cout << "after turning" << endl;
	cout << sq << endl;
	cout << "" << endl;

	cout << "after moving" << endl;
	sq.reLocate(3,3);
	cout << sq << endl;
	cout << "/----------------------------------/" << endl;

	
	Ellipse el({ 0,0 }, 4, 2);
	cout << el;
	cout << "" << endl;
	cout << "after zooming +color" << endl;
	el.setColor("Red");
	el.zoom(2);
	cout << el;
	cout << "" << endl;

	cout << "after turning" << endl;
	el.turn(90);
	cout << el << endl;
	cout << "" << endl;

	cout << "after moving" << endl;
	el.reLocate(-2,-2);
	cout << el << endl;
	cout << "-------------------------------------" << endl;


	Pentagon pen({ 0,0 }, 2);
	cout << pen;
	cout << "" << endl;
	cout << "after zooming +color" << endl;
	pen.setColor("White");
	pen.zoom(2);
	cout << pen;
	cout << "" << endl;

	cout << "after turning" << endl;	
	pen.turn(90);
	cout << pen << endl;
	cout << "" << endl;

	cout << "after moving" << endl;
	pen.reLocate(1,1);
	cout << pen;
	cout << "----------------------------------" << endl;
	cout << "/***********************************************/" << endl;

	return 0;
}
