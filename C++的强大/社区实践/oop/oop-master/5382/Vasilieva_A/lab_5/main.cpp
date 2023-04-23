#include "lab5.h"

int main()
{
	setlocale(LC_ALL, "rus");

	/*Создание списка из 1000 фигур и демонстрация работы предиката на нем*/ 

	list<shared_ptr<Shape>> rand_list = randList();
	sqTriangle unionWithIt1(Point(1, 3), Point(2, 2), 34.5);
	Shape *callShape = new Square(Point(0, 0), Point(0, 0));

	for (auto p : rand_list)
	{
		if (callShape->isUnionOf(unionWithIt1, *p))
		{
			cout << "Первая фигура из списка, которая является объединением с данной фигурой: " << endl;
			cout << *p << endl;
			break;
		}
	}

	list<shared_ptr<Shape>> l_true1;
	list<shared_ptr<Shape>> l_false1;
	for (auto p : rand_list)
	{
		if (callShape->isUnionOf(unionWithIt1, *p))
			l_true1.push_back(p);
		else
			l_false1.push_back(p);
	}
	cout << "Количество фигур из списка, являющихся объединением с данной фигурой: " << l_true1.size() << endl;
	cout << "Количество фигур из списка, неявляющихся объединением с данной фигурой: " << l_false1.size() << endl;
	
	cout << "--------------------------------------------------------------" << endl;
	/*Проверка. Создание списка из 6 фигур и демонстрация работы предиката на нем*/
	
	Shape *sq1 = new Square(Point(2, 3), Point(1, 2));
	cout << *sq1;
	Shape *sq2 = new Square(Point(1, 1), Point(0, 2));
	cout << *sq2;
	Shape *istr1 = new isosTriangle(Point(2, 3), Point(1, 2), 34.5);
	cout << *istr1;
	Shape *istr2 = new isosTriangle(Point(0, 3), Point(4, 1), 12);
	Shape *sqtr1 = new sqTriangle(Point(2, 3), Point(1, 2), 34.5);
	Shape *sqtr2 = new sqTriangle(Point(4, 7), Point(2, 5), 7);
	cout << *sq1;
	list<shared_ptr<Shape>> my_list;
	my_list.push_back(shared_ptr<Shape>(sq1));
	my_list.push_back(shared_ptr<Shape>(sq2));
	my_list.push_back(shared_ptr<Shape>(istr1));
	my_list.push_back(shared_ptr<Shape>(istr2));
	my_list.push_back(shared_ptr<Shape>(sqtr1));
	my_list.push_back(shared_ptr<Shape>(sqtr2));

	sqTriangle unionWithIt(Point(2, 3), Point(1, 2), 34.5);
	Shape *callShape1 = new Square(Point(0, 0), Point(0, 0));

	for (auto p : my_list) 
	{
		if (callShape1->isUnionOf(unionWithIt, *p))
		{ 
			cout << "Первая фигура из списка, которая является объединением с данной фигурой: " << endl;
			cout << *p << endl;
			break;
		}
	}

	list<shared_ptr<Shape>> l_true;
	list<shared_ptr<Shape>> l_false;
	for (auto p : my_list) 
	{
		if (callShape1->isUnionOf(unionWithIt, *p))
			l_true.push_back(p); 
		else
			l_false.push_back(p); 
	}
	cout << "Количество фигур из списка, являющихся объединением с данной фигурой: " << l_true.size() << endl;
	cout << "Количество фигур из списка, неявляющихся объединением с данной фигурой: " << l_false.size() << endl;

	return 0;
}