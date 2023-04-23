// oop_lab_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#define _USE_MATH_DEFINES
#include <math.h> // число pi
#include "shape.h"
#include "circle.h"
#include "ellipse.h"
#include "ellipse_sector.h"


using namespace std;

int main()
{
	//const double M_PI = 3.14;
	cout << "============================================\n";
	cout << "Creating array of base class pointers, point them on every class and rotating:\n\n";
	Shape* sh_arr[3];
	sh_arr[0] = new Circle(2, { 0,0 });
	cout << "Creating circle:\n" << *(sh_arr[0]) << endl;
	sh_arr[0]->rotate(M_PI / 2);
	cout << "Rotating:\n" << *(sh_arr[0]) << endl;
	delete sh_arr[0];
	sh_arr[1] = new Ellipse(6, 4, { 0,0 });
	cout << "Creating ellipse:\n" << *(sh_arr[1]) << endl;
	sh_arr[1]->rotate(M_PI / 2);
	cout << "Rotating:\n" << *(sh_arr[1]) << endl;
	sh_arr[2] = new Ellipse_Sector({ 4, M_PI / 2 }, { 2, 0 }, { 0,0 });
	cout << "Creating ellipse sector:\n" << *(sh_arr[2]) << endl;
	sh_arr[2]->rotate(M_PI / 2);
	cout << "Rotating:\n" << *(sh_arr[2]) << endl;

	cout << "============================================\n";

	return 0;
}
