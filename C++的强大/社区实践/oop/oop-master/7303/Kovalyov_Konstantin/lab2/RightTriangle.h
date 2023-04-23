#pragma once

#include "Triangle.h"


class RightTriangle : public Triangle {
	friend std::ostream &operator<<(std::ostream &output, RightTriangle &t) {
		output << "I'm RightTriangle\nMy coords : \n";

		for (auto iter = t.positions.begin(); iter != t.positions.end(); iter++) {
			output << "(" << iter->x << ", " << iter->y << ")" << std::endl;
		}

		//printf("My color - #%.2x%.2x%.2x\n\n", t.color.r, t.color.g, t.color.b);

		output.precision(2);
		output << "My color - " << std::hex << (int)t.color.r << " " << (int)t.color.g << " " << (int)t.color.b << std::endl << std::endl;

		return output;
	}

public:
	RightTriangle(Pointf right_angle_pos, float x_offset, float y_offset, Color _color = Color())
		: Triangle(right_angle_pos, right_angle_pos + Pointf(x_offset, 0), right_angle_pos + Pointf(0, y_offset), _color) {}

	virtual void move(Pointf new_position) {
		Triangle::move(new_position);
	}

	virtual void rotate(float _angle) {
		Triangle::rotate(_angle);
	}

	virtual void scale(float pc) {
		Triangle::scale(pc);
	}
};