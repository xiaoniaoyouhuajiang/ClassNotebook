#include "shape.h"

Shape::Shape()
{
    count++;
    id = count;
}

Shape::Shape(rgb color) : Shape()
{
    this->color = color;
}

void Shape::setMainCenter(double x, double y)
{
    center.setPoint(x, y);
}

Point Shape::getMainCenter()
{
    return center;
}

rgb Shape::getShapeColor()
{
    return color;
}

unsigned long int Shape::getId(){
    return id;
}
