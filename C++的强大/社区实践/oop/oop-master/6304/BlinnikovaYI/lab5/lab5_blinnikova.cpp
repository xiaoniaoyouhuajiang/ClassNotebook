// lab5_blinnikova.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Square.h"
#include "Shape.h"
#include "Shared_ptr.cpp"
#include "Vector.cpp"
#include <ctime>
#include <cstdlib>
#define NumberOfShapes 7
#define ValueRange 50
#define n 4

void generateShapes(stepik::vector<shared_ptr<Shape>>& Shapes)
{
	srand(time(NULL));
	for (shared_ptr<Shape> &shape : Shapes)
	{
		int object = rand() % 3;
		switch (object)
		{
			//Isosceless triangle
		case 0:
		{
			shape.reset(new Ellipse({ (double)rand() / ValueRange, (double)rand() / ValueRange }, rand() % ValueRange, rand() % ValueRange));
			break;
		}
		//Square
		case 1:
		{
			shape.reset(new Square({ (double)rand() / ValueRange, (double)rand() / ValueRange }, (double)rand() / ValueRange));
			break;
		}
		case 2:
		{
			shape.reset(new Rectangle({ (double)rand() / ValueRange, (double)rand() / ValueRange }, rand() % ValueRange, rand() % ValueRange));
			break;
		}
		}
	}
}

//проверка на определенные свойства
bool properties(Shape& shape) {
	if (shape.getCenter().x > 150 && shape.getCenter().y > 150) {
		return true;
	}
	return false;
}

//Поиск первых n последовательных элементов с определенными свойствами.
void findFirstNShapeByProperties(stepik::vector<shared_ptr<Shape>> shapes, stepik::vector<shared_ptr<Shape>> &boxShapes)
{
	int res = 0;
		for (shared_ptr<Shape> &shape : shapes)
	{
		if (properties(*shape) && res < n) {
			boxShapes.push_back(shape);
			res++;
		}
	}
}

//Скопировать элементы, удовлетворяющие критерию.
void copyElemByProperties(stepik::vector<shared_ptr<Shape>> shapes,stepik::vector<shared_ptr<Shape>> &boxShapes)
{
	int res = 0;
	for (shared_ptr<Shape> &shape : shapes)
	{
		if (properties(*shape)) {
			boxShapes.push_back(shape);
		}
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");

	stepik::vector<shared_ptr<Shape>> shapes(NumberOfShapes);

	generateShapes(shapes);

	for each (shared_ptr<Shape> shape in shapes)
	{
		cout << *shape << endl;
	}
	cout << "**********************************************" << endl;
	stepik::vector<shared_ptr<Shape>> boxShapes;
	

	cout << "after findFirstNShapeByProperties" << endl;
	findFirstNShapeByProperties(shapes, boxShapes);
	for(shared_ptr<Shape> &shape : boxShapes)
	{
		cout << *shape << endl;
	}

	cout << "***********************************************" << endl;
	stepik::vector<shared_ptr<Shape>> boxShapes2;
	copyElemByProperties(shapes, boxShapes2);
	cout << "after copyElemByProperties" << endl;
	for (shared_ptr<Shape> &shape : boxShapes2)
	{
		cout << *shape << endl;
	}
	return 0;
}

