#ifndef STAR_H
#define STAR_H

#include <vector>
#include <iostream>

#include "RegularPolygon.h"

class Star : public RegularPolygon {
	friend std::ostream &operator<<(std::ostream &output, Star &t) {
		output << "I'm Star\nMy coords : \n";

		for (auto iter = t.positions.begin(); iter != t.positions.end(); iter++) {
			output << "(" << iter->x << ", " << iter->y << ")" << std::endl;
		}

		for (auto iter = t.star_positions.begin(); iter != t.star_positions.end(); iter++) {
			output << "(" << iter->x << ", " << iter->y << ")" << std::endl;
		}

		//printf("My color - #%.2x%.2x%.2x\n\n", t.color.r, t.color.g, t.color.b);

		output.precision(2);
		output << "My color - " << std::hex << (int)t.color.r << " " << (int)t.color.g << " " << (int)t.color.b << std::endl << std::endl;

		return output;
	}

protected:
	UINT second_radius;
	std::vector<Pointf> star_positions;

public:
	Star(UINT _radius, UINT _second_radius, UINT _vertex_num = 5, Pointf _position = Pointf(), Color _color = Color())
		: RegularPolygon(_radius, _vertex_num, _position, _color)
		, second_radius(_second_radius)
		, star_positions(std::vector<Pointf>(vertex_num, Pointf())) {
		this->calc_positions();
	}

	bool operator==(Star &s) {
		return this->area() == s.area();
	}

	virtual void move(Pointf new_position) {
		this->position = new_position;
		this->calc_positions(new_position);
	}

	virtual void rotate(float _angle) {
		this->angle += _angle;
		this->calc_positions();
	}

protected:
	virtual void calc_positions(Pointf move_vector = Pointf()) {
		RegularPolygon::calc_positions(move_vector);
		auto fraction = 360.0f / static_cast<float>(vertex_num);

		for (int i = 0; i < vertex_num; i++) {
			*(positions.begin() + i) = Pointf(radius * std::cos(i * (angle + fraction)),
				radius * std::sin(i * (angle + fraction))) + move_vector;

			*(star_positions.begin() + i) = Pointf(second_radius * std::cos(i * (angle + 1.5f * fraction)),
				second_radius * std::sin(i * (angle + 1.5f * fraction))) + move_vector;
		}
	}

private:
	float area() const {
		auto fraction = 360.0f / static_cast<float>(vertex_num);
		float h1 = radius * std::cos(fraction / 2.0f);
		float h2 = second_radius - h1;
		float a = 2 * radius * std::sin(fraction / 2.0f);

		return 0.5f * a * (h1 + h2);
	}
};

#endif