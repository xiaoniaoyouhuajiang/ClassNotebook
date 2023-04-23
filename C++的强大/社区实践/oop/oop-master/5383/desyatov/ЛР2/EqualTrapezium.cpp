#include "EqualTrapezium.h"
#include <iostream>

using namespace std;

EqualTrapezium::EqualTrapezium()
{
	type = "Равнобедренная трапеция";
	color = "Красный";
	scale = 0;
}

EqualTrapezium::EqualTrapezium(double lBot, double lTop, double hight)
{
	area = ((lBot + lTop) *hight / 2);
}


void EqualTrapezium::check()
{
	double tmp;
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
	cout << "Введенная фигура является равнобедренной трапецией " << endl;
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
	//equalTrapeziumArea = ((lenghtBottom + lenghtTop) *hight) / 2;
}

EqualTrapezium::~EqualTrapezium()
{

}

double EqualTrapezium::compareAreas(EqualTrapezium etrap1, EqualTrapezium etrap2)
{
	if (etrap1.area> etrap2.area)
	{
		return 1;
		cout << "Площадь первой фигуры больше второй " << endl;
	}
	if (etrap1.area < etrap2.area)
	{
		return 2;
		cout << "Площадь первой фигуры меньше второй " << endl;
	}
	if (etrap1.area == etrap2.area)
	{
		return 3;
		cout << "Площади равны" << endl;
	}
}