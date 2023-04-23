#include "MyAlgorithm.hpp"

GenShape::GenShape()
{
	std::random_device rd;
	gen.seed(rd());
}

int GenShape::get_int(int a, int b)
{
	return (a + gen() % (b - a + 1));
}

double GenShape::get_double(double a, double b)
{
	std::uniform_real_distribution<> dist(a, b);

	return dist(gen);
}

stepik::vector<double> GenShape::get_double_vector(int len, double a, int b)
{
	std::uniform_real_distribution<> dist(a, b);
	stepik::vector<double> result(len);

	for (int i = 0; i < len; i++) {
		result[i] = dist(gen);
	}

	return result;
}

stepik::vector<int> GenShape::get_int_vector(int len, int a, int b)
{
	std::uniform_int_distribution<> dist(a, b);
	stepik::vector<int> result(len);

	for (int i = 0; i < len; i++) {
		result[i] = dist(gen);
	}

	return result;
}

stepik::vector<std::string> GenShape::get_string_vector(int len)
{
	std::uniform_int_distribution<> dist(1, 7);
	stepik::vector<std::string> result(len);

	for (int i = 0; i < len; i++) {
		int res = dist(gen);
		switch (res)
		{
		case 1:
			result[i] = "green";
			break;
		case 2:
			result[i] = "blue";
			break;
		case 3:
			result[i] = "red";
			break;
		case 4:
			result[i] = "black";
			break;
		case 5:
			result[i] = "yellow";
			break;
		case 6:
			result[i] = "orange";
			break;
		case 7:
			result[i] = "white";
			break;
		default:
			result[i] = "unknown color";
			break;
		}
	}

	return result;
}

stepik::vector<stepik::shared_ptr<Shape>> GenShape::get_shape_vector(int len)
{
	stepik::vector<stepik::shared_ptr<Shape>> result(len);

	stepik::vector<std::string> colors = get_string_vector(len);
	stepik::vector<double> sizes = get_double_vector(len);
	stepik::vector<int> types = get_int_vector(len, 0, 2);

	for (int i = 0; i < len; i++) {
		Point point = { get_double(), get_double() };
		int angle = get_int(0, 4);

		switch (types[i])
		{
		case CIRCLE:
			result[i].reset(new Circle(colors[i], sizes[i], point));
			break;
		case SQUARE:
			result[i].reset(new Square(colors[i], sizes[i], point));
			(*result[i]).rotate(rot_angle(angle));
			break;
		case TRIANGLE:
			result[i].reset(new Triangle(colors[i], sizes[i], point));
			(*result[i]).rotate(rot_angle(angle));
			break;
		default:
			break;
		}
	}

	return result;
}

std::pair<bool, stepik::shared_ptr<Shape>> unmodif_algorithm(const stepik::vector<stepik::shared_ptr<Shape>>& shapes, int left, int right, double value)
{
	for (int i = left - 1; i < right; i++) {
		if ((*shapes[i]).area() > value) {
			return std::pair<bool, stepik::shared_ptr<Shape>>(true, shapes[i]);
		}

		if (i == right - 1) {
			return std::pair<bool, stepik::shared_ptr<Shape>>(false, stepik::shared_ptr<Shape>());
		}
	}
}

std::pair<stepik::list<stepik::shared_ptr<Shape>>,
stepik::list<stepik::shared_ptr<Shape>>> modif_algorithm(stepik::vector<stepik::shared_ptr<Shape>>& shapes,
																			int left, int right, double value, GenShape& gen)
{
	stepik::vector<stepik::shared_ptr<Shape>> new_shapes = gen.get_shape_vector(right - left + 1);

	stepik::list<stepik::shared_ptr<Shape>> new_shapes_list;
	stepik::list<stepik::shared_ptr<Shape>> copied;

	for (int i = left - 1; i < right; i++) {
		if ((*shapes[i]).area() > value) {
			copied.push_back(shapes[i]);
			shapes[i].swap(new_shapes[i - left + 1]);
			new_shapes_list.push_back(shapes[i]);
		}
	}
	
	return { new_shapes_list, copied };
}