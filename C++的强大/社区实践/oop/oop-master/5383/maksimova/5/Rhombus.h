#pragma once
#ifndef Rhombus_h
#define Rhombus_h
#include"Shape.h"
#include "Dot.h"
#include <vector>

class Rhombus :public Shape {
public:
	static bool is_rhombus(const std::vector<Dot>& corners); // проверка на ромб

															 //конструктор
	Rhombus(std::vector<Dot> points, Color color = Color(), double angle = 0) :Shape(points, color, angle) {
		if (!is_rhombus(points)) {
			throw std::invalid_argument("It is not Rhombus");
		}
		else {
			corners = points;
		}
	}


	void print(std::ostream& OS) const override; // Вывод
};
#endif Rhombus_h