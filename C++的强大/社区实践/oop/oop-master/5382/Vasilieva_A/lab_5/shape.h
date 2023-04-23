#include <iostream>
#include <cmath>
#include <typeinfo.h>
#include <climits>

using namespace std;

struct Point
{
	double x, y;

	Point() : x(0), y(0)
	{}

	Point(double x, double y) : x(x), y(y)
	{}

	friend bool operator== (const Point p1, const Point p2)
	{
		if (p1.x == p2.x && p1.y == p2.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

struct myColor
{
	double r, g, b;

	myColor() : r(0), g(0), b(0)
	{}

	myColor(double r, double g, double b) : r(r), g(g), b(b)
	{}
};

class Shape
{
	static size_t counter;
protected:
	unsigned ID;
	Point leftTopPoint;
	Point mainPointToMove;
	myColor color;

public:
	Shape()
	{
		static size_t counter = 0;
		ID = ++counter;
	}
	virtual ~Shape() {}
	virtual void moveTo(Point const & newCenter) = 0;	//перемещение
	virtual void rotate(double angle) = 0;	//поворот
	virtual void scale(double k) = 0;	//масштабирование
	myColor getColor()	//получение цвета
	{
		return this->color;
	}
	void setColor(myColor color)	//установка цвета
	{
		this->color = color;
	}

	virtual void print(ostream &ost) = 0;

	friend ostream &operator << (ostream &ost, Shape &object);

	friend bool operator== (const Shape& p1, const Shape& p2);

	bool isUnionOf(const Shape & first, const Shape & second)
	{
		Point firstPoint1, secondPoint1, thirdPoint1, fourthPoint1, diff, firstPoint2, secondPoint2, thirdPoint2, fourthPoint2;
		int bad_numb = INT_MIN;
		int equal = strcmp(typeid(first).name(), "class Square");
		int equal2;
		if (equal == 0)
		{
			diff.x = abs(first.mainPointToMove.x - first.leftTopPoint.x);
			diff.y = abs(first.mainPointToMove.y - first.leftTopPoint.y);
			firstPoint2.x = second.mainPointToMove.x + diff.x;
			firstPoint2.y = second.mainPointToMove.y + diff.y;
			secondPoint2.x = second.mainPointToMove.x - diff.x;
			secondPoint2.y = second.mainPointToMove.y - diff.y;
			thirdPoint2.x = second.mainPointToMove.x + diff.x;
			thirdPoint2.y = second.mainPointToMove.y - diff.y;
			fourthPoint2.x = second.mainPointToMove.x - diff.x;
			fourthPoint2.y = second.mainPointToMove.y + diff.y;
		}
		else
		{
			equal = strcmp(typeid(first).name(), "class sqTriangle");
			int equal2 = strcmp(typeid(first).name(), "class isosTriangle");
			if (equal == 0 || equal2 == 0)
			{
				firstPoint1 = first.mainPointToMove;
				secondPoint1 = first.leftTopPoint;
				thirdPoint1.x = bad_numb;
				thirdPoint1.y = bad_numb;
				fourthPoint1.x = bad_numb;
				fourthPoint1.y = bad_numb;
				bad_numb += 1;
			}
		}
		equal = strcmp(typeid(second).name(), "class Square");
		if (equal == 0)
		{
			diff.x = abs(first.mainPointToMove.x - second.leftTopPoint.x);
			diff.y = abs(first.mainPointToMove.y - second.leftTopPoint.y);
			firstPoint2.x = second.mainPointToMove.x + diff.x;
			firstPoint2.y = second.mainPointToMove.y + diff.y;
			secondPoint2.x = second.mainPointToMove.x - diff.x;
			secondPoint2.y = second.mainPointToMove.y - diff.y;
			thirdPoint2.x = second.mainPointToMove.x + diff.x;
			thirdPoint2.y = second.mainPointToMove.y - diff.y;
			fourthPoint2.x = second.mainPointToMove.x - diff.x;
			fourthPoint2.y = second.mainPointToMove.y + diff.y;
		}
		else
		{
			equal = strcmp(typeid(second).name(), "class sqTriangle");
			equal2 = strcmp(typeid(second).name(), "class isosTriangle");
			if (equal == 0 || equal2 == 0)
			{
				firstPoint2 = second.mainPointToMove;
				secondPoint2 = second.leftTopPoint;
				thirdPoint2.x = bad_numb;
				thirdPoint2.y = bad_numb;
				fourthPoint2.x = bad_numb;
				fourthPoint2.y = bad_numb;
			}
		}

		if (firstPoint1 == firstPoint2 || firstPoint1 == secondPoint2 || firstPoint1 == thirdPoint2 || firstPoint1 == fourthPoint2 ||
			secondPoint1 == firstPoint2 || secondPoint1 == secondPoint2 || secondPoint1 == thirdPoint2 || secondPoint1 == fourthPoint2 ||
			thirdPoint1 == firstPoint2 || thirdPoint1 == secondPoint2 || thirdPoint1 == thirdPoint2 || thirdPoint1 == fourthPoint2 ||
			fourthPoint1 == firstPoint2 || fourthPoint1 == secondPoint2 || fourthPoint1 == thirdPoint2 || fourthPoint1 == fourthPoint2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class Square : public Shape	//квадрат, точка mainPointToMove - центр квадрата, leftTopPoint - верхняя левая вершина квадрата
{
public:
	Square(Point & mainPointToMove, Point  & leftTopPoint);
	void moveTo(Point const & newCenter);
	void rotate(double angle);
	void scale(double k);
	void print(ostream &output)
	{
		output << "Square number " << this->ID- 1 << endl;
		output << "Color: " << "red component = " << this->color.r << ", green component = " << this->color.g << ", blue component = " << this->color.b << " " << endl;
		output << "Center-point {" << this->mainPointToMove.x << " ; " << this->mainPointToMove.y << "}" << endl;
		output << "Second-point {" << this->leftTopPoint.x << " ; " << this->leftTopPoint.y << "}" << endl;
	}
};

class Triangle : public Shape
{
protected:
	double length;
public:
	Triangle(Point const & mainPointToMove, Point const & leftTopPoint, double length);
	void moveTo(Point const & newPoint);
	void rotate(double angle);
	void scale(double k);
};

class sqTriangle : public Triangle	//прямоугольный треугольник, точка mainPointToMove - вершина при угле в 90, length - второй катет, leftTopPoint - образует с точкой mainPointToMove первый катет
{
public:
	sqTriangle(Point const & mainPointToMove, Point const & leftTopPoint, double length) : Triangle(mainPointToMove, leftTopPoint, length) {}
	void print(ostream &output)
	{
		myColor tmpColor = getColor();
		output << "SqTriangle number " << ID - 1 << endl;
		output << "Color: " << "red component = " << tmpColor.r << ", green component = " << tmpColor.g << ", blue component = " << tmpColor.b << " " << endl;
		output << "First-point {" << this->mainPointToMove.x << " ; " << this->mainPointToMove.y << "}" << endl;
		output << "Second-point {" << this->leftTopPoint.x << " ; " << this->leftTopPoint.y << "}" << endl;
		output << "Length of second catheter " << this->length << endl;
	}
};

class isosTriangle : public Triangle	//равнобедренный треугольник, точка mainPointToMove - правая вершина напротив одной из равных сторон, leftTopPoint - левая вершина, length - высота, проведенная из 3 точки
{
public:
	isosTriangle(Point const & mainPointToMove, Point const & leftTopPoint, double length) : Triangle(mainPointToMove, leftTopPoint, length) {}
	void print(ostream &output)
	{
		myColor tmpColor = getColor();
		output << "isosTriangle number " << ID - 1 << endl;
		output << "Color: " << "red component = " << tmpColor.r << ", green component = " << tmpColor.g << ", blue component = " << tmpColor.b << " " << endl;
		output << "First-point {" << this->mainPointToMove.x << " ; " << this->mainPointToMove.y << "}" << endl;
		output << "Second-point {" << this->leftTopPoint.x << " ; " << this->leftTopPoint.y << "}" << endl;
		output << "Length of second catheter " << this->length << endl;
	}
};