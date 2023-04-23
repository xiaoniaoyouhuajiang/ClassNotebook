//
// Created by user on 31.03.19.
//

#include "Triangle.h"

Triangle::Triangle(Point center, Color color,double a, double b, double angle_a_b) : Shape (center, color), a(a), b(b)
    {
        if(angle_a_b >= 360)
            this->angle_a_b = angle_a_b - int(angle_a_b / 360) * 360;
        else
            this->angle_a_b = angle_a_b;
        c = sqrt(a*a + b*b - 2*a*b*cos(angle_a_b * M_PI / 180));
        double p=a+b+c/2;
        double S=sqrt(p*(p-a)*(p-b)*(p-c));
        double Bb1=sqrt(a*a+(b/2)*(b/2)-a*b*cos(angle_a_b));
        double qb=S*2/(3*b);
        double BG=Bb1-qb;
        double angle_BB1_B1C=180-asin(b*sin(angle_a_b)/(2*a))-angle_a_b;
        double Bx=sin(angle_BB1_B1C)*BG+center.get_x();
        double By=cos(angle_BB1_B1C)*BG+center.get_y();
        points.push_back(Point(Bx,By));
        double yC=a*sin(angle_a_b)+Bx;
        double xC=a*cos(angle_a_b)+By;
        points.push_back(Point(xC,yC));
        double yA=b*sin(angle_a_b)+yC;
        double xA=b*cos(angle_a_b)+xC;
        points.push_back(Point(xA,yA));
    }



    void Triangle::scaling(double k)
    {
        a *= k;
        b *= k;
        c *= k;
        center.setter_y(center.get_y()*k);
        center.setter_x(center.get_x()*k);
        for (auto& pt : points) {
            pt.setter_x(pt.get_x()*k);
            pt.setter_y(pt.get_y()*k);
        }
    }

    std::ostream & operator << (std::ostream & out, Triangle &triangle)
    {
        out << dynamic_cast<Shape &>(triangle)<<endl<<"Shape:Triangle" << endl << "Side a: " <<  triangle.a << endl <<  "Side b: " << triangle.b << endl <<  "Side c:" << triangle.c<< endl <<  "angle:" << triangle.angle_a_b;
        return out;
    }

