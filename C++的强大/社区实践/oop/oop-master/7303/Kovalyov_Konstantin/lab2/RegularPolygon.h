#ifndef REGULARPOLYGON_H
#define REGULARPOLYGON_H

#include <vector>

#include "Shape.h"

class RegularPolygon : public Shape {
	friend std::ostream &operator<<(std::ostream &output, RegularPolygon &t) {
		output << "I'm RegularPolygon\nMy coords : \n";

		for (auto iter = t.positions.begin(); iter != t.positions.end(); iter++) {
			output << "(" << iter->x << ", " << iter->y << ")" << std::endl;
		}

		//printf("My color - #%.2x%.2x%.2x\n\n", t.color.r, t.color.g, t.color.b);

		output.precision(2);
		output << "My color - " << std::hex << (int)t.color.r << " " << (int)t.color.g << " " << (int)t.color.b << std::endl << std::endl;

		return output;
	}

protected:
	UINT radius;
	UINT vertex_num;

	std::vector<Pointf> positions;

public:
	RegularPolygon(UINT _radius, UINT _vertex_num,
		Pointf _position = Pointf(), Color _color = Color())
		: Shape(_position, _color)
		, radius(_radius)
		, vertex_num(_vertex_num)
		, positions(std::vector<Pointf>(vertex_num, Pointf())) {
		this->calc_positions();
	}

	virtual ~RegularPolygon() {}

	virtual void rotate(float _angle) {
		this->angle += _angle;
		this->calc_positions();
	}

	virtual void move(Pointf new_position) {
		this->position = new_position;
		this->calc_positions(new_position);
	}

protected:
	virtual void calc_positions(Pointf move_vector = Pointf()) {
		auto fraction = 360.0f / static_cast<float>(vertex_num);

		for (int i = 0; i < vertex_num; i++) {
			*(positions.begin() + i) = Pointf(radius * std::cos(i * (angle + fraction)),
											  radius * std::sin(i * (angle + fraction))) + move_vector;
		}
	}
};

#endif