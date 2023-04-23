#ifndef PARALLELOGRAM_HPP
#define PARALLELOGRAM_HPP

#include "Shape.hpp"

class Parallelogram : public Shape {
	double base_len;
	double side_len;
	double alpha;
public:
	Parallelogram(const double base_len, const double side_len, const double alpha,
				  const Point centre = Point(0, 0), const Color color = Color(0, 0, 0))
				  : Shape(centre, color), base_len(base_len), side_len(side_len), alpha(alpha) {
		vertex[0] = Point(centre.x - side_len / 2 * std::cos(alpha * M_PI / 180) - base_len / 2, centre.y - side_len / 2 * std::sin(alpha * M_PI / 180));
		vertex[1] = Point(centre.x - side_len / 2 * std::cos(alpha * M_PI / 180) + base_len / 2, centre.y - side_len / 2 * std::sin(alpha * M_PI / 180));
		vertex[2] = Point(centre.x + side_len / 2 * std::cos(alpha * M_PI / 180) + base_len / 2, centre.y + side_len / 2 * std::sin(alpha * M_PI / 180));
		vertex[3] = Point(centre.x + side_len / 2 * std::cos(alpha * M_PI / 180) - base_len / 2, centre.y + side_len / 2 * std::sin(alpha * M_PI / 180));
	};
	~Parallelogram() {};

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
		base_len *= increase_factor;
		side_len *= increase_factor;
		for (size_t i = 0; i < 4; i++)
			vertex[i] *= increase_factor;
	}

	friend std::ostream & operator << (std::ostream &out, const Parallelogram &obj) {
		out << "ID: " << obj.id << std::endl <<
			   "Shape type: Parallelolgram" << std::endl <<
			   "Color: " << obj.color << std::endl <<
			   "base_length: " << obj.base_len << std::endl <<
			   "Side length: " << obj.side_len << std::endl <<
			   "alpha: " << obj.alpha << std::endl <<
			   "Center coordinates: " << obj.centre << std::endl <<
			   "vertex coordinates: ";
		for (size_t i = 0; i < 4; i++)
			out << obj.vertex[i] << " ";
		out << std::endl;

		return out;
	}
};

#endif
