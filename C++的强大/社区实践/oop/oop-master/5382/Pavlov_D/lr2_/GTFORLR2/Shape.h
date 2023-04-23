#pragma once

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
///////////////////////
/// Фигуры
/// Квадрат
/// Прямоугольный треугольник
/// Равнобедренный треуг.
///
///
/// Структура точек.
/////////////////
class Point {
public:
	Point() :x(0.), y(0.)
	{}

	Point(double x, double y) :x(x), y(y)
	{}

	double getX() const
	{
		return x;
	}
	double getY() const
	{
		return y;
	}
	void show() const
	{
		std::cout << x << " " << y << std::endl;
	}
	void change(double cx, double cy)
	{
		x = cx;
		y = cy;
	}

private:
	double x;
	double y;
};

Point operator+ (const Point& left, const Point& right)
{
	return Point(left.getX() + right.getX(), left.getY() + right.getY());
}
Point operator- (const Point& left, const Point& right)
{
	return Point(left.getX() - right.getX(), left.getY() - right.getY());
}

Point operator* (const Point& left, double parametr)
{
	return Point(left.getX() * parametr, left.getY() * parametr);
}
Point operator / (const Point& left, double parametr)
{
	return Point(left.getX() / parametr, left.getY() / parametr);
}
bool operator ==  (const Point& left, const Point& right)
{
	return ((left.getX() == right.getX()) && (left.getY() == right.getY()));
}
bool operator !=  (const Point& left, const Point& right)
{
	return !(left == right);
}
struct line {
	std::vector<double  > xl1;
	std::vector<double  > yl1;
	std::vector<double  > xl2;
	std::vector<double  > yl2;
	std::vector<double  > k;
	std::vector<double  > b;
	std::vector<double  > d;
	int size;
	bool checkPoint(double mx, double my)
	{


		for (int q = 0; q < size; q++) {
			double buffer1 = d[q] * my;
			double buffer2 = k[q] * mx + b[q];
			if (buffer1 == buffer2) {
				double sizeBuffer = sqrt(pow(xl1[q] - xl2[q], 2.0) + pow(yl1[q] - yl2[q], 2.0));
				double sizeBuffer1 = sqrt(pow(mx - xl2[q], 2.0) + pow(my - yl2[q], 2.0));
				double sizeBuffer2 = sqrt(pow(xl1[q] - mx, 2.0) + pow(yl1[q] - my, 2.0));
				if ((sizeBuffer >= sizeBuffer1) && (sizeBuffer >= sizeBuffer2))
					return true;

			}

		}
		return false;
	}

	line() :size(0) {}

	line(std::vector<Point> Array, std::vector<double > inputsize) :size(Array.size())
	{

		bool notSide = false;
		int c = 0;
		for (int q = 0; q<size; ++q)
		{

			for (int j = 1; j<(size - q); ++j)
			{

				double buffer = SizeSide(Array, q, q + j);

				for (int n = 0; n<size; n++) {
					if (buffer == inputsize[n])
						break;
					if ((buffer != inputsize[n]) && (n == size - 1))
						notSide = true;
				}
				if (!notSide) {

					double count1 = (Array[q].getY() - Array[q + j].getY());


					double count2 = (Array[q].getX() - Array[q + j].getX());

					if ((count1 == 0) && (count2 != 0)) {

						k.push_back(0);
						d.push_back(1);

						b.push_back(Array[q].getY());

						xl1.push_back(Array[q].getX());
						yl1.push_back(Array[q].getY());
						xl2.push_back(Array[q + j].getX());
						yl2.push_back(Array[q + j].getY());
						c++;
					}
					if ((count2 == 0) && (count1 != 0)) {

						k.push_back(-1);
						b.push_back(Array[q].getX());
						d.push_back(0);
						xl1.push_back(Array[q].getX());
						yl1.push_back(Array[q].getY());
						xl2.push_back(Array[q + j].getX());
						yl2.push_back(Array[q + j].getY());
						c++;

					}
					if ((count1 != 0) && (count2 != 0))
					{

						double buffer = (double)count1 / count2;

						k.push_back(buffer);
						d.push_back(1);
						buffer = Array[q].getY() - k[c] * Array[q].getX();
						b.push_back(buffer);
						xl1.push_back(Array[q].getX());
						yl1.push_back(Array[q].getY());
						xl2.push_back(Array[q + j].getX());
						yl2.push_back(Array[q + j].getY());
						c++;
					}

				}
				notSide = false;

			}

		}

	}
private:

	double SizeSide(std::vector<Point> array, int pos1, int pos2)
	{
		return sqrt(pow(array[pos1].getX() - array[pos2].getX(), 2.0) + pow(array[pos1].getY() - array[pos2].getY(), 2.0));

	}

};
////////////////
class Shape
{
public:
	Shape() :colour_(0), pointCount_(0), ID_(0) {}

	Shape(std::vector<Point> array)
	{

		if (!checkSame(array))
			throw std::invalid_argument("Shape have Equal points ");

	}
	Shape & operator=(Shape const & other)
	{
		if (this != &other) {

			side = other.side;
			Point_ = other.Point_;
			pointCount_ = other.pointCount_;
			colour_ = other.colour_;
			ID_ = other.ID_;

		}
		return *this;


	}

	virtual  ~Shape() {

	}

	unsigned int getColour() const;//
	void setColour(unsigned int colour); //
	void turn(double angle);  //
	void expand(int size); //
	void replaceShape(double mx, double my);//
	virtual void showShape(std::ostream& os) const = 0;  //
	int getPointCount() const;  //
	int getID() const; //
	int setNextID();//
	friend std::ostream& operator<< (std::ostream& os, Shape& p); //

	virtual void countSides(std::vector<double> & side, std::vector<Point> array) = 0;
	bool similar(const Shape &sh1, const Shape &sh2);
	bool sameShape(const Shape &sh1) const;
	bool sameShape(std::vector<Point> &array) const;
	bool sameShape(std::vector<Point> &array, const Shape &sh1, const Shape &sh2) const;
	bool sameShape(Point point) const {
		return std::find(Point_.begin(), Point_.end(), point) != Point_.end();
	}
	virtual  double area() const = 0;
	bool itSide(double tside)
	{
		for (size_t count = 0; count<pointCount_; ++count) {
			if (tside == side[count])
				return true;
		}
		return false;
	}

	Point findCenter()
	{

		Point center;
		for (size_t i = 0; i<pointCount_; ++i) {
			center = center + Point_[i];
		}
		center = center / pointCount_;
		return center;
		
	}
protected:
	int  colour_;
	size_t pointCount_;
	int ID_;
	static int nextID_;
	std::vector<Point> Point_;


	std::vector<double  > side;


	bool checkSame(std::vector<Point> array);

	bool insidePoint(double ix, double iy, const  Shape &shape) const;
	void cross(line lin1, int pos1, line lin2, int pos2, std::vector<Point> &pointer, const Shape &sh);

};
int Shape::nextID_ = 0;
class Triangle : public Shape
{

public:
	Triangle()
	{

		pointCount_ = 3;
	}

	Triangle(std::vector<Point> array) :Shape(array)
	{
		pointCount_ = 3;
		if (array.size() != pointCount_)
			throw std::invalid_argument("Not enought/Too much points ");

		countSides(side, array);

		Point_ = array;
	}
	
	void showShape(std::ostream &os) const override
	{
		os << "I'm Triangle" << std::endl;
		for (size_t i = 0; i<pointCount_; ++i) {
			os << "POINT " << i + 1 << "(" << Point_[i].getX() << ";" << Point_[i].getY() << ")" << std::endl;
		}
	}
	double area()  const  override {
		double per = 0;
		for (size_t count = 0; count<pointCount_; ++count)
			per += side[count];
		per = per / 2;
		return sqrt(per*(per - side[0])*(per - side[1])*(per - side[2]));


	}

	void countSides(std::vector<double> & side, std::vector<Point> array) override
	{
		side.push_back(sqrt(pow(array[0].getX() - array[1].getX(), 2.0) + pow(array[0].getY() - array[1].getY(), 2.0)));//

		side.push_back(sqrt(pow(array[0].getX() - array[2].getX(), 2.0) + pow(array[0].getY() - array[2].getY(), 2.0)));//

		side.push_back(sqrt(pow(array[1].getX() - array[2].getX(), 2.0) + pow(array[1].getY() - array[2].getY(), 2.0)));//

	}

protected:


};


std::ostream& operator<< (std::ostream& os, Shape& p)
{
	p.showShape(os);
	return os;
}
///////////////////////////////////////

unsigned int Shape::getColour() const
{
	return colour_;
}
////////////////////////////////////

int Shape::getPointCount() const
{
	return pointCount_;
}
////////////////////////////////////
void Shape::setColour(unsigned int colour)
{
	colour_ = colour;
}
///////////////////////////////////


bool Shape::checkSame(std::vector<Point> array) {
	for (size_t q = 0; q<array.size() - 1; ++q) {
		for (size_t k = 1; k<array.size() - q; ++k) {

			if ((array[q].getX() == array[q + k].getX()) && (array[q].getY() == array[q + k].getY())) {
				return false;
			}

		}
	}

	return true;

}

