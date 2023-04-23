#ifndef SHAPE_H
#define SHAPE_H
#include "color.h"
#include "point.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265

class shape{
public:
    shape(point o,color color):o(o),col(color){
        static long int i = 0;
                ID = i;
                i++;
    }

    int ID;
    point o;
    color col;
	std::vector <point> tops;

    void move(point p){
    double changex = p.x-o.x;
    double changey =p.y-o.y;
    o=p;
    for(unsigned int i=0;i<tops.size();i++){
    tops[i].x=tops[i].x+changex;
    tops[i].y=tops[i].y+changey;
    }
}
     void turn(int angle){

         for(unsigned int i=0;i<tops.size();i++){
                point top=tops[i];
                tops[i].x = o.x+(top.x-o.x)*cos(angle* PI / 180)-(top.y-o.y)*sin(angle* PI / 180);
                tops[i].y =o.y+(top.x-o.x)*sin(angle* PI / 180)+(top.y-o.y)*cos(angle* PI / 180);
				if (tops[i].x < 0.00000001 && tops[i].x > -0.00000001) {
					tops[i].x = 0;
				}
				if (tops[i].y < 0.00000001 && tops[i].y > -0.00000001) {
					tops[i].y = 0;
				}
         }
     }

	 virtual void scale(double coef) =0;
	 virtual void write() =0;
};

#endif // SHAPE_H
