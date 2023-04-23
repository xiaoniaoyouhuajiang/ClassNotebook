#include "right_triangle.h"

RightTriangle::RightTriangle(rgb color, double x, double y, double side1, double side2)
{
    this->side1 = side1;    //вертикаль
    this->side2 = side2;    //горизонталь
    setMainCenter(x, y);
    one.setPoint(x-side2/4, y-side1/4);
    two.setPoint(one.getX(), one.getY() + 3*side1/4);     //вертикаль
    three.setPoint(one.getX() + 3*side2/4, one.getY());   //горизонталь
    this->color.setColor(color.getRed(), color.getGreen(), color.getBlue());
}

std::ostream& RightTriangle::printShape(std::ostream &out, Shape &shape)
{
    rgb clr = shape.getShapeColor();
    out << "RightTriangle: (" << one.getX() << ", " << one.getY() << ") (" << two.getX() << ", " << two.getY() << ") (" << three.getX() << ", " << three.getY() << ")\n";
    out << "               Center of shape: (" << center.getX() << ", " << center.getY() << ")\n";
    out << "               ID: " << shape.getId() << " Color: (" << clr.getRed() << ", " << clr.getGreen() << ", " << clr.getBlue() << ")\n";
    return out;
}

RightTriangle RightTriangle::operator +(double value)
{
    RightTriangle tmp = *this;
    tmp.one = tmp.one + value;
    tmp.two = tmp.two + value;
    tmp.three = tmp.three + value;
    tmp.setCenter();
    return tmp;
}
