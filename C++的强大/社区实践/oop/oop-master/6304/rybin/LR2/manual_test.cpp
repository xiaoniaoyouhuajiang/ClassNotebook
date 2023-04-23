#include "Shape.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
	Shape* base_ptr;

	base_ptr = new Circle("blue", 2.0, { 3.0, 4.0 });
	base_ptr->operator<<(std::cout);

	base_ptr->set_color("yellow");
	base_ptr->zoom(2.0);
	base_ptr->move({ 10.0, 20.0 });
	base_ptr->rotate(RIGHT180);
	base_ptr->operator<<(std::cout);
	delete base_ptr;

	base_ptr = new Square("brown", 5.0, { -10.0, -5.0 });
	base_ptr->operator<<(std::cout);

	base_ptr->set_color("red");
	base_ptr->zoom(1.0 / 2.0);
	base_ptr->move({ 5.0, -10.0 });
	base_ptr->rotate(LEFT90);
	base_ptr->operator<<(std::cout);
	delete base_ptr;

	base_ptr = new Triangle("green", 6.0, { -10.0, 5.0 });
	base_ptr->operator<<(std::cout);

	base_ptr->set_color("white");
	base_ptr->zoom(1.0 / 3.0);
	base_ptr->move({ 5.0, 10.0 });
	base_ptr->rotate(LEFT90);
	base_ptr->operator<<(std::cout);
	delete base_ptr;

	getchar();

	return 0;
}

