#include "my_shared_ptr.h"
#include "my_vector.h"
#include "oop_lr2.h"
#include <iostream>
#include <ctime>
#include <algorithm>

unsigned GenColor()
{
	return rand() % 6;
}

float GenNum()
{
	float r = ((float) rand() / RAND_MAX)*5 + 1; 
	r = ((int)(r*10 + 0.5))/10.0;
	return r;
}

Point GenerationPoint()
{
	Point point(rand() % 20 - 10, rand() % 20 - 10);
	return point;
}

stepik::shared_ptr<Shape> GenerationEllipse()
{
	stepik::shared_ptr<Shape> x(new Ellipse(GenerationPoint(), GenNum(), GenNum()));
	return x;
}

void GenCoordforTrap(Point &topLeft, Point &bottomLeft)
{
	topLeft = GenerationPoint();
	bottomLeft = GenerationPoint();			
}

stepik::shared_ptr<Shape> GenerationTrapezium()
{
	Point topLeft(0, 0), bottomLeft(0, 0);
	do
	{
		GenCoordforTrap(topLeft, bottomLeft);
	}
	while((topLeft.x == bottomLeft.x) && (topLeft.y == bottomLeft.y));
	stepik::shared_ptr<Shape> x(new Trapezium(topLeft, bottomLeft, GenNum(), GenNum()));
	return x;
}

stepik::shared_ptr<Shape> GenerationIsoscelesTrapezium()
{
	Point topLeft(0, 0), bottomLeft(0, 0);
	float bottomBase;
	do
	{
		GenCoordforTrap(topLeft, bottomLeft);
		bottomBase = GenNum();
	}
	while (((-2 * topLeft.x + bottomBase + 2 * bottomLeft.x) <= 0) || ((topLeft.x == bottomLeft.x) && (topLeft.y == bottomLeft.y)));
	stepik::shared_ptr<Shape> x(new IsoscelesTrapezium(topLeft, bottomLeft, bottomBase));
	return x;
}

stepik::vector<stepik::shared_ptr<Shape>> GenerationVector(unsigned size)
{
	stepik::vector<stepik::shared_ptr<Shape>> shapes;
	for (unsigned i = 0; i < size; i++)
	{
		stepik::shared_ptr<Shape> x;
		int k = rand() % 3 + 1;
		switch (k)
		{
		case 1:
			x = GenerationEllipse();
			break;
		case 2:
			x = GenerationTrapezium();
			break;
		case 3:
			x = GenerationIsoscelesTrapezium();
			break;
		}
		x->setColor(GenColor());
		shapes.push_back(x);
	}
	return shapes;
}


//ищет первые 2 эквивалентных элемента по полю цвет
//возвращает true, если были найдены
//если были найдены - во втором аргументе окажется shared_ptr<Shape> на первый элемент из найденной пары
bool SearchforEqualinColor(stepik::vector<stepik::shared_ptr<Shape>> shapes, stepik::shared_ptr<Shape> &foundEqual) 	
{
	int i;
	for (i = 0; i < shapes.size() - 2; i++)
	{
		if (shapes[i]->getColor() == shapes[i + 1]->getColor())
		{
			foundEqual = shapes[i];
			return true;
		}
	}
	foundEqual = shapes[i + 1];
	return false;
}


//создает упорядоченное объединение двух диапазонов dip1 и dip2
stepik::vector<stepik::shared_ptr<Shape>> UniontwoDiapazons(stepik::vector<stepik::shared_ptr<Shape>> dip1, stepik::vector<stepik::shared_ptr<Shape>> dip2)
{
	stepik::vector<stepik::shared_ptr<Shape>> result(dip1.size() + dip2.size());
	std::copy(dip1.begin(), dip1.end(), result.begin());
	std::copy(dip2.begin(), dip2.end(), result.begin() + dip1.size());

	std::sort(dip1.begin(), dip1.end(), [](const stepik::shared_ptr<Shape> & a, const stepik::shared_ptr<Shape> & b) -> bool
	{ 
		return a->Perimeter() < b->Perimeter(); 
	});

	std::sort(dip2.begin(), dip2.end(), [](const stepik::shared_ptr<Shape> & a, const stepik::shared_ptr<Shape> & b) -> bool
	{ 
		return a->Perimeter() < b->Perimeter(); 
	});
	
	stepik::vector<stepik::shared_ptr<Shape>>::iterator it = (std::set_union(dip1.begin(), dip1.end(), dip2.begin(), dip2.end(), result.begin(), 
	[](const stepik::shared_ptr<Shape> & a, const stepik::shared_ptr<Shape> & b) -> bool
	{ 
		return a->Perimeter() < b->Perimeter(); 
	}));

	result.resize(it - result.begin());
	
	return result;
}

//создает упорядоченное объединение двух диапазонов (берет 2 указанных диапазона из вектора - первого аргумента)
stepik::vector<stepik::shared_ptr<Shape>> UniontwoDiapazons(stepik::vector<stepik::shared_ptr<Shape>> shapes, int min1, int max1, int min2, int max2)
{
	if ((max1 < min1) || (max2 < min2) || (min1 < 0) || (min2 < 0) || (max2 > shapes.size()) || (max1 > shapes.size()))
		throw std::invalid_argument("No such diapazone in vector!");
	stepik::vector<stepik::shared_ptr<Shape>> dip1(max1 - min1 );
	std::copy(shapes.begin() + min1, shapes.begin() + max1, dip1.begin());

	stepik::vector<stepik::shared_ptr<Shape>> dip2(max2 - min2 );
	std::copy(shapes.begin() + min2, shapes.begin() + max2, dip2.begin());
	
	return UniontwoDiapazons(dip1, dip2);
}