////////////////////////////////////
void Shape::turn(double angle)
{

	Point center = findCenter();
	for (size_t i = 0; i<pointCount_; ++i) {
		double buffer1 = (Point_[i].getX() - center.getX())*cos(angle) - (Point_[i].getY() - center.getY())*sin(angle);
		double buffer2 = (Point_[i].getX() - center.getX())*sin(angle) + (Point_[i].getY() - center.getY())*cos(angle);
		Point_[i].change(buffer1, buffer2);
	}
}
////////////////////////////////////
void Shape::expand(int size)
{
	Point center = findCenter();
	for (size_t i = 0; i<pointCount_; ++i) {
		double buffer1 = (Point_[i].getX() - center.getX())*size + center.getY();
		double buffer2 = (Point_[i].getY() - center.getY())*size + center.getY();
		Point_[i].change(buffer1, buffer2);

	}
	for (size_t count = 0; count<pointCount_; ++count)
		side[count] = side[count] * size;

}

////////////////////////////////////
void Shape::replaceShape(double mx, double my)
{
	for (size_t i = 0; i<pointCount_; ++i) {
		Point_[i].change(Point_[i].getX() + mx, Point_[i].getY() + my);

	}
}
////////////////////////////////////

////////////////////////////////////
int Shape::getID() const
{
	return ID_;
}
////////////////////////////////////
int Shape::setNextID()
{
	nextID_++;
	return nextID_;
}
////////////////////////////////////

bool Shape::similar(const Shape &sh1, const Shape &sh2)
{

	if (sameShape(sh1))
		return true;


	std::vector<Point> NewPoint;
	line lin1(sh1.Point_, sh1.side);
	line lin2(sh2.Point_, sh2.side);

	for (size_t count = 0; count<sh1.pointCount_; count++) {

		if (!insidePoint(sh1.Point_[count].getX(), sh1.Point_[count].getY(), sh2)) {

			Point buffer(sh1.Point_[count].getX(), sh1.Point_[count].getY());
			NewPoint.push_back(buffer);

		}
	}

	if ((NewPoint.size()>pointCount_) || (NewPoint.size() == 0))
		return false;


	for (int count1 = 0; count1<lin1.size; count1++) {
		for (int count2 = 0; count2<lin2.size; count2++) {
			cross(lin1, count1, lin2, count2, NewPoint, sh1);

		}

	}


	if (NewPoint.size()>pointCount_) {
		if (sameShape(NewPoint, sh1, sh2)) {

			return true;
		}
		else
			return false;
	}


	return (sameShape(NewPoint));

}
bool Shape::insidePoint(double ix, double iy, const Shape &shape) const
{

	for (size_t i = 0; i<pointCount_; ++i) {
		if ((shape.Point_[i].getX() == ix) && (shape.Point_[i].getY() == iy))
			return true;
	}
	std::vector<Point> vbuffer = shape.Point_;
	line lin(vbuffer, shape.side);
	if (lin.checkPoint(ix, iy))
		return true;
	double S = 0;

	std::vector<Point> vectorBuffer;
	Point buffer(ix, iy);
	vectorBuffer.push_back(buffer);
	bool test = false;
	for (size_t count1 = 0; count1<shape.pointCount_; ++count1) {
		for (size_t count2 = 1; count2 + count1<shape.pointCount_; ++count2) {
			double tside = (sqrt(pow(shape.Point_[count1].getX() - shape.Point_[count1 + count2].getX(), 2.0) + pow(shape.Point_[count1].getY() - shape.Point_[count2 + count1].getY(), 2.0)));

			for (size_t count = 0; count<shape.pointCount_; ++count) {
				if (tside == shape.side[count])
					test = true;
			}

			if (test) {
				buffer.change(shape.Point_[count1].getX(), shape.Point_[count1].getY());
				vectorBuffer.push_back(buffer);
				buffer.change(shape.Point_[count1 + count2].getX(), shape.Point_[count1 + count2].getY());
				vectorBuffer.push_back(buffer);

				Triangle triangle(vectorBuffer);

				S = S + triangle.area();
				test = false;

				for (int i = vectorBuffer.size(); i != 1; --i) {
					vectorBuffer.pop_back();

				}

			}
		}

	}
	if (S == shape.area())
		return true;
	else
		return false;

}

bool Shape::sameShape(const Shape &sh1) const
{
	if (pointCount_ != sh1.pointCount_)
		return false;
	else
	{
		int count = 0;
		for (size_t i = 0; i<pointCount_; ++i) {
			for (size_t q = 1; q<pointCount_ - i; ++q) {
				if ((sh1.Point_[i].getX() == Point_[q + i].getX()) && (sh1.Point_[i].getY() == Point_[q + i].getY()))
					++count;

			}
		}
		if (count == pointCount_)
			return true;
		else
			return false;
	}
}

