#pragma once

#include <random>
#include <string>

#include "MyVector.hpp"
#include "MySharedPtr.hpp"
#include "Shape.hpp"
#include "MyList.hpp"

class GenShape
{
public:
	GenShape();

	stepik::vector<stepik::shared_ptr<Shape>> get_shape_vector(int len);

private:
	int get_int(int a = 1, int b = 10);
	double get_double(double a = 1.0, double b = 10.0);

	stepik::vector<double> get_double_vector(int len, double a = 1.0, int b = 10.0);
	stepik::vector<int> get_int_vector(int len, int a = 1, int b = 10);
	stepik::vector<std::string> get_string_vector(int len);

	std::mt19937 gen;
};

std::pair<bool, stepik::shared_ptr<Shape>> unmodif_algorithm(const stepik::vector<stepik::shared_ptr<Shape>>& shapes,
	int left, int right, double value);

std::pair<stepik::list<stepik::shared_ptr<Shape>>, stepik::list<stepik::shared_ptr<Shape>>> modif_algorithm(stepik::vector<stepik::shared_ptr<Shape>>& shapes,
	int left, int right, double value, GenShape& gen);