#include "shape.h"

Shape::Shape() : _angle(0), _center(0,0), _color(0,0,0)
{
    static unsigned long int counter = 0;
    id = counter;
    counter++;
}

Shape::Shape(Coor coor, Color color, double angle) :
    _angle(angle), _center(coor), _color(color)
{
    static unsigned long int counter = 0;
    id = counter;
    counter++;
}
Shape::Shape(double x, double y, Color color, double angle) :
    _angle(angle), _center(x,y),  _color(color)
{
    static unsigned long int counter = 0;
    id = counter;
    counter++;
}


std::ostream& operator<< (std::ostream &out, Shape& s)
{
    return s.print(out);
}

void Shape::setColor(Color color)
{
    this->_color = color;
}

void Shape::rotate(double angle)
{
    double x, y;
    _angle = angle;

    angle = angle*M_PI/180;
            for (size_t i = 0; i < coords.size(); ++i) {

                x = coords[i].x();
                y = coords[i].y();

                coords[i].x( (x - _center.x()) * cos(angle) - (y - _center.y()) * sin(angle) + _center.x());
                if (coords[i].x() < 0.00000001)
                    coords[i].x(0);
                coords[i].y((x - _center.x()) * sin(angle) + (y - _center.y()) * cos(angle) + _center.y());
                if (coords[i].y() < 0.00000001)
                    coords[i].y(0);
            }

}

void Shape::moveTo(Coor center)
{
    _center.setCoor(center);
    updateCoords();
}

void Shape::moveTo(double x, double y)
{
    _center.setCoor(x,y);
    updateCoords();
}

