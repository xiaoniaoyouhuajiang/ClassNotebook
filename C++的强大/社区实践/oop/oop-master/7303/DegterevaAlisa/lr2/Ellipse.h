#include "Shape.h"


class Ellipse : public Shape {

private:

	double minDiameter;
	double maxDiameter;

public:

	Ellipse(double diameter, double _diameter, point _centre) : Shape(_centre) {

		if (diameter > _diameter) {

			minDiameter = _diameter;
			maxDiameter = diameter;
		}
		else {

			minDiameter = diameter;
			maxDiameter = _diameter;
		}

		make_coordinates();
	}

	void scale(double coefficient) {

		minDiameter = minDiameter * coefficient;
		maxDiameter = maxDiameter * coefficient;
		make_coordinates();
	}

	~Ellipse() {

		coordinates.clear();
	}

private:

	void make_coordinates() {

		coordinates.clear();
		coordinates.push_back({ centre.x, centre.y + minDiameter / 2 });
		coordinates.push_back({ centre.x + maxDiameter / 2, centre.y });
		coordinates.push_back({ centre.x, centre.y - minDiameter / 2 });
		coordinates.push_back({ centre.x - maxDiameter / 2, centre.y });

		rotate(ang);
	}

	void print(ostream& out) {

		out << "Ellipse" << endl;
		out << "Id: " << id << endl;
		out << "Coordinates: ";

		for (unsigned int i = 0; i < coordinates.size(); ++i) {

			out << "(" << coordinates[i].x << ", " << coordinates[i].y << ") ";
		}

		out << endl << "Color: ";

		switch (clr) {

		case RED:
			out << "red" << endl;
			break;
		case ORANGE:
			out << "orange" << endl;
			break;
		case GREEN:
			out << "green" << endl;
			break;
		case BLUE:
			out << "blue" << endl;
			break;
		case YELLOW:
			out << "yellow" << endl;
			break;
		case NO_COLOR:
			out << "no color" << endl;
			break;
		}
	}

};