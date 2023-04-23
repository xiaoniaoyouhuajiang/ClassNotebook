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
		if(p1.x == p2.x && p1.y == p2.y)
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
protected:
	static int ID;
	Point leftTopPoint;	
	Point mainPointToMove;
	myColor color;

public:
	Shape(){}
	virtual void moveTo(Point const & newCenter) =  0;	//перемещение
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
	virtual ostream &operator << (ostream &output)
	{
		return output;
	};	//оператор вывода в поток

	friend bool operator== (const Shape& p1, const Shape& p2)
	{
		if(p1.leftTopPoint == p2.leftTopPoint &&  p1.mainPointToMove == p2.mainPointToMove)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	friend bool isUnionOf(const Shape & first, const Shape & second)
	{
		Point firstPoint1, secondPoint1, thirdPoint1, fourthPoint1, diff, firstPoint2, secondPoint2, thirdPoint2, fourthPoint2;
		int bad_numb = INT_MIN;
		int equal = strcmp(typeid(first).name(),"class Square");
		int equal2;
		if(equal == 0)
		{
			diff.x = abs(first.mainPointToMove.x - first.leftTopPoint.x);
			diff.y = abs(first.mainPointToMove.y - first.leftTopPoint.y);
			firstPoint1.x = first.mainPointToMove.x + diff.x;
			firstPoint1.y = first.mainPointToMove.y + diff.y;
			secondPoint1.x = first.mainPointToMove.x - diff.x;
			secondPoint1.y = first.mainPointToMove.x - diff.x;
			thirdPoint1.x = first.mainPointToMove.x + diff.y;
			thirdPoint1.y = first.mainPointToMove.x - diff.x;
			fourthPoint1.x = first.mainPointToMove.x - diff.y;
			fourthPoint1.y = first.mainPointToMove.x + diff.x;
		}
		else
		{
			equal = strcmp(typeid(first).name(),"class sqTriangle");
			int equal2 = strcmp(typeid(first).name(),"class isosTriangle");
			if(equal == 0 || equal2 == 0)
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
		equal = strcmp(typeid(second).name(),"class Square");
		if(equal == 0)
		{
			diff.x = abs(first.mainPointToMove.x - second.leftTopPoint.x);
			diff.y = abs(first.mainPointToMove.y - second.leftTopPoint.y);
			firstPoint2.x = second.mainPointToMove.x + diff.x;
			firstPoint2.y = second.mainPointToMove.y + diff.y;
			secondPoint2.x = second.mainPointToMove.x - diff.x;
			secondPoint2.y = second.mainPointToMove.x - diff.x;
			thirdPoint2.x = second.mainPointToMove.x + diff.y;
			thirdPoint2.y = second.mainPointToMove.x + diff.x;
			fourthPoint2.x = second.mainPointToMove.x - diff.y;
			fourthPoint2.y = second.mainPointToMove.x - diff.x;
		}
		else
		{
			equal = strcmp(typeid(second).name(),"class sqTriangle");
			equal2 = strcmp(typeid(second).name(),"class isosTriangle");
			if(equal == 0 || equal2 == 0)
			{
				firstPoint2 = second.mainPointToMove;
				secondPoint2 = second.leftTopPoint;
				thirdPoint2.x = bad_numb;
				thirdPoint2.y = bad_numb;
				fourthPoint2.x = bad_numb;
				fourthPoint2.y = bad_numb;
			}
		}
		
		if(firstPoint1 == firstPoint2 || firstPoint1 == secondPoint2 || firstPoint1 == thirdPoint2 || firstPoint1 == fourthPoint2 || 
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
		//Point firstPoint1, secondPoint1, thirdPoint1, fourthPoint1, diff, firstPoint2, secondPoint2, thirdPoint2, fourthPoint2;
		//diff.x = abs(first.mainPointToMove.x - first.leftTopPoint.x);
		//diff.y = abs(first.mainPointToMove.y - first.leftTopPoint.y);
		//if(typeid(first).name() == "Square")
		//{
		//	firstPoint1.x = first.mainPointToMove.x + diff.x;
		//	firstPoint1.y = first.mainPointToMove.y + diff.y;
		//	secondPoint1.x = first.mainPointToMove.x - diff.x;
		//	secondPoint1.y = first.mainPointToMove.x - diff.x;
		//	thirdPoint1.x = first.mainPointToMove.x + diff.y;
		//	thirdPoint1.y = first.mainPointToMove.x + diff.x;
		//	fourthPoint1.x = first.mainPointToMove.x - diff.y;
		//	fourthPoint1.y = first.mainPointToMove.x - diff.x;
		//}
		//if(typeid(second).name() == "Square")
		//{
		//	firstPoint2.x = second.mainPointToMove.x + diff.x;
		//	firstPoint2.y = second.mainPointToMove.y + diff.y;
		//	secondPoint2.x = second.mainPointToMove.x - diff.x;
		//	secondPoint2.y = second.mainPointToMove.x - diff.x;
		//	thirdPoint2.x = second.mainPointToMove.x + diff.y;
		//	thirdPoint2.y = second.mainPointToMove.x + diff.x;
		//	fourthPoint2.x = second.mainPointToMove.x - diff.y;
		//	fourthPoint2.y = second.mainPointToMove.x - diff.x;
		//}
		//if(firstPoint1 == firstPoint2 && secondPoint1 == secondPoint2 && thirdPoint1 == thirdPoint2)
		//if(typeid(first) == typeid(sqTriangle) || typeid(second).name() == "sqTriangle")
		//{
		//	sqTriangle curr = typeid(first);//записать first сюда
		//	x_new = 0;
		//	y_new = curr.length;
		//	//двигаем нашу точку
		//	x_new -= curr.mainPointToMove.x;
		//	y_new -= curr.mainPointToMove,y;
		//	//ищем угол на который будем поворачивать
		//	alpha=tg((curr.mainPointToMove.y - first.curr.y)/(curr.mainPointToMove.x - curr.leftTopPoint.x));
		//	//вращаем точку на угол альфа
		//	double x_new, y_new;
		//	x_new = this->mainPointToMove.x + (x_new - this->mainPointToMove.x)*cos(angle) - (y_new - this->mainPointToMove.y)*sin(alpha);
		//	y_new = this->mainPointToMove.y + (x_new - this->mainPointToMove.x)*sin(angle) + (y_new - this->mainPointToMove.y)*cos(alpha);
		//	Point findSqTrPoint(Point p1, Point p2, double h) 
		//	{ 
		//		Point p3; 
		//		double a, b, a1, b1, alpha, betta; 
		//		a1 = p1.y - p2.y; 
		//		b1 = p2.y - p2.y; 
		//		betta = atan(a1 / b1); 
		//		alpha = 3.1415 / 2 - betta; 
		//		a = h*sin(alpha); 
		//		b = h*cos(alpha); 
		//		p3.x = p1.x + a; 
		//		p3.y = p1.y + b; 
		//		return p3; 
		//	} 
		//}
		//return true;
	/*}
	Point findIsOsTrPoint(Point p1, Point p2, double h) 
	{ 
		Point p3, pTmp; 
		pTmp.x = (p1.x - p2.x) / 2 + p1.x; 
		pTmp.y = (p1.y - p2.y) / 2 + p1.y; 
		p3 = findTrSqPoint(pTmp, p2, h); 
		return p3; 
	} 
	void findSquarePoint(Point v1, Point center, Point &v2, Point &v3, Point &v4) 
	{ 
		double h; 
		v3.x = center.x + (center.x - v1.x); 
		v3.y = center.y + (center.y - v1.y); 
		h = 0.5*sqrt((v3.x - v1.x)*(v3.x - v1.x) + (v3.y - v1.y)*(v3.y - v1.y)); 
		v2 = findTrIsOsPoint(v1, v3, h); 
		v4 = findTrIsOsPoint(v1, v3, -h); 
	}
*/
};

class Square : public Shape	//квадрат, точка mainPointToMove - центр квадрата, leftTopPoint - верхняя левая вершина квадрата
{
public:
	Square(Point & mainPointToMove, Point  & leftTopPoint); 
	void moveTo(Point const & newCenter);
	void rotate(double angle);
	void scale(double k);
	friend ostream &operator << (ostream &output, const Square &b) 
	{
	//	myColor tmpColor = b.getColor();
		output << "Square number " << b.ID << endl;
		output << "Color: " << "red component = " << b.color.r << ", green component = " << b.color.g << ", blue component = " << b.color.b << " " << endl;
		output << "Center-point {" << b.mainPointToMove.x << " ; " << b.mainPointToMove.y << "}" << endl;
		output << "Second-point {" << b.leftTopPoint.x << " ; " << b.leftTopPoint.y <<"}" <<  endl;
		return output ;
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
	sqTriangle(Point const & mainPointToMove, Point const & leftTopPoint, double length) : Triangle(mainPointToMove, leftTopPoint, length){}
	ostream &operator << (ostream &output)
	{
		myColor tmpColor = getColor();
		output << "SqTriangle number " << ID << endl;
		output << "Color: " << "red component = " << tmpColor.r << ", green component = " << tmpColor.g << ", blue component = " << tmpColor.b << " " << endl;
		output << "First-point {" << this->mainPointToMove.x << " ; " << this->mainPointToMove.y << "}" << endl;
		output << "Second-point {" << this->leftTopPoint.x << " ; " << this->leftTopPoint.y <<"}" <<  endl;
		output << "Length of second catheter " << this->length << endl;
		return output;
	}
};

class isosTriangle : public Triangle	//равнобедренный треугольник, точка mainPointToMove - правая вершина напротив одной из равных сторон, leftTopPoint - левая вершина, length - высота, проведенная из 3 точки
{
public:
	isosTriangle(Point const & mainPointToMove, Point const & leftTopPoint, double length) : Triangle(mainPointToMove, leftTopPoint, length){}
	ostream &operator << (ostream &output)
	{
		myColor tmpColor = getColor();
		output << "isosTriangle number " << ID << endl;
		output << "Color: " << "red component = " << tmpColor.r << ", green component = " << tmpColor.g << ", blue component = " << tmpColor.b << " " << endl;
		output << "First-point {" << this->mainPointToMove.x << " ; " << this->mainPointToMove.y << "}" << endl;
		output << "Second-point {" << this->leftTopPoint.x << " ; " << this->leftTopPoint.y <<"}" <<  endl;
		output << "Length of second catheter " << this->length << endl;
		return output;
	}
};