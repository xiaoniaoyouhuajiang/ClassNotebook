#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <math.h>

using namespace std;

struct point {

	double x;
	double y;
};

enum color { RED, GREEN, BLUE, YELLOW, NO_COLOR };

class Shape {

protected:

	vector <point> coordinates;
	point centre;
	double angle;
	long int id;
	color clr;

public:

	Shape(point _centre) {
	
		srand(time(NULL));
		
		id     = rand();
		clr    = NO_COLOR;
		angle  = 0;
		centre = _centre;
	};

	virtual void scale(double resizeCoefficient) = 0;
	
	void move(point newCenter) {

		centre = newCenter;
		makeСoordinates();
	}

	void rotate(double _angle) {

		double _x, _y;

		for (int i = 0; i < coordinates.size(); ++i) {

			_x = coordinates[i].x;
			_y = coordinates[i].y;

			coordinates[i].x = (_x - centre.x) * cos(_angle) - (_y - centre.y) * sin(_angle) + centre.x;
			coordinates[i].y = (_x - centre.x) * sin(_angle) + (_y - centre.y) * cos(_angle) + centre.y;
		}

		angle = _angle;
	}

	color getСolor() {

		return clr;
	}

	void setСolor(color _clr) {

		clr = _clr;
	}

	virtual ~Shape() {};

	friend ostream& operator<< (ostream& outputStream, const Shape& shape) {

		outputStream << "Id: " << shape.id << endl;
		outputStream << "Coordinates of extreme points: ";

		for (int i = 0; i < shape.coordinates.size(); ++i) {

			outputStream << "(" << shape.coordinates[i].x << ", " << shape.coordinates[i].y << ") ";
		}

		outputStream << endl << "Color: ";

		switch (shape.clr) {
			
			case RED:
				outputStream << "red"    << endl;
				break;
			case GREEN:
				outputStream << "green"  << endl;
				break;
			case BLUE:
				outputStream << "blue"   << endl;
				break;
			case YELLOW:
				outputStream << "yellow" << endl;
				break;
			case NO_COLOR:
			case default:
				outputStream << "color is not defined" << endl;
				break;
		}

		return outputStream;
	}

private:
	
	virtual void makeCoordinates() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Square : public Shape {

private:

	double side;

public:

	Square(double _side, point _centre) : Shape (_centre) {

		side = _side;
		makeCoordinates();
	}

	void scale(double resizeCoefficient) {

		side *= resizeCoefficient;
		makeCoordinates();
	}

	~Square() {

		coordinates.clear();
	}

	friend std::ostream& operator<< (ostream& outputStream, const Square& square) {

		outputStream << "Square" << endl;
		outputStream << (const Shape&)square;
		return outputStream;
	}

private:

	void makeCoordinates() {

		coordinates.clear();
		coordinates.push_back({ centre.x - side / 2, centre.y + side / 2 });
		coordinates.push_back({ centre.x + side / 2, centre.y + side / 2 });
		coordinates.push_back({ centre.x + side / 2, centre.y - side / 2 });
		coordinates.push_back({ centre.x - side / 2, centre.y - side / 2 });

		rotate(angle);
	}

};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Ellipse : public Shape {

private:

	double minDiameter;
	double maxDiameter;

public:

	Ellipse(double diameter, double _diameter, point _centre) : Shape (_centre) {

		if (diameter > _diameter) {

			minDiameter = _diameter;
			maxDiameter = diameter;
		} else {

			minDiameter = diameter;
			maxDiameter = _diameter;
		}

		makeCoordinates();
	}

	void scale(double resizeCoefficient) {

		minDiameter *= resizeCoefficient;
		maxDiameter *= resizeCoefficient;
		makeCoordinates();
	}

	~Ellipse() {

		coordinates.clear();
	}

	friend std::ostream& operator<< (ostream& outputStream, const Ellipse& ellipse) {

		outputStream << "Ellipse" << endl;
		outputStream << (const Shape&)ellipse;
		
		return outputStream;
	}

private:

	void makeСoordinates() {

		coordinates.clear();
		coordinates.push_back({ centre.x, centre.y + minDiameter / 2 });
		coordinates.push_back({ centre.x + maxDiameter / 2, centre.y });
		coordinates.push_back({ centre.x, centre.y - minDiameter / 2 });
		coordinates.push_back({ centre.x - maxDiameter / 2, centre.y });

		rotate(angle);
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Rhombus : public Shape {

private:
	double side;
	double minDiagonal;
	double maxDiagonal;

public: 
	
	Rhombus(double _side, double _minDiagonal, double _maxDiagonal, point _centre) : Shape(_centre) {

		side  = _side;
		if (_minDiagonal < _maxDiagonal) {
			
			minDiagonal = _minDiagonal;
			maxDiagonal = _maxDiagonal;
		}
		else {
			maxDiagonal = _minDiagonal;
			minDiagonal = _maxDiagonal;
		}
		
		makeCoordinates();
	}
	
	void scale(double resizeCoefficient) {

		side 	    *= resizeCoefficient;
		maxDiagonal *= resizeCoefficient;
		minDiagonal *= resizeCoefficient;
		makeCoordinates();
	}

	~Rhombus() {

		coordinates.clear();
	}

	friend std::ostream& operator<< (ostream& outputStream, const Rhombus& rhombus) {

		outputStream << "Rhombus" << endl;
		outputStream << (const Shape&)rhombus;
		
		return outputStream;
	}

private:

	void makeCoordinates() {

		coordinates.clear();
		coordinates.push_back(centre);

		coordinates.push_back({ centre.x - maxDiagonal / 2, centre.y});
		coordinates.push_back({ centre.x, centre.y + minDiagonal / 2});
		coordinates.push_back({ centre.x + maxDiagonal / 2, centre.y});
		coordinates.push_back({ centre.x, centre.y - minDiagonal / 2});

		rotate(angle);
	}
};