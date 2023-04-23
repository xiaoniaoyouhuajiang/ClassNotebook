
#include <iostream>

#include <conio.h>

#include <locale>

#include "figure.h"

#include "rectangle.h"


#include "5angle.h"
#include "pentagram.h"

#include <cmath>

#define PI 3.14159265358979323846
using namespace std;
int main()

{

	setlocale(LC_ALL, "russian");

	while (true)

	{

		int choice = 0;

		cout << "Выберите действие: " << endl;

		cout << "1.Задать прямоугольник" << endl;

		cout << "2.Задать  пятиугольник" << endl;

		cout << "3.Задать пентаграмму" << endl;

		cout << "4.Выход" << endl;

		cin >> choice;

		switch (choice)

		{

		case 1:

		{
			
			Rectangle rectangle(10, 20);
			//Figure* rectangle = new Rectangle(10, 20, "green");

			rectangle.print(cout);
			

			cout << "поворот" << endl;

			rectangle.turn(90 * PI / 180);

			rectangle.print(cout);

			cout << "установили новые длиныы сторон" << endl;

			rectangle.set_length(5, 10);

			rectangle.print(cout);

			cout << "изменили длиныы сторон" << endl;

			rectangle.scale(10);

			rectangle.print(cout);

			cout << "сдвинули фигуру" << endl;

			rectangle.sdvig(10, 10);

			rectangle.print(cout);
			
			rectangle.distance(100, 100);

			rectangle.print(cout);

		   _getch();

			system("cls");

			break;

		}

		case 2:

		{

			Pentagon pentagon(-2,-3,-2,4,0,5,2,4,2,-3);

			pentagon.print(cout);

			pentagon.turn(180*PI/180);

			pentagon.print(cout);

			pentagon.turn(60 * PI / 180);

			pentagon.print(cout);
			

			pentagon.scale(2);

			pentagon.print(cout);

			pentagon.sdvig(10, 10);

			pentagon.print(cout);

			pentagon.distance(100,100);

			pentagon.print(cout);
			_getch();

			system("cls");

			break;

		}

		case 3:

		{

			Pentagram pentagram(-2, -3, -2, 4, 0, 5, 2, 4, 2, -3);

			pentagram.print(cout);

			pentagram.turn(30 * PI / 180);

			pentagram.print(cout);

			pentagram.turn(60 * PI / 180);

			pentagram.print(cout);

			

			pentagram.scale(2);

			pentagram.print(cout);

			pentagram.sdvig(10, 10);

			pentagram.print(cout);

			pentagram.distance(100,100);

			pentagram.print(cout);

			_getch();

			system("cls");

			break;

		}

		case 4: exit(0);

		default:break;

		}

	}

}