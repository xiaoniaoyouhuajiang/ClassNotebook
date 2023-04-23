#pragma once

#include <ctime>

#include "vector.h"
#include "sharedptr.hpp"
#include "shape.hpp"
#include "Circle.hpp"
#include "Pentagon.hpp"
#include "RegularPentagon.hpp"


const double BORDER = 40;
const double RBORDER = 10;

namespace rabid
{
	double randNumber(double lborder, double rborder)
	{
		return (int)((double)(rand()) / RAND_MAX*(rborder - lborder) + lborder);
	};

	Point createRandomPoint()
	{
		return { randNumber(-BORDER, BORDER), randNumber(-BORDER, BORDER) };
	};

	rabid::vector < rabid::shared_ptr< Shape > > generateRandomShapes(size_t size)
	{
		rabid::vector < rabid::shared_ptr< Shape > > ofShapes(size);

		for (auto& i : ofShapes)
		{
			int a = rand() % 3;
			int col = rand() % 9;
			switch (a)
			{
			case 0:
				i = (rabid::shared_ptr< Shape >)new Circle(createRandomPoint(), randNumber(1, RBORDER), Shape::ofColours[col]);
				break;
			case 1:
				i = (rabid::shared_ptr< Shape >)new Pentagon(createRandomPoint(),
					createRandomPoint(),
					createRandomPoint(),
					createRandomPoint(),
					createRandomPoint(),
					Shape::ofColours[col]);
				break;
			case 2:
				i = (rabid::shared_ptr< Shape >)new RegularPentagon(createRandomPoint(), randNumber(1, RBORDER), Shape::ofColours[col]);
				break;
			default:
				break;
			}
		}
		return ofShapes;
	};
}