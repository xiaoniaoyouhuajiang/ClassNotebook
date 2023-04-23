
#include <iostream>
#include <vector>
#include <locale>
#define PI            3.14159265358979323846
using namespace std;

class Point
{

	double x;
	double y;
public:
	Point()
	{
		this->x = 0;
		this->y = 0;
	}

	Point(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	double getX()
	{
		return x;
	}
	double getY()
	{
		return y;
	}
	void setX(double x)
	{
		this->x = x;
	}
	void setY(double y)
	{
		this->y = y;
	}
};

class Shape
{
protected:
	Point center;
	int angle;
	string color = "black";
	vector<Point> points;
public:
	Shape(Point center)
	{
		this->center = center;
		this->angle = 0;
		this->color = "black";
	}

	void move(Point newCenter)
	{
		double changeX = newCenter.getX() - center.getX(), changeY = newCenter.getY() - center.getY();
		for (int i = 0; i < points.size(); i++)
		{
			points[i].setX(points[i].getX() + changeX);
			points[i].setY(points[i].getY() + changeY);
		}
	}
	void turn(int angle)
	{
		this->angle += angle%360;
		double angleRad = angle*PI / 180;
		for (int i = 0; i < points.size(); i++)
		{
			double newX = points[i].getX()*cos(angleRad) - points[i].getY()*sin(angleRad);
			double newY = points[i].getX()*sin(angleRad) + points[i].getY()*cos(angleRad);
			points[i].setX(newX);
			points[i].setY(newY);
		}
	}
	void zoom(int k)
	{
		if (k<0) {
			k = abs(k);
		}
		center.setX(center.getX() * k);
		center.setY(center.getY() * k);
		for (auto& i : points) {
			i.setX(i.getX() * k);
			i.setY(i.getY() * k);
		}
	}

	void setColor(string color) {
		this->color = color;
	}
	string getColor()
	{
		return color;
	}
	virtual void printOUT(ostream& out) = 0;
	friend std::ostream& operator<<(std::ostream& outStream, Shape& shape) {
		shape.printOUT(outStream);
		return outStream;
	}

};
class Square : public Shape
{
	double side;
public:
	Square(Point center, double side) : Shape(center)
	{
		this->side = side;
		points.push_back(Point((center.getX()-side/2), (center.getY()-side/2)));
		points.push_back(Point((center.getX() - side / 2), (center.getY() + side / 2)));
		points.push_back(Point((center.getX() + side / 2), (center.getY() + side / 2)));
		points.push_back(Point((center.getX() + side / 2), (center.getY() - side / 2)));
	}


	void scale(int k)
	{
		side *= k;
		zoom(k);
	}

	void printOUT(ostream& out) {
		out << "Квадрат!" << endl;
		out << "Координаты центра: (" << center.getX() << ", " << center.getY() << ")" << endl;
		out << "Длина стороны квадрата: " << side << endl;
		out << "Точки квадрата:" << endl;
		for (int i = 0; i < points.size(); i++)
		{
			out << "(" << points[i].getX() << ", " << points[i].getY() << ")\n";
		}
		out << "Цвет: " << color << endl;
		out << "Угол: " << angle << endl;

	}
};

class isoscelesTriangle : public Shape
{
	double side;
	double side2;
	int angleOfTriangle;
public:
	isoscelesTriangle (Point center, double side, int angle) : Shape(center)
	{
		this->side = side;
		this->angleOfTriangle = angle;
		side2 = 2 * side*(1 - cos(angle*PI / 180));
		double r = side2*sin((180 - angle) / 2)*sin((180 - angle) / 2) / cos(angle / 2);
		double h = sqrt(side*side - side2*side2 / 4);
		points.push_back(Point((center.getX() - side2 / 2), (center.getY() - r)));
		points.push_back(Point((center.getX()), (center.getY() + h - r)));
		points.push_back(Point((center.getX() + side2/2), (center.getY() - r)));
	}

	void scale(int k)
	{

		side *= k;
		side2 *= k;
		zoom(k);
	}
	void printOUT(ostream& out) {
		out << "Равнобедренный треугольник!" << endl;
		out << "Координаты центра: (" << center.getX() << ", " << center.getY() << ")" << endl;
		out << "Длина сторон равнобедренного треугольника: " << side << " "<< side2 << endl;
		out << "Угол равнобедренного треугольника: " <<angleOfTriangle << endl;
		out << "Точки равнобедренного треугольника:" << endl;
		for (int i = 0; i < points.size(); i++)
		{
			out << "(" << points[i].getX() << ", " << points[i].getY() << ")\n";
		}
		out << "Цвет: " << color << endl;
		out << "Угол: " << angle << endl;

	}
};
class rectangularTriangle : public Shape
{
	double side;
	double side2;
public:
	rectangularTriangle(Point center, double side, double side2) : Shape(center)
	{
		this->side = side;
		this->side2 = side2;
		double side3 = sqrt(side*side + side2*side2);
		double r = (side+side2-side3)/2;
		points.push_back(Point((center.getX() - r), (center.getY() - r)));
		points.push_back(Point((center.getX() - r), (center.getY() + side - r)));
		points.push_back(Point((center.getX() - r + side2), (center.getY() - r)));
	}
	void scale(int k)
	{
		side *= k;
		side2*= k;
		zoom(k);
	}
	void printOUT(ostream& out) {
		out << "Прямоугольный треугольник!" << endl;
		out << "Координаты центра: (" << center.getX() << ", " << center.getY() << ")" << endl;
		out << "Длина сторон прямоугольного треугольника: " << side << " " << side2 << endl;
		out << "Точки прямоугольного треугольника:" << endl;
		for (int i = 0; i < points.size(); i++)
		{
			out << "(" << points[i].getX() << ", " << points[i].getY() << ")\n";
		}
		out << "Цвет: " << color << endl;
		out << "Угол: " << angle << endl;
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Создаем квадрат" << endl;
	Square shape1({ 0, 0 }, 5);
	cout << shape1<< endl;
	cout << "Увеличим квадрат в 4 раза" << endl;
	shape1.scale(4);
	cout << shape1<<endl;
	cout << "Повернем квадрат на 90*" << endl;
	shape1.turn(90);
	cout << shape1<<endl;
	cout << "Установим цвет квадрата как 'Green'" << endl;
	shape1.setColor("Green");
	cout << shape1<<endl;

	cout << "Создаем равнобедренный треугольник" << endl;
	isoscelesTriangle shape2({ 0,0 }, 4, 60);
	cout << shape2<<endl;
	cout << "Увеличим равнобедренный треугольник в 16 раза" << endl;
	shape2.scale(16);
	cout << shape2<<endl;
	cout << "Повернем равнобедренный треугольник на 60*" << endl;
	shape2.turn(60);
	cout << shape2 << endl;
	cout << "Установим цвет равнобедренного треугольника как 'White'" << endl;
	shape2.setColor("White");
	cout << shape2 << endl;

	cout << "Создаем прямоугольный треугольник" << endl;
	rectangularTriangle shape3({ 0,0 }, 3, 4);
	cout << shape3 << endl;
	cout << "Увеличим прямоугольный треугольник в 9 раз" << endl;
	shape3.scale(9);
	cout << shape3 << endl;
	cout << "Повернем прямоугольный треугольник на 45*" << endl;
	shape3.turn(45);
	cout << "Установим цвет прямоугольного треугольника как 'White'" << endl;
	shape3.setColor("Blue");
	cout << shape3 << endl;


    return 0;
}

