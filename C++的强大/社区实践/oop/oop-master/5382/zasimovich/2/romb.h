#pragma once
#include <string>
#include "base.h"
#include <iostream>
#include <math.h>
using namespace std;

class Rombus:public Shape
{
	public:
		Rombus( ){
			 double angle=180;
		     this->Centre = Point(0,0);
			 this->Vertex[0] = Point(1,1);
			 this->Vertex[1] = Point(-1,1);
			 this-> Vertex[2]=Turnus(angle,Vertex[0],Centre);
	         this-> Vertex[3]=Turnus(angle,Vertex[1],Centre);
		
		
		
		};
		Rombus(const Point& centre,const Point& vertex1,const Point& vertex2)
		{   if(sqrt(pow(Distance(centre,vertex1),2)+pow(Distance(centre,vertex2),2))!=Distance(vertex1,vertex2))
			throw invalid_argument("Диагонали ромба должны образовывать прямой угол");
			double angle=180;
	        cout << "ромб\n";
	        this->Centre = centre;
	        this->Vertex[0] = vertex1;
	        this->Vertex[1] = vertex2;
	        this-> Vertex[2]=Turnus(angle,Vertex[0],Centre);
	        this-> Vertex[3]=Turnus(angle,Vertex[1],Centre);
	        
         }

		~Rombus(){cout << "ромб\n";}
   
};

