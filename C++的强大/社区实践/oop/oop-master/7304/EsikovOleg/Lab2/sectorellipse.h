#ifndef SECTORELLIPSE_H
#define SECTORELLIPSE_H

#include "ellipse.h"

class SectorEllipse : public Ellipse
{
protected:
    double AngleWithX;
    double AngleSector;

public:
    SectorEllipse(Point LF, Point RF, double space, double Angle1, double Angle2);
    ~SectorEllipse(){}

    void Turn(double value);
    void info(ostream &os);
};

#endif // SECTORELLIPSE_H
