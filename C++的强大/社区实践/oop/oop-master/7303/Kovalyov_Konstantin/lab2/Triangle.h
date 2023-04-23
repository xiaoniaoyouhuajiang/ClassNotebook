#pragma once

#include <vector>
#include <iostream>

#include "Shape.h"

class Triangle : public Shape {
	friend std::ostream &operator<<(std::ostream &output, Triangle &t) {
		output << "I'm Triangle\nMy coords : \n";

		for (auto iter = t.positions.begin(); iter != t.positions.end(); iter++) {
			output << "(" << iter->x << ", " << iter->y << ")" << std::endl;
		}

		//printf("My color - #%.2x%.2x%.2x\n\n", t.color.r, t.color.g, t.color.b);

		output.precision(2);
		output << "My color - " << std::hex << (int)t.color.r << " " << (int)t.color.g << " " << (int)t.color.b << std::endl << std::endl;

		return output;
	}

protected:
	std::vector<Pointf> positions;

public:
	Triangle(Pointf first, Pointf second, Pointf third, Color _color = Color())
		: Shape(calc_center(first, second, third), _color)
		, positions(std::vector<Pointf>({ first, second, third })) {}

	virtual void move(Pointf new_position) {
		Pointf vect = new_position - this->position;
		this->position = new_position;

		for (auto iter = positions.begin(); iter != positions.end(); iter++) {
			iter->x += vect.x; //Лень было переопределять оператор += :/
			iter->y += vect.y;
		}
	}

	virtual void rotate(float _angle) {
		this->angle += _angle;

		for (auto iter = positions.begin(); iter != positions.end(); iter++) {
			iter->x = (iter->x - position.x) * std::cos(this->angle) - (iter->y - position.y) * std::sin(this->angle) + position.x;
			iter->y = (iter->x - position.x) * std::sin(this->angle) + (iter->y - position.y) * std::cos(this->angle) + position.y;
		}
	}

	virtual void scale(float pc) {
		for (auto iter = positions.begin(); iter != positions.end(); iter++) {
			iter->x = pc * (iter->x - this->position.x);
			iter->y = pc * (iter->y - this->position.y);
		}
	}

protected:
	Pointf calc_center(Pointf _first, Pointf _second, Pointf _third) {
		Pointf just_center = _first + _second + _third;

		return Pointf(just_center.x / 3.0f, just_center.y / 3.0f);
	}
};