#ifndef PARALL_H
#define PARALL_H
#include "shape.h"

class Parall : public Shape
{
public:
    Parall();
    Parall(Parall&);
    Parall(double length, double sideLenth, double sideAngle,double x,double y, Color& color, double angle);
    ~Parall() override
    {
        coords.clear();
    }
    void scale(double coef) override
    {
        _height *= coef;
        _length *= coef;
        _sideLength *= coef;
        updateCoords();
    }

    std::ostream& print(std::ostream& out) override
    {
        out<<"***************************************"<<std::endl;
        out<<"Shape: Parallelogram"<<std::endl;
        out<<"Angle: "<<_angle<<std::endl;
        out<<"Center: "<<_center<<std::endl;
        out<<"Coords:"<<std::endl;
        for (size_t i = 0; i < coords.size();i++)
        {
        out<<"\t"<<coords[i]<<std::endl;
        }
        out<<"Height: "<<_height<<std::endl;
        out<<"Length: "<<_length<<std::endl;
        out<<"Length of side: "<<_sideLength<<std::endl;
        out<<"Angle between sides: "<<_sideAngle<<std::endl;
        out<<"Color: "<< _color;
        out<<"***************************************"<<std::endl;
        return out;
    }
    void updateCoords() override
    {
        coords.clear();

        double sidex = _sideLength*cos(_sideAngle*M_PI/180);
        double h = _height/2;
        coords.push_back(Coor(_center.x() - (_length+sidex) / 2, _center.y() - h));
        coords.push_back(Coor(_center.x() - (_length+sidex) / 2 + sidex, _center.y() + h));
        coords.push_back(Coor(_center.x() + (_length+ sidex)/ 2, _center.y() + h ));
        coords.push_back(Coor(_center.x() + (_length+sidex)/ 2 - sidex, _center.y() - h ));

    }
private:
    double _sideAngle;

    double _length;
    double  _sideLength;
    double _height;

};

#endif // PARALL_H
