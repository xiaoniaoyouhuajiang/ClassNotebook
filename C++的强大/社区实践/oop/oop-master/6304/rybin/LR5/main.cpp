// Lab5.cpp: определяет точку входа для консольного приложения.
//

#include "MyAlgorithm.hpp"
#include <iostream>

int main()
{
	int num = 0;
	GenShape generator;

	std::cout << "Input num of figures to generate: ";
	std::cin >> num;
	
	auto shapes = generator.get_shape_vector(num);

	std::cout << std::endl <<  "FIGURES:" << std::endl << std::endl;
	for (int i = 0; i < shapes.size(); i++) {
		std::cout << "#" << i + 1 << std::endl;
		std::cout << shapes[i].get() << std::endl;
		shapes[i]->operator<<(std::cout);
	}

	int leftbound, rightbound;
	double area;
	std::cout << "non-modifying algorithm: Check that at least one element of the range has an area larger than the specified value" << std::endl;
	std::cout << "left bound: ";
	std::cin >> leftbound;
	std::cout << "right bound: ";
	std::cin >> rightbound;
	std::cout << "value: ";
	std::cin >> area;
	
	auto result1 = unmodif_algorithm(shapes, leftbound, rightbound, area);
	if (result1.first) {
		std::cout << std::endl << "[True]" << std::endl << "area is : " << result1.second->area() << std::endl;
		std::cout << result1.second.get() << std::endl;
		result1.second->operator<<(std::cout);
	}
	else {
		std::cout << std::endl <<  "[False]" << std::endl;
	}

	std::cout << "modifying algorithm: Replace elements that have an area larger than a given value by new random elements, copying the entire range." << std::endl;
	std::cout << "left bound: ";
	std::cin >> leftbound;
	std::cout << "right bound: ";
	std::cin >> rightbound;
	std::cout << "value: ";
	std::cin >> area;

	auto result2 = modif_algorithm(shapes, leftbound, rightbound, area, generator);

	if (result2.first.size()) {
		std::cout << std::endl << "NEW FIGURES: " << std::endl << std::endl;

		for (auto it = result2.first.begin(); it != result2.first.end(); it++) {
			std::cout << it->get() << std::endl;
			it->get()->operator<<(std::cout);
		}

		std::cout << std::endl << "COPYIED OLD FIGURES: " << std::endl << std::endl;

		for (auto it = result2.second.begin(); it != result2.second.end(); it++) {
			std::cout << it->get() << std::endl;
			it->get()->operator<<(std::cout);
		}
	}
	else {
		std::cout << std::endl << "[Empty] no figures to replace" << std::endl;
	}

    return 0;
}

