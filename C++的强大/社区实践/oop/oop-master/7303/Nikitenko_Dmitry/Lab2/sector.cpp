#include "sector.h"

Sector::Sector() : Shape (), _sectorAngle(45),_radius(1)
{
    updateCoords();
}

Sector::Sector(double sectorAngle, double radius,
       Coor center, Color color,
       double angle)
    : Shape(center,color,angle), _sectorAngle(sectorAngle),_radius(radius)
{updateCoords();}
