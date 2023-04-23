#ifndef RAVNTRAP_H
#define RAVNTRAP_H
#include"shape.h"
class ravntrap:public shape{
public:
    ravntrap(point o, double topbase, double bottombase, double width, color color):shape(o,color){

         col=color;
		 //o - middle of midline of trapeze
		 tops.push_back(point(o.x - topbase / 2, o.y + width / 2));
		 tops.push_back(point(o.x + topbase / 2, o.y + width / 2));
		 tops.push_back(point(o.x + bottombase / 2, o.y - width / 2));
		 tops.push_back(point(o.x - bottombase / 2, o.y - width / 2));
    }
    void scale(double coef)override {
        for(unsigned int i=0;i<tops.size();i++){
        tops[i].x= o.x+tops[i].x*coef;
        tops[i].y= o.y+tops[i].y*coef;
        }
       }
    void write()override {
        std::cout<<"Isosceles Trapezium" << std::endl;
        std::cout<<"ID: "<< ID<<std::endl;
        std::cout<<"Color: "<< col.red << " " << col.green << " " << col.blue << std::endl;;
       std::cout<<"Coordinats of tops: ";
       for(unsigned int i=0;i<tops.size();i++){
            std::cout<<tops[i].x<<"."<<tops[i].y << " ";
       }
       std::cout<< std::endl;
	   system("pause");
    }
};

#endif // RAVNTRAP_H
