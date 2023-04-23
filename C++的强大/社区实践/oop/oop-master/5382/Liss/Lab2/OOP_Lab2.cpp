// OOP_Lab2.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "string"
#include <conio.h>
#include "Shape.h"
#include "Pentagon.h"
#include "Segment.h"
#include "Ellips.h"
#include "iostream"
using namespace std;

int main()
{
	while (true)
	{
		int choice = 0;
		cout << "Chose the number: " << endl;
		cout << "1.Information about segment" << endl;
		cout << "2.Information about pentagon" << endl;
		cout << "3.Information about ellips" << endl;
		cout << "4.Exit" << endl;

		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			Segment A (0, 0, 3, 2.0, 60, "pink");
			Segment B(1, 1, 3, 3.0, 35,"pink");
			cout << A <<B;
			_getch();
			system("cls");
			break;
		}
		case 2:
		{
			Pentagon B(0, 0, 3, 4.0, 45, "pink");
			cout <<  B ;
			_getch();
			system("cls");
			break;
			}
		case 3:
			{
			Ellips C(0, 3, 3, 4, 3.0, 90, "pink");
			cout <<C;
			_getch();
			system("cls");
			break;
			}
			case 4: exit(0);
			default:break;
			}
			}
	
	system("pause");
	return 0;
}

