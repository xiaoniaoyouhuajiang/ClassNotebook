#ifndef ELLIPS_H
#define ELLIPS_H
#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse();
    Ellipse(double x, double y, double _OXRadius, double _OYRadius, Color color, double angle = 0);
    ~Ellipse() override{coords.clear();}
    void scale(double coefficient) override
    {
        if (coefficient <= 0)
        {
            std::cout<<"Wrong scale coefficient";
            return;
        }
        _OYRadius *= coefficient;
        _OXRadius *= coefficient;
        updateCoords();
    }
    std::ostream& print(std::ostream& out) override
    {
        out<<"***************************************"<<std::endl;
        out<<"Shape: Ellipse"<<std::endl;
        out<<"Angle: "<<_angle<<std::endl;
        out<<"Center: "<<_center<<std::endl;
        out<<"Coords:"<<std::endl;
        for (size_t i = 0; i < coords.size();i++)
        {
        out<<"\t"<<coords[i]<<std::endl;
        }
        out<<"OY Radius: "<< _OYRadius << std::endl;
        out<<"OX Radius: "<< _OXRadius << std::endl;
        out<<"Color: "<< _color;
        out<<"***************************************"<<std::endl;
        return out;
    }
    void updateCoords() override
    {
        coords.clear();
        coords.push_back(Coor(_center.x(), _center.y() + _OYRadius / 2));
        coords.push_back(Coor( _center.x() + _OXRadius / 2, _center.y()));
        coords.push_back(Coor(_center.x(), _center.y() - _OYRadius / 2));
        coords.push_back(Coor( _center.x() - _OXRadius / 2, _center.y()));

    }
protected:
    double _OYRadius;
    double _OXRadius;
};

#endif // ELLIPS_H
