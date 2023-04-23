#include <iostream>
#include "Shape.h"
//Variant 12 Квадрат - Пятиконечная звезда - Правильный пятиугольник

using namespace std;

int Shape::id;

class Square : public Shape {
private:
	double a;
public:
	Square(double a, Point cent, double angle, Color& c):a(a), Shape(cent, angle, c) {
		peaks.push_back(Point(cent.getX() - a / 2, cent.getY() - a / 2));
		peaks.push_back(Point(cent.getX() - a / 2, cent.getY() + a / 2));
		peaks.push_back(Point(cent.getX() + a / 2, cent.getY() + a / 2));
		peaks.push_back(Point(cent.getX() + a / 2, cent.getY() - a / 2));
	}
	virtual void scale(double k) override {
		this->a *= k;
		for (int i = 0; i < peaks.size(); i++) {
			double dx = peaks[i].getX() - center.getX();
			double dy = peaks[i].getY() - center.getY();
			peaks[i].setX(center.getX() + k * dx);
			peaks[i].setY(center.getY() + k * dy);
		}
	}
	friend ostream & operator << (ostream & os, Square sq) {
		id++;
		os << Shape::id <<". Square:"<< endl;
		os << "Length: " << sq.a << endl;
		os << "Color: " << sq.color << endl << "Angle: " << sq.angle << endl;
		os << "Center: " << "(" << sq.center.getX() << "," << sq.center.getY() << ")" << endl;
		os << "Peaks: " << endl;
		for (int i = 0; i < sq.peaks.size(); i++) {
			os << "(" << sq.peaks[i].getX() << ", " << sq.peaks[i].getY() << ")" << endl;
		}
		os << endl;
		return os;
	}
};

class FivePointedStar : public Shape {
private:
	double R;
public:
	FivePointedStar(double R, Point center, double angle, Color& c)
		:R(R), Shape(center, angle, c) {
		double angleR = 2 * pi / 5;
		peaks.push_back(Point(center.getX() + R * cos(angleR * 0), center.getY() + R * sin(angleR * 0)));
		peaks.push_back(Point(center.getX() + R * cos(angleR * 1), center.getY() + R * sin(angleR * 1)));
		peaks.push_back(Point(center.getX() + R * cos(angleR * 2), center.getY() + R * sin(angleR * 2)));
		peaks.push_back(Point(center.getX() + R * cos(angleR * 3), center.getY() + R * sin(angleR * 3)));
		peaks.push_back(Point(center.getX() + R * cos(angleR * 4), center.getY() + R * sin(angleR * 4)));
	}
	virtual void scale(double k) override {
		this->R *= k;
		for (int i = 0; i < peaks.size(); i++) {
			double dx = peaks[i].getX() - center.getX();
			double dy = peaks[i].getY() - center.getY();
			peaks[i].setX(center.getX() + k * dx);
			peaks[i].setY(center.getY() + k * dy);
		}
	}
	friend ostream & operator << (ostream & os, FivePointedStar star) {
		id++;
		os << Shape::id << ". FivePointedStar:" << endl;
		os << "Radius: " << star.R << endl;
		os << "Color: " << star.color << endl << "Angle: " << star.angle << endl;
		os << "Center: " << "(" << star.center.getX() << "," << star.center.getY() << ")" << endl;
		os << "Peaks: " << endl;
		for (int i = 0; i < star.peaks.size(); i++) {
			os << "(" << star.peaks[i].getX() << ", " << star.peaks[i].getY() << ")" << endl;
		}
		os << endl;
		return os;
	}
};

class RegularPentagon : public Shape {
private:
	double a;
public:
	RegularPentagon(double a, Point center, double angle, Color& c)
		:a(a), Shape(center, angle, c) {
		double R = (sqrt(50 + 10 * sqrt(5))) / 10 * a;
		double angleR = 2 * pi / 5;
		peaks.push_back(Point(center.getX() + R * cos(angleR * 0), center.getY() + R * sin(angleR * 0)));
		peaks.push_back(Point(center.getX() + R * cos(angleR * 1), center.getY() + R * sin(angleR * 1)));
		peaks.push_back(Point(center.getX() + R * cos(angleR * 2), center.getY() + R * sin(angleR * 2)));
		peaks.push_back(Point(center.getX() + R * cos(angleR * 3), center.getY() + R * sin(angleR * 3)));
		peaks.push_back(Point(center.getX() + R * cos(angleR * 4), center.getY() + R * sin(angleR * 4)));
	
	}
	virtual void scale(double k) override {
		this->a *= k;
		for (int i = 0; i < peaks.size(); i++) {
			double dx = peaks[i].getX() - center.getX();
			double dy = peaks[i].getY() - center.getY();
			peaks[i].setX(center.getX() + k * dx);
			peaks[i].setY(center.getY() + k * dy);
		}
	}
	friend ostream & operator << (ostream & os, RegularPentagon rg) {
		id++;
		os << Shape::id << ". RegularPentagon:" << endl;
		os << "Length: " << rg.a << endl;
		os << "Center: " << "(" << rg.center.getX() << "," << rg.center.getY() << ")" << endl;
		os << "Color: " << rg.color << endl << "Angle: " << rg.angle << endl;
		os << "Center: " << "(" << rg.center.getX() << "," << rg.center.getY() << ")" << endl;
		os << "Peaks: " << endl;
		for (int i = 0; i < rg.peaks.size(); i++) {
			os << "(" << rg.peaks[i].getX() << ", " << rg.peaks[i].getY() << ")" << endl;
		}
		os << endl;
		return os;
	}
};

int main()
{
	Shape::id = 0;
	Color c1(255, 0, 255);
	Square square(5, { 0, 0 }, 0, c1);
	cout << square;
	FivePointedStar star(5, { 0,0 }, 0, c1);
	cout << star;
	RegularPentagon pentagon(5, { 0, 0 }, 0, c1);
	cout << pentagon;

	Shape::id = 0;
	Color c2(100, 100, 100);
	square.scale(3);
	star.move({ 1,2 });
	pentagon.setColor(c2);

	cout <<" square.scale(3)\n"<<"star.move({ 1,2 })\n"<<"pentagon.setColor(100,100,100)"<<endl;
	cout << "---After change---" << endl;
	cout << square;
	cout << star;
	cout << pentagon;

	system("pause");
	return 0;
}