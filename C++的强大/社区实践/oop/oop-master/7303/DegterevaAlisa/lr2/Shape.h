#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <exception>

static int s_itemID;

using namespace std;

struct point {

	double x;
	double y;
};

enum color { RED, ORANGE, GREEN, BLUE, YELLOW, NO_COLOR };

class Shape {

protected:

	vector <point> coordinates;
	point centre;
	double ang;
	color clr;
	long int id;

public:

	Shape(point _centre) {

		id = s_itemID++;;

		clr = NO_COLOR;
		ang = 0;

		centre = _centre;
	};

	virtual void scale(double coefficient) = 0;

	void move(point _coordinates) {

		centre = _coordinates;
		make_coordinates();
	}

	void rotate(double _angle) {

		double _x, _y;

		for (unsigned int i = 0; i < coordinates.size(); ++i) {

			_x = coordinates[i].x;
			_y = coordinates[i].y;

			coordinates[i].x = (_x - centre.x) * cos(_angle) - (_y - centre.y) * sin(_angle) + centre.x;
			coordinates[i].y = (_x - centre.x) * sin(_angle) + (_y - centre.y) * cos(_angle) + centre.y;
		}

		ang = _angle;
	}

	color get_golor() {

		return clr;
	}

	void set_color(color _clr) {

		clr = _clr;
	}

	virtual ~Shape() {};

	ostream& operator<< (ostream& out) {

		print(out);
		return out;
	}

	virtual point& operator[] (const size_t index) {

		try {

			if (index >= coordinates.size())
				throw std::exception("Выход за границы вектора");

			return coordinates[index];
		}
		catch (std::exception msg) {

			cout << msg.what() << endl;
			throw;
		}

	}

private:

	virtual void print(ostream& out) = 0;
	virtual void make_coordinates() = 0;
};
