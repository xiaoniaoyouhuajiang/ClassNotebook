#include "Trapezium.h"
#include <iostream>
using namespace std;


	void Trapezium::ChangeColor(string c) //Поменять цвет
	{
		color = c;
		cout << "Цвет был изменен на " << c;
	}

	Trapezium::Trapezium()
	{
		type = "Трапеция";
		color = "Красный";
		scale = 0;
	}

	Trapezium::Trapezium(double lenghtTop, double h, double lenghtBottom)
	{
		area = ((lenghtBottom + lenghtTop) * h) / 2;
	}

	void Trapezium::SetPoint(double x, double y, int num)
	{
		switch (num)
		{
		case 1:
			a1 = Point(x, y); // A
		case 2:
			a2 = Point(x, y); // B
		case 3:
			a3 = Point(x, y); // C
		case 4:
			a4 = Point(x, y); // D
		}
	}

	void Trapezium::check()
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
		k1 = (a2.y - a1.y) / (a2.x - a1.x); //Угловой коэффицент отрезка AB
		k2 = (a4.y - a3.y) / (a4.x - a3.x); //Угловой коэффицент отрезка CD
		if (k1 != k2)
		{
			k1 = (a3.y - a2.y) / (a3.x - a2.x); //Угловой коэффицент отрезка CB
			k2 = (a4.y - a1.y) / (a4.x - a1.x); //Угловой коэффицент отрезка AD
			if (k1 != k2)
			{
				cout << "Введенная фигура не является трапецией!" << endl;
				exit(1);
			}
		}
		else
		{
			cout << "Введенная фигура является трапецией." << endl;
			scale = 1;
			hight = a1.y - a4.y;
			lenghtBottom = a3.x = a4.x;
			lenghtTop = a2.x - a1.x;
			if (lenghtBottom > lenghtTop)
			{
				lenght = lenghtBottom;
			}
			else
				lenght = lenghtTop;

			center.x = lenght / 2;
			center.y = hight / 2;
			area = ((lenghtBottom + lenghtTop) *hight) / 2;
		}
	}

	void Trapezium::getArea()
	{
		area = ((lenghtBottom + lenghtTop) *hight) / 2; //площадь
	}
    
	double Trapezium::compareAreas(Trapezium trap1, Trapezium trap2)
	{
			if (trap1.area> trap2.area)
			{
				return 1;
				cout << "Площадь первой фигуры больше второй " << endl;
			}
			if (trap1.area < trap2.area)
			{
				return 2;
				cout << "Площадь первой фигуры меньше второй " << endl;
			}
			if (trap1.area == trap2.area)
			{
				return 3;
				cout << "Площади равны" << endl;
			}
	}

	void Trapezium :: ShowPoints()
	{
		cout << "Точка А: " << endl;
		a1.ShowPoint(); //1 - левая верхняя
		cout << "Точка B: " << endl;
		a2.ShowPoint(); //2 - правая верхняя
		cout << "Точка C: " << endl;
		a3.ShowPoint(); //3 - правая нижняя
		cout << "Точка D: " << endl;
		a4.ShowPoint(); //4 - левая нижняя
		cout << "Координаты центра: "  << endl;
		cout << "X = " << center.x << " " << "Y = " << center.y << endl;
	}

	void Trapezium::Move(double x, double y)
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

	void Trapezium::ChangeScale(int n)
	{
		lenghtBottom = lenghtBottom * n;
		lenghtTop = lenghtTop * n;
		hight = hight * n;
		a1.x = center.x + lenghtTop/2;
		a1.y = center.y + hight/2;
		a2.x = center.x + lenghtTop/2;
		a2.y = center.y + hight/2;
		a3.x = center.x + lenghtBottom/2;
		a3.y = center.y + hight/2;
		a4.x = center.x + lenghtBottom/2;
		a4.y = center.y + hight/2;

		scale = n;
		cout << "Масштаб фигуры был изменен на " << n << endl;
	}

	void Trapezium::ShowFigure()
	{
		cout << "Тип фигуры - " << type << endl;
		cout << "Цвет фигуры - " << color << endl;
		ShowPoints();
		cout << "Площадь фигуры = " << area << endl;
	}

	void Trapezium::ChangeAngle(double a)
	{
		int x0;

		x0 = a1.x;
		a1.x = a1.x * cos(a) - a1.y * sin(a);
		a1.y = x0 * sin(a) + a1.y * cos(a);

		x0 = a2.x;
		a2.x = a2.x * cos(a) - a2.y * sin(a);
		a2.y = x0 * sin(a) + a2.y * cos(a);

		x0 = a3.x;
		a3.x = a3.x * cos(a) - a3.y * sin(a);
		a3.y = x0 * sin(a) + a3.y * cos(a);

		x0 = a4.x;
		a4.x = a4.x * cos(a) - a4.y * sin(a);
		a4.y = x0 * sin(a) + a4.y * cos(a);
	}

	void Trapezium::print(ostream& output)
	{
		output << "Тип фигуры - " << type << endl;
		output << "Цвет фигуры - " << color << endl;
		ShowPoints();
	}
	Trapezium::~Trapezium()
	{

	}