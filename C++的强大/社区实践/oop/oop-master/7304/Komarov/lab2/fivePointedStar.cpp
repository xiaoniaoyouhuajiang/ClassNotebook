//
// Created by user on 31.03.19.
//
#include "fivePointedStar.h"

    fivePointedStar::fivePointedStar(Point center, Color color, double radius): Shape (center,color), radius(radius){


        angle = 2 * M_PI / 5;              //делится круг на 5 частей
        points.push_back(Point(center.get_x() + radius * cos(angle * 0),center.get_y() + radius * sin(angle * 0)));
        points.push_back(Point(center.get_x()  + radius * cos(angle * 1),center.get_y()  + radius * sin(angle * 1)));
        points.push_back(Point(center.get_x()  + radius * cos(angle * 2),center.get_y()  + radius * sin(angle * 2)));
        points.push_back(Point(center.get_x()  + radius * cos(angle * 3),center.get_y()  + radius * sin(angle * 3)));
        points.push_back(Point(center.get_x()  + radius * cos(angle * 4),center.get_y()  + radius * sin(angle * 4)));
    }




    void fivePointedStar::scaling(double k)
    {
        radius*=k;
        center.setter_y(center.get_y()*k);
        center.setter_x(center.get_x()*k);
        for (auto& pt : points) {
            pt.setter_x(pt.get_x()*k);
            pt.setter_y(pt.get_y()*k);
        }
    }

  std::ostream & operator << (std::ostream & out, fivePointedStar &fivePointedStar)
    {
        out << dynamic_cast<Shape &>(fivePointedStar)<< endl<<"Shape:fivePointedStar" << endl << "Side radius: " <<  fivePointedStar.radius << endl <<  "Side angle: " << fivePointedStar.angle << endl;
        return out;
    }
