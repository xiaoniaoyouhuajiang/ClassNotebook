#include <iostream>
#include <cstdlib>
#include <math.h>
#include <random>
#include <ctime>
#include <algorithm>
#include "Shape.h"
#include "Ellipse.h"
#include "Parallelogram.h"
#include "SectorEllipse.h"
#include "Vector.h"
#include "Shared_ptr.h"
#define TestNumber 1000

using namespace std;

int GenerateRandom(int xmin, int xmax) {
	//xmin - от включительно, xmax - до включительно
	return rand() % (xmax - xmin + 1) + xmin;
}

void generateTest(stepik::vector<stepik::shared_ptr<Shape>>& test) {
	double x0 = 0.0;
	double y0 = 0.0;
	double a = 0.0;
	double b = 0.0;
	double angle1 = 0.0;
	double angle2 = 0.0;
	stepik::shared_ptr<Ellipse>* E=NULL;
	stepik::shared_ptr<SectorEllipse>* SE=NULL;
	stepik::shared_ptr<Parallelogram>* P=NULL;
	int colour = 0;
	vector<string> Colours {"White", "Yellow", "Red", "Blue", "Green", "Black", "Pink", "Orange", "Purple", "Gray"};

	for (int i = 0; i < TestNumber; i++) {//цикл инициализации 1000 фигур
		x0 = GenerateRandom(-10, 10) + (double)GenerateRandom(0, 9) / 10;
		y0 = GenerateRandom(-10, 10) + (double)GenerateRandom(0, 9) / 10;
		a = GenerateRandom(1, 20)+ (double)GenerateRandom(0, 9)/10;
		b = GenerateRandom(1, 20) + (double)GenerateRandom(0, 9) / 10;
		colour = GenerateRandom(0, 9);
		//выбор фигуры из 3
		switch (GenerateRandom(1, 3)) {
		case 1:
			E = new stepik::shared_ptr<Ellipse>(new Ellipse(x0, y0, a, b, Colours[colour]));
			test.push_back(*E);
			delete E;
			break;
		case 2:
			angle1 = GenerateRandom(0, 180);
			angle2 = GenerateRandom(0, 180);
			SE = new stepik::shared_ptr<SectorEllipse>(new SectorEllipse(x0, y0, a, b, angle1, angle2, Colours[colour]));
			test.push_back(*SE);
			delete SE;
			break;
		case 3:
			angle1 = GenerateRandom(0, 180);
			P = new stepik::shared_ptr<Parallelogram>(new Parallelogram(x0, y0, a, b, angle1, Colours[colour]));
			test.push_back(*P);
			delete P;
			break;
		}
	}
}

bool compareRanges(stepik::vector<stepik::shared_ptr<Shape>>& test, int n1, int n2, int size) {
	bool answer = true;
	int index1 = n1;
	int index2 = n2;
	while ((index1 != n1 + size) && (index2 != n2 + size) && (answer)) {
		if (!test[index1]->compareCentre(test[index2].get()))
			answer = false;
		index1++;
		index2++;
	}

	return answer;
}

void SortRanges(stepik::vector<stepik::shared_ptr<Shape>>& association) {
	sort(association.begin(), association.end(), [](stepik::shared_ptr<Shape> a, stepik::shared_ptr<Shape> b) {//сортируем по возрастанию величин потоков
		if (a->getX0() == b->getX0())
			return a->getY0() < b->getY0();
		return a->getX0() < b->getX0();
	});
}

int main()
{
	int n1, n2, size;
	stepik::vector<stepik::shared_ptr<Shape>> test;//вектор с тестами
	stepik::vector<stepik::shared_ptr<Shape>> association;//вектор для объединения двух подмножеств
	srand(time(0));
	generateTest(test);//генерируем 1000 различных фигур

	n1 = GenerateRandom(0, TestNumber-2);
	n2 = GenerateRandom(0, TestNumber-2);
	//n2 = n1;
	size = GenerateRandom(1, TestNumber - 1 - max(n1, n2));

	for (int i = 0; i < test.size(); i++) {
		test[i]->printCentre();
	}
	cout << endl;

	//5.Проверка двух неупорядоченных диапазонов на равенство по определенному критерию.
	cout << "Check the figures on the equality of the coordinates of the center from ranges:" << endl <<"[" <<n1+1 << "," << n1 + size << "]  and  [" << n2+1 <<","<< n2 + size <<"]"<< endl<<endl;
	if (compareRanges(test, n1, n2, size))
		cout << "The figures of the two range have the same coordinates of the centers!" << endl<<endl;
	else
		cout << "The figures from the ranges have different coordinates of the centers!" << endl<<endl;

	//4.Создать упорядоченное объединение двух диапазонов.
	for (int i = n1; i < n1 + size; i++) {
		association.push_back(test[i]);
	}

	for (int i = n2; i < n2 + size; i++) {
		if(test[i].use_count()==1)
			association.push_back(test[i]);
	}

	SortRanges(association);//сортировка по возрастанию координат, если х равны, то сортируется по y

	cout << "The two bands were combined into one!" << endl << "Sorted by coordinates of the centre:" << endl;
	for (int i = 0; i < association.size(); i++) {
		association[i]->printCentre();
	}
	cout << endl;

	system("pause");
	return 0;
}