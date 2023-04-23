
#ifndef Trapezium_h
#define Trapezium_h
#include "Shape.h"
class Trapezium :public Shape {
public:
	static bool is_trapezium(const std::vector<Dot>& corners); // проверка на ромб

															   //конструктор
	Trapezium(std::vector<Dot> points, Color color = Color(), double angle = 0) :Shape(points, color, angle) {
		if (!is_trapezium(points)) {
			throw std::invalid_argument("It is not trapezium");
		}
		else {
			corners = points;
		}
	}


	void print(std::ostream& OS) const override; // Вывод
};
#endif Trapezium_h