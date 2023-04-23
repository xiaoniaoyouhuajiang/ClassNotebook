#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Shape.hpp"

class Square : public Shape {
	double side_len;
public:
	Square(const double side_len,
		const Point centre = Point(0, 0), const Color color = Color(0, 0, 0))
		: Shape(centre, color), side_len(side_len) {
		vertex[0] = Point(centre.x - side_len / 2, centre.y - side_len / 2);
		vertex[1] = Point(centre.x + side_len / 2, centre.y - side_len / 2);
		vertex[2] = Point(centre.x + side_len / 2, centre.y + side_len / 2);
		vertex[3] = Point(centre.x - side_len / 2, centre.y + side_len / 2);
	};
	~Square() {};

	void rotate(const double angle) {
		for (size_t i = 0; i < 4; i++) {
			double x = vertex[i].x - centre.x;
			double y = vertex[i].y - centre.y;
			vertex[i].x = x * std::cos(angle * (M_PI / 180)) - y * std::sin(angle * (M_PI / 180)) + centre.x;
			vertex[i].y = x * std::sin(angle * (M_PI / 180)) + y * std::cos(angle * (M_PI / 180)) + centre.y;
		}
	}

	void moveTo(const Point point) {
		centre += point;
		for (size_t i = 0; i < 4; i++)
			vertex[i] += point;
	}

	void scale(const double increase_factor) {
		side_len *= increase_factor;
		for (size_t i = 0; i < 4; i++)
			vertex[i] *= increase_factor;
	}

	friend std::ostream & operator << (std::ostream &out, const Square &obj) {
		out << "ID: " << obj.id << std::endl <<
			   "Shape type: Square" << std::endl <<
			   "Color: " << obj.color << std::endl <<
			   "Side length: " << obj.side_len << std::endl <<
			   "Center coordinates: " << obj.centre << std::endl <<
			   "vertex coordinates: ";
		for (size_t i = 0; i < 4; i++)
			out << obj.vertex[i] << " ";
		out << std::endl;

		return out;
	}
};

#endif