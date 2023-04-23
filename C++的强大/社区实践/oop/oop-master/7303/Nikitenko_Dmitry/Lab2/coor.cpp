#include "coor.h"

Coor::Coor() : _x(0),_y(0)
{
}

Coor::Coor(const Coor &source) :_x(source._x), _y(source._y)
{
}

Coor::Coor(double x, double y) : _x(x),_y(y)
{
}

void Coor::setCoor(double x, double y)
{
   _x = x;
   _y = y;
}

void Coor::setCoor(Coor coor)
{
    _x = coor.x();
    _y = coor.y();
}

double Coor::x(){return _x;}

double Coor::y(){return _y;}

void Coor::x(double x){_x = x;}

void Coor::y(double y){_y = y;}

std::ostream& operator<< (std::ostream &out, Coor& coor)
{
    return coor.print(out);
}
std::ostream& Coor::print(std::ostream& out)
{
    out<<"X = "<<_x<<", Y = "<<_y<<std::endl;
    return out;
}
