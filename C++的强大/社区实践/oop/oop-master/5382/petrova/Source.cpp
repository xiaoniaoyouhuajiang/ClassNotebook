
#include "string"
#include <locale>
#include "Shape.h"
#include "iostream"

using namespace std;
double x, y;


/*void coor()
{
	cout << "Введите координаты x и y :\n";
	cout << "x = ";
	cin >> x;
	cout << "y = ";
	cin >> y;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int choice = 0;
	while (true)
	{
		cout << "Выберите действие: " << endl;
		cout << "1.Вывести информацию об эллипсе" << endl;
		cout << "2.Вывести информацию о сегменте эллипса" << endl;
		cout << "3.Вывести информацию о параллелограмме" << endl;
		cout << "4.Выход" << endl;

		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			int R, r;
			coor();
			Point center = { x,y };
			cout << "Введите больший радиус эллипса: ";
			cin >> R;
			cout << "Введите меньший радиус эллипса: ";
			cin >> r;
			Ellips E(center, R, r);
			cout << "Введите координаты центра эллипса: ";
			Point new_center = { 2,3 };
			E.move(new_center);
			cout << "Введите цвет: ";
			my_color color = { 0.2, 0.7, 0.4 };
			cout << "Измените размер эллипса: ";
			E.changesize(3);
			system("cls");
		}
		case 2:
		{
			int  x1, x2, y1, y2;
			coor();
			Point center = { x,y };
			cout << "Введите координаты левого конца: ";
			cin >> x1;
			cin >> y1;
			Point left = { x1,y1 };
			cout << "Введите координаты правого конца: ";
			cin >> x2;
			cin >> y2;
			Point right = { x2,y2 };
			SegEl S(center, left, right);
			system("cls");

		}
		case 3:
		{
			int l, L;
			coor();
			Point center = { x,y };
			cout << "Введите расстояние от центра до вершин : ";
			cin >> l;
			cin >> L;
			Parallelogramm P(center, l, L);
			system("cls");

		}
		case 4: exit(0);
		default:break;
		}
	}

	system("pause");
	return 0;
} */

