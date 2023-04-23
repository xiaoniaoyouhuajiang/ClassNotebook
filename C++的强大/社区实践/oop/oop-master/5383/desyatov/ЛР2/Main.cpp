#include <iostream>
#include <cmath>
#include <string>
#include "EqualTrapezium.h"
#include "Ellipse.h"
using namespace std;
/*
class Point
{
public:
	int x;
	int y;
	
	Point() //Дефолтный констуктор
	{
		x = 0;
		y = 0;
	}
	
	Point(int x0, int y0) //Установить точки пользователя
	{
		x = x0;
		y = y0;
	}

	void show_Point() // Показать точки
	{
		cout << "Координаты точки x = " << x << endl;
		cout << "Координаты точки y = " << y << endl;
	}
};

class Shape
{
public:

	virtual void ShowFigure()= 0; //Показать
	virtual void Move(int x, int y) = 0;
	virtual void ChangeScale(int n) = 0;
	virtual void ChangeColor(string color) = 0;
};

class Trapezium : public Shape
{
public:
	
	Point a1;
	Point a2;
	Point a3;
	Point a4;
	string color = "Красный";
	string type = "Трапеция";

	void ChangeColor(string c) //Поменять цвет
	{
		color = c;
		cout << "Цвет был изменен на " << c;
	}

	void SetPoint(int x, int y, int num)
	{
		switch (num)
		{
		case 1:
		a1 = Point(x,y); // A
		case 2:
		a2 = Point(x, y); // B
		case 3:
		a3 = Point(x, y); // C
		case 4:
		a4 = Point(x, y); // D
		}
	}

	void check()
	{
		int tmp;
		if (a1.x > a2.x) //Проверка A и B
		{
			tmp = a2.x;
			a2.x = a1.x;
			a1.x = tmp;
		}
		if (a3.y > a2.y) //Проверка C и В
		{
			tmp = a2.y;
			a2.y = a3.y;
			a3.y = tmp;
		}
		if (a4.x > a3.x) //Проверка C и D
		{
			tmp = a3.x;
			a3.x = a4.x;
			a4.x = tmp;
		}
		if (a4.y > a1.y) //Проверка D и A
		{
			tmp = a1.y;
			a1.y = a4.y;
			a4.y = tmp;
		}
	    double k1, k2;
		k1 = (a2.y - a1.y)/(a2.x - a1.x); //Угловой коэффицент отрезка AB
		k2 = (a4.y - a3.y)/(a4.x - a3.x); //Угловой коэффицент отрезка CD
		if (k1 != k2)
		{
			k1 = (a3.y - a2.y)/(a3.x - a2.x); //Угловой коэффицент отрезка CB
			k2 = (a4.y - a1.y)/(a4.x - a1.x); //Угловой коэффицент отрезка AD
			if (k1 != k2)
			{
				cout << "Введенная фигура не является трапецией!" << endl;
			}
		}
		else
		cout << "Введенная фигура является трапецией." << endl;
	}

	void ShowPoints()
	{
		cout << "Точка А: " << endl;
		a1.show_Point(); //1 - левая верхняя
		cout << "Точка B: " << endl;
		a2.show_Point(); //2 - правая верхняя
		cout << "Точка C: " << endl;
	    a3.show_Point(); //3 - правая нижняя
		cout << "Точка D: " << endl;
		a4.show_Point(); //4 - левая нижняя
	}

	void Move(int x, int y)
	{
		a1.x = a1.x + x;
		a2.x = a2.x + x;
		a3.x = a3.x + x;
		a4.x = a4.x + x;

		a1.y = a1.y + y;
		a2.y = a2.y + y;
		a3.y = a3.y + y;
		a4.y = a4.y + y;
		cout << "Трапеция была подвинута " << endl;
	}

	void ChangeScale(int n)
	{
		a1.x = a1.x * n;
		a2.x = a2.x * n;
		a3.x = a3.x * n;
		a4.x = a4.x * n;

		a1.y = a1.y * n;
		a2.y = a2.y * n;
		a3.y = a3.y * n;
		a4.y = a4.y * n;
		cout << "Масштаб фигуры был изменен в " << n << " раз " << endl;
	}

	void ShowFigure()
	{
		cout << "Тип фигуры - " << type << endl;
		cout << "Цвет фигуры - " << color << endl;
		ShowPoints();
	}
};

class EqualTrapezium : public Trapezium //Равнобедренная трапеция
{
public:
	string type = "Равнобедренная трапеция";
	void check()
	{
		int tmp;
		if (a1.x > a2.x) //Проверка A и B
		{
			tmp = a2.x;
			a2.x = a1.x;
			a1.x = tmp;
		}
		if (a3.y > a2.y) //Проверка C и В
		{
			tmp = a2.y;
			a2.y = a3.y;
			a3.y = tmp;
		}
		if (a4.x > a3.x) //Проверка C и D
		{
			tmp = a3.x;
			a3.x = a4.x;
			a4.x = tmp;
		}
		if (a4.y > a1.y) //Проверка D и A
		{
			tmp = a1.y;
			a1.y = a4.y;
			a4.y = tmp;
		}
		double k1, k2, l1, l2;
		k1 = (a2.y - a1.y) / (a2.x - a1.x); //Угловой коэффицент отрезка AB
		k2 = (a4.y - a3.y) / (a4.x - a3.x); //Угловой коэффицент отрезка CD
		if (k1 != k2)
		{
			k1 = (a3.y - a2.y) / (a3.x - a2.x); //Угловой коэффицент отрезка CB
			k2 = (a4.y - a1.y) / (a4.x - a1.x); //Угловой коэффицент отрезка AD
			if (k1 != k2)
			{
				cout << "Введенная фигура не является равнобедренной трапецией!" << endl;
				exit(1);
			}
			else //Если AB и CD параллельны, проверяем другие две стороны на равенство
			{
				l1 = sqrt(((a2.x - a1.x)*(a2.x - a1.x)) + ((a2.y - a1.y)*(a2.y - a1.y)));
				l2 = sqrt(((a3.x - a4.x)*(a3.x - a4.x)) + ((a3.y - a4.y)*(a3.y - a4.y)));
				if (l1 != l2)
				{
					cout << " Введная фигура не является равнобедренной трапецией!" << endl;
					exit(1);
				}
			}
		}
		l1 = sqrt(((a4.x - a1.x)*(a4.x - a1.x)) + ((a4.y - a1.y)*(a4.y - a1.y)));
		l2 = sqrt(((a3.x - a2.x)*(a3.x - a2.x)) + ((a3.y - a2.y)*(a3.y - a2.y)));
		if (l1 != l2)
		{
			cout << "Введеная фигура не является равнобедренной трапецией! " << endl;
			exit(1);
		}

	};
};
*/
int main()
{
	setlocale(LC_ALL, "Russian");
	int x, y, n;
	string colornew;
	int num = 1;
	int var = 0;
	char par[5] = "ABCD";
	cout << "Введите тип создаваемой фигуры (1 - трапеция, 2 - равнобедренная трапеция, 3 - эллипс. " << endl;
	cin >> var;
	if (var == 1)
	{
		Trapezium trap;
		while (num != 5)
		{
			cout << "Введите координаты  точки " << par[num - 1] << endl;
			cout << "(A - левая верхняя, B - правая верхняя, C - правая нижняя , D - левая нижняя)" << endl;
			cout << "x = ";
			cin >> x;
			cout << "y = ";
			cin >> y;
			//Передать
			trap.SetPoint(x, y, num);
			num++;
		}
		trap.check();
		trap.ShowPoints();
		while (var != 0)
		{
			cout << endl << "Выберите действие:" << endl << "1.Подвинуть фигуру на x или y" << endl;
			cout << "2.Изменить масштаб " << endl << "3.Изменить цвет " << endl << "4.Показать параметры " << endl << "0. для выхода " << endl;
			cin >> var;
			switch (var)
			{
			case 1:
				cout << "Введите х и у на которые нужно подвинуть " << endl;
				cout << "X = ";
				cin >> x;
				cout << endl << "Y = ";
				cin >> y;
				trap.Move(x, y);
				trap.ShowPoints();
				break;
			case 2:
				cout << "Введите во сколько нужно увеличить " << endl;
				cin >> n;
				trap.ChangeScale(n);
				break;
			case 3:
//				cout << "Введите цвет (сейчас цвет " << trap.color << " )" << endl;
				cin >> colornew;
				trap.ChangeColor(colornew);
				break;
			case 4:
				trap.ShowFigure();
				break;
			case 0:
				exit(1);
			}
		}
	}
	if (var == 2)
	{
		EqualTrapezium Etrap;
		while (num != 5)
		{
			cout << "Введите координаты  точки " << par[num - 1] << endl;
			cout << "(A - левая верхняя, B - правая верхняя, C - правая нижняя , D - левая нижняя)" << endl;
			cout << "x = ";
			cin >> x;
			cout << "y = ";
			cin >> y;
			//Передать
			Etrap.SetPoint(x, y, num);
			num++;
		}
		Etrap.check();
		Etrap.ShowPoints();
		while (var != 0)
		{
			cout << endl << "Выберите действие:" << endl << "1.Подвинуть фигуру на x или y" << endl;
			cout << "2.Изменить масштаб " << endl << "3.Изменить цвет " << endl << "4.Показать параметры " << endl << "0. для выхода " << endl;
			cin >> var;

			switch (var)
			{
			case 1:
				cout << "Введите х и у на которые нужно подвинуть " << endl;
				cout << "X = ";
				cin >> x;
				cout << endl << "Y = ";
				cin >> y;
				Etrap.Move(x, y);
				Etrap.ShowPoints();
				break;
			case 2:
				cout << "Введите во сколько нужно увеличить " << endl;
				cin >> n;
				Etrap.ChangeScale(n);
				break;
			case 3:
//				cout << "Введите цвет (сейчас цвет " << Etrap.color << " )" << endl;
				cin >> colornew;
				Etrap.ChangeColor(colornew);
				break;
			case 4:
				Etrap.ShowFigure();
				break;
			case 0:
				exit(1);
			}
		}
	}

	if (var == 3)
	{
		Ellipse trap;

		cout << "Введите координаты цента " << endl;
	}
}