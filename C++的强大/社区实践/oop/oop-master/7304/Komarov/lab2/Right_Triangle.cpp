//
// Created by user on 31.03.19.
//
#include "Right_Triangle.h"

Right_Triangle::Right_Triangle(Point center, Color color,double a, double b) :Triangle(center,color,a,b,90) {
    }

   std::ostream & operator << (std::ostream & out, Right_Triangle &right_triangle)
    {
        out << dynamic_cast<Shape &>(right_triangle)<< endl<<"Shape:Right_Triangle" << endl << "Side a: " <<  right_triangle.a << endl <<  "Side b: " << right_triangle.b << endl <<  "Side c:" << right_triangle.c<< endl <<  "angle:" << right_triangle.angle_a_b;
        return out;
    }
