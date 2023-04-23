#ifndef TRAP_H
#define TRAP_H
#include"shape.h"
#include <iostream>

class trap:public shape{
public:
	point top, bottom;
	double topwidth, bottomwidth;
    trap(point topmid,point bottommid,double topw, double bottomw,color color):shape(o,color){
		top = topmid;
		bottom = bottommid;
		topwidth = topw;
		bottomwidth = bottomw;

		point p0(topmid.x - topw / 2, topmid.y), p1(topmid.x + topw / 2, topmid.y), p2(bottommid.x - bottomw / 2, bottommid.y), p3(bottommid.x + bottomw / 2, bottommid.y);

	 tops.push_back(p0);
	 tops.push_back(p1);
	 tops.push_back(p2);
	 tops.push_back(p3);

	 col = color;

	 double A = topmid.y - bottommid.y, B = bottommid.x - topmid.x, C = topmid.x*bottommid.y - bottommid.x*topmid.y;
	 double X, Y;
	 Y = abs(topmid.y- bottommid.y)/2;
	 X = (-B * Y - C) / A;

	 o.x = X;
	 o.y = Y;

    }
    void scale(double coef)override {
		top.x = top.x*coef;
		top.y = top.y*coef;

		bottom.x = bottom.x*coef;
		bottom.y = bottom.y*coef;

		topwidth = topwidth * coef;
		bottomwidth = bottomwidth * coef;

		point p0(top.x - topwidth / 2, top.y), p1(top.x + topwidth / 2, top.y), p2(bottom.x - bottomwidth / 2, bottom.y), p3(bottom.x + bottomwidth / 2, bottom.y);
		tops[0] = p0;
		tops[1] = p1;
		tops[2] = p2;
		tops[3] = p3;
       }
    void write()override {
        std::cout<<"Trapezium" << std::endl;
        std::cout<<"ID: "<< ID<<std::endl;
        std::cout<<"Color: "<<col.red << " " << col.green << " " << col.blue << std::endl;;
       std::cout<<"Coordinats of tops: ";
       for(unsigned int i=0;i<tops.size();i++){
            std::cout<<tops[i].x<<"."<<tops[i].y << " ";
       }
       std::cout<< std::endl;
	   system("pause");
    }

};
#endif // TRAP_H
