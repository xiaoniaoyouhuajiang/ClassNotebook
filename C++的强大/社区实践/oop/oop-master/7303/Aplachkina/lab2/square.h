#ifndef SQUARE_H
#define SQUARE_H
#include"shape.h"
#include <iostream>

class square:public shape{
public:
    square(point o,double side,color color):shape(o,color) {

       // tops.reserve(4);
         col=color;
		 tops.push_back(point(o.x- side / 2, o.y + side / 2));
		 tops.push_back(point(o.x + side / 2, o.y + side / 2));
		 tops.push_back(point(o.x + side / 2, o.y - side / 2));
		 tops.push_back(point(o.x - side / 2, o.y - side / 2));
    }
    void scale (double coef)override {
        for(unsigned int i=0;i<tops.size();i++){
        tops[i].x=o.x+tops[i].x*coef;
        tops[i].y=o.y+tops[i].y*coef;
        }
    }
    void write()override{
        std::cout<<"Square"<< std::endl;
        std::cout<<"ID: "<< ID<<std::endl;
        std::cout<<"Color: "<<col.red << " " << col.green << " " << col.blue << std::endl;;
       std::cout<<"Coordinats of tops: ";
       for(unsigned int i=0;i<tops.size();i++){
            std::cout<<tops[i].x<<"."<<tops[i].y<<" ";
       }
       std::cout<< std::endl;
	   system("pause");
    }

};
#endif // SQUARE_H
