#include <iostream>
#include <vector>

#include "RegularPolygon.h"
#include "Star.h"
#include "Triangle.h"
#include "Shape.h"
#include "RightTriangle.h"

void print(std::vector<Shape *> &shapes) {
	for (auto shape = shapes.begin(); shape != shapes.end(); shape++) {
		if (dynamic_cast<Triangle *>(*shape)) {
			dynamic_cast<Triangle *>(*shape)->rotate(90);
			std::cout << *dynamic_cast<Triangle *>(*shape);
		}
		else if (dynamic_cast<Star *>(*shape)) {
			dynamic_cast<Star *>(*shape)->move(Pointf(3, 2));
			std::cout << *dynamic_cast<Star *>(*shape);
		}
		else if (dynamic_cast<RightTriangle *>(*shape)) {
			dynamic_cast<RightTriangle *>(*shape)->scale(0.2f);
			std::cout << *dynamic_cast<RightTriangle *>(*shape);
		}
	}
}

int main() {
	std::vector<Shape *> shapes;
	shapes.emplace_back(new Triangle(Pointf(0, 0), Pointf(123, 42), Pointf(13, 54), Color(3, 255, 90)));
	shapes.emplace_back(new Star(5, 10, 6, Pointf(0, 0), Color(255, 255, 255)));
	shapes.emplace_back(new RightTriangle(Pointf(0, 0), 10.0f, 14.4f));

	print(shapes);

	system("pause");
	return 0;
}