bool Shape::sameShape(std::vector<Point> &array) const
{
	if (pointCount_ != array.size())
		return false;
	else {
		int count = 0;
		for (size_t i = 0; i<pointCount_; ++i) {
			for (size_t q = 1; q<pointCount_ - i; ++q) {
				if ((array[i].getX() == Point_[i + q].getX()) && (array[i].getY() == Point_[i + q].getY()))
					++count;
			}
		}
		if (count == pointCount_)
			return true;
		else
			return false;

	}
}

bool Shape::sameShape(std::vector<Point> &array, const Shape &sh1, const Shape &sh2) const
{
	std::vector<Point> TroublePoint;
	int truecount = 0;
	for (size_t i = 0; i<array.size(); i++)
	{
		bool check = false;
		for (size_t q = 0; q<pointCount_; q++) {
			if ((array[i].getX() == Point_[q].getX()) && (array[i].getY() == Point_[q].getY()))
			{
				check = true;
				truecount++;
			}
		}
		if (!check)
		{
			Point buffer(array[i].getX(), array[i].getY());
			TroublePoint.push_back(buffer);


		}
		check = false;
	}
	if (truecount != pointCount_)
		return false;
	int count = 0;
	for (size_t i = 0; i < TroublePoint.size(); i++)
	{

		if ((insidePoint(TroublePoint[i].getX(), TroublePoint[i].getY(), *this)) && (!sameShape(TroublePoint[i]))) {   //!sameShape(TroublePoint[i].getX(), TroublePoint[i].getY())

			return false;
		}

		if (((insidePoint(TroublePoint[i].getX(), TroublePoint[i].getY(), sh1)) || ((insidePoint(TroublePoint[i].getX(), TroublePoint[i].getY(), sh2))))) {
			count++;

		}
		for (size_t q = 0; q < sh1.pointCount_; q++)
			if ((TroublePoint[i].getX() == sh1.Point_[q].getX()) && (TroublePoint[i].getY() == sh1.Point_[q].getY())) {
				count++;

			}


		for (size_t q = 0; q < sh2.pointCount_; q++)
			if ((TroublePoint[i].getX() == sh2.Point_[q].getX()) && (TroublePoint[i].getY() == sh2.Point_[q].getY())) {
				count++;

			}
		if (count == 0)
			return false;
		count = 0;

	}
	return true;


}
////////////////////////
void Shape::cross(line lin1, int pos1, line lin2, int pos2, std::vector<Point> &pointer, const Shape &sh)
{
	if ((lin1.d[pos1] == lin2.d[pos2]) && (lin1.b[pos1] != lin2.b[pos2]) && (lin1.k[pos1] == lin2.k[pos2]))
		// | | -no cross

		return;


	if ((lin1.d[pos1] == lin2.d[pos2]) && (lin1.k[pos1] == lin2.k[pos2]) && (lin1.b[pos1] == lin2.b[pos2])) {
		// same. no cross,but....	
		return;


	}
	double crossX;
	double crossY;

	if (lin2.d[pos2] == 0)
	{
		crossX = -lin2.b[pos2] / lin2.k[pos2];
		crossY = (lin1.k[pos1] * crossX + lin1.b[pos1]);

	}
	else {
		if ((lin2.d[pos2] * lin1.k[pos1] - lin2.k[pos2] * lin1.d[pos1]) == 0) {
			if (lin2.k[pos2] == 0) {
				crossY = lin2.b[pos2];
				crossX = (lin1.d[pos1] * crossY - lin1.b[pos1]) / lin1.k[pos1];
			}

			else {
				crossY = lin2.b[pos2] / lin2.d[pos2];
				crossX = (lin1.d[pos1] * crossY - lin1.b[pos1]) / lin1.k[pos1];
			}
		}
		else {

			crossX = (lin2.b[pos2] * lin1.d[pos1] - lin2.d[pos2] * lin1.b[pos1]) / (lin2.d[pos2] * lin1.k[pos1] - lin2.k[pos2] * lin1.d[pos1]);
			crossY = (lin2.k[pos2] * crossX + lin2.b[pos2]) / lin2.d[pos2];

		}
	}

	bool check = false;
	for (size_t q = 0; q<pointer.size(); q++)
	{
		if ((crossX == pointer[q].getX()) && (crossY == pointer[q].getY()))
			check = true;
	}
	if (!check)
	{

		Point buffer(crossX, crossY);
		pointer.push_back(buffer);

	}
	return;

}