#pragma once
#include <string>
#include "base.h"
#include <iostream>
#include <math.h>
using namespace std;
typedef unsigned int unInt;

class Square:public Shape
{   public:
         Square(){
			 this->Centre = Point(0,0);
			 this->Vertex[0] = Point(1,1);
			 for(int i=1;i<4;i++){
				 double R=90;
				 Vertex[i] = Turnus(R,Vertex[i-1], Centre);}
        };

        Square(const Point& centre,const Point& vertex1)
        {   
			double angle=90;
	        cout << "квадрат\n";
	        this->Centre = centre;
	        this->Vertex[0] = vertex1;
			for(int i =1;i<4 ;i++){
	           this-> Vertex[i]=Turnus(angle,this->Vertex[i-1],Centre);
	       
	        
		      
	        }
        }


		~Square(){cout << "квадрат\n";}
};

