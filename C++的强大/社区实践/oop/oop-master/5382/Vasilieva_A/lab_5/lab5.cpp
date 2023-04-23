#include "lab5.h"

const double diapason = 10;

int rand_val(double fMin = -diapason, double fMax = diapason)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

shared_ptr<Shape> randShape()
{
	static size_t x = rand() % 3;

	shared_ptr<Shape> tmp;

	switch (x)
	{
	case 0:
	{
		tmp = shared_ptr<Shape>(new Square(Point(rand_val(), rand_val()), Point(rand_val(), rand_val())));
		break;
	}
	case 1:
	{
		tmp = shared_ptr<Shape>(new sqTriangle(Point(rand_val(), rand_val()), Point(rand_val(), rand_val()), rand_val(0)));
		break;
	}
	case 2:
	{
		tmp = shared_ptr<Shape>(new isosTriangle(Point(rand_val(), rand_val()), Point(rand_val(), rand_val()), rand_val(0)));
		break;
	}
	}
	return tmp;
}

list<shared_ptr<Shape>> randList()
{
	list<shared_ptr<Shape>> my_list;
	for (size_t i = 0; i < 1000; ++i)
	{
		my_list.push_back(randShape());
	}
	return my_list;
}