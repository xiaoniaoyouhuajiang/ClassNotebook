#ifndef SECTOR_H
#define SECTOR_H
#include "shape.h"

class Sector : public Shape
{
public:
    Sector();
    Sector(double sectorAngle, double radius, Coor center, Color color, double angle);
    ~Sector() override
    {
        coords.clear();
    }
    void scale(double coef) override
    {
        _radius *= coef;
        updateCoords();
    }
    void updateCoords() override
    {
        coords.clear();
        double h = fabs(_radius)*sin(_sectorAngle*M_PI/180);
        double l = sqrt(_radius*_radius-h*h);
        coords.push_back(Coor(_center.x() - _radius,_center.y()));
        if (h > 0)
        coords.push_back(Coor(_center.x() - l, _center.y()+h));
        else
        coords.push_back(Coor(_center.x() + l, _center.y()+h));
    }
    std::ostream& print(std::ostream& out) override
    {
        out<<"***************************************"<<std::endl;
        out<<"Shape: Sector"<<std::endl;
        out<<"Angle of Sector: "<<_sectorAngle<<std::endl;
        out<<"Angle: "<<_angle<<std::endl;
        out<<"Center: "<<_center<<std::endl;
        out<<"Coords:"<<std::endl;
        for (int i = 0; i < coords.size();i++)
        {
        out<<"\t"<<coords[i]<<std::endl;
        }
        out<<"Radius: "<< _radius << std::endl;
        out<<"Color: "<< _color;
        out<<"***************************************"<<std::endl;
        return out;
    }
private:
    double _sectorAngle;
    double _radius;

};

#endif // SECTOR_H
