#include "AlgorithmsForShapes.h"
#include <string>

stepik::vector<shared_ptr<Shape>> generateFigures(int size)
{
	stepik::vector<shared_ptr<Shape>> vect_a(size);

	for (int i = 0; i < size; i++)
	{
		int figureType = rand() % 3;
		switch (figureType)
		{
			case 0:
			{
				vect_a[i] = shared_ptr<Shape>(new Rectangle({ 0,0 }, 20, 10));
				break;
			}
			case 1:
			{
				vect_a[i] = shared_ptr<Shape>(new Circle({ 0,0 }, 4));
				break;
			}
			case 2:
			{
				vect_a[i] = shared_ptr<Shape>(new Trapeze({ 2, 6 }, { 7, 6 }, { 8, 0 }, { 0,0 }));
				break;
			}
		}

	}
	return vect_a;
}


int compareFiguresByName(const void * x1, const void * x2)
{
	return typeid((*(*(shared_ptr<Shape>*)x1))).name() - typeid((*(*(shared_ptr<Shape>*)x2))).name();
}

// Проверка двух упорядоченных диапазонов на равенство по определенному критерию
// Упорядоченные диапазоны по имени
// Проверка диапазонов на совпадение имен фигур
bool isSimiliarRegion(Region r1, Region r2, const stepik::vector<shared_ptr<Shape>>& vect_a)
{
	stepik::vector<shared_ptr<Shape>> a(vect_a.begin() + r1.start, vect_a.begin() + r1.finish);
	stepik::vector<shared_ptr<Shape>> b(vect_a.begin() + r2.start, vect_a.begin() + r2.finish);

	qsort(&a[0], a.size(), sizeof(shared_ptr<Shape>), compareFiguresByName);
	qsort(&b[0], b.size(), sizeof(shared_ptr<Shape>), compareFiguresByName);

	for (int i = 0; i < a.size(); i++)
	{
		string name1 = typeid(*a[i]).name();
		string name2 = typeid(*b[i]).name();
		if (name1 != name2)
			return false;
	}

	return true;
}

// Упорядочить элементы, пока первые n элементов не будут следовать в требуемом порядке.
// Критерий - увеличение площади фигур
void sortFirstNElements(stepik::vector<shared_ptr<Shape>>& vect_a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < vect_a.size(); j++)
		{
			if ((*vect_a[i]).getSquare() >= (*vect_a[j]).getSquare())
			{
				std::swap(vect_a[i], vect_a[j]);
			}
		}
	}
}

void printVector(const stepik::vector<shared_ptr<Shape>>& vect_a)
{
	for (int i = 0; i < vect_a.size(); i++)
		cout << i << " Figure Square: " << (*vect_a[i]).getSquare() << "\n";
}

void print2Vectors(const stepik::vector<shared_ptr<Shape>>& a, const stepik::vector<shared_ptr<Shape>>& b)
{
	for (int i = 0; i < a.size(); i++)
	{
		double square1 = (*a[i]).getSquare();
		double square2 = (*b[i]).getSquare();
		cout << i << ":\n 1 Figure Square: " << square1 << "\n" << " 2 Figure Square: " << square2 << "\n\n";
	}
}
