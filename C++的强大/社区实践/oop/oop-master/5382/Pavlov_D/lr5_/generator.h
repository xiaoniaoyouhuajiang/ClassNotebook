#pragma once

#include "Square.h"
#include "IsoscelesTriangle.h"
#include "RightTriangle.h"
#include <ctime>
#include "SharedPtrStepik.h"
#include "vectorStepik.h"
//Simple random generator.Need More....
Point generate_Point(long int limit)
{

	Point point(rand() % limit, rand() % limit);
	return point;
}
stepik::shared_ptr<Shape>  generate_Square(long int limit)
{


	Point generatePoint1 = generate_Point(limit);
	double sideSize = rand() % limit + 1;
	stepik::shared_ptr<Shape> buffer(new Square({ generatePoint1,Point(generatePoint1.getX(),generatePoint1.getY() + sideSize),
		Point(generatePoint1.getX() + sideSize,generatePoint1.getY()),Point(generatePoint1.getX() + sideSize,generatePoint1.getY() + sideSize) }));

	return buffer;
}
stepik::shared_ptr<Shape> generate_IsoscelesTriangle(long int limit)
{

	Point generatePoint1 = generate_Point(limit);
	double distance = rand() % (limit / 2) + 1;
	double height = rand() % (limit / 2) + 4;
	stepik::shared_ptr<Shape> buffer(new IsoscelesTriangle({ generatePoint1,Point(generatePoint1.getX() + height,generatePoint1.getY() + distance),
		Point(generatePoint1.getX() + height,generatePoint1.getY() - distance) }));

	return buffer;
}

stepik::shared_ptr<Shape> generate_RightTriangle(long int limit)
{

	Point generatePoint1 = generate_Point(limit);
	//Same Points defence Forces//
	double otherCoordinate1 = rand() % limit;
	double otherCoordinate2 = rand() % limit;
	if ((otherCoordinate1 == otherCoordinate2) || (otherCoordinate1 == generatePoint1.getY()))
		otherCoordinate1++;
	if ((otherCoordinate1 == otherCoordinate2) || (otherCoordinate2 == generatePoint1.getX()))
		otherCoordinate2++;

	stepik::shared_ptr<Shape> buffer(new RightTriangle({ generatePoint1,
		Point(generatePoint1.getX(),otherCoordinate1),Point(otherCoordinate2,generatePoint1.getY()) }));

	return buffer;
}
stepik::vector<stepik::shared_ptr<Shape>> generate_shape_array(long size, long limit)
{

	stepik::vector<stepik::shared_ptr<Shape>> array;
	for (int count = 0; count <size; ++count)
	{
		stepik::shared_ptr<Shape> buffer;
		size_t switch_on = rand() % 3 + 1;

		switch (switch_on)
		{
		case 1:
		{
			buffer = generate_Square(limit);
			break;
		}
		case 2:
		{
			buffer = (generate_RightTriangle(limit));

			break;
		}
		case 3:
		{
			buffer = (generate_IsoscelesTriangle(limit));
			break;
		}
		default:
			break;
		}
		array.push_back(buffer);
	}
	return array;
}