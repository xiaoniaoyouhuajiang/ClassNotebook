//
// Created by user on 31.03.19.
//
#include "Point.h"

    Point::Point(double x, double y):   x(x), y(y){};

    void Point::setter_x(double x){
        this->x = x;
    }

    void Point::setter_y(double y){
        this->y=y;
    }

    double Point::get_x(){
        return x;
    }
    double Point::get_y(){
        return y;
    }



