#pragma once

#include "point.h"
#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

class Shape
{   protected:
        Point Centre;
	    Point Vertex[4];
	    string Color; 

    public:
        
        static  int ID;
        int Id;
	    Shape() 
		{   cout << "Создана фигура ";
		    Centre=(0,0);Vertex[0]=(1,1);Vertex[1]=(-1,1);Vertex[2]=(-1,-1);Vertex[3]=(1,-1);
			Color="Белый";
			Id = ID;
	        ID++;
		}//конструктор фигуры
		void printShape();//вывод информации
	    void move(const double& x,const double& y);//перемещение
	    void Mahtab(const double& P);// маштабирование
	    void Turn(const double& R);//поворот 
        void SetColorFigure(const string &color);//установка цвета
	    string  GetColorFigure();//вывод цвета
	    bool CommonSide(const Shape& shape2);//функция. определяющая, содержатся ли стороны одной фигуры в другой
		//вначале сравним уравнения прямых,
	    virtual ~Shape() { cout << "Удалена фигура ";}//деструктор фигуры
};






