
#include <iostream>
#include <cmath>
#include "rectangle.h"

Rectangle::Rectangle(const Point &upperLeft, double width, double height, double angle) :
    Shape(angle),
    upperLeft(upperLeft),
    width(width),
    height(height)
{
    if(width < 0 || height < 0)
    {
        throw std::invalid_argument("Negative sides are not allowed");
    }
}

void Rectangle::move_to(const Point &p)
{
    upperLeft = p;
}

void Rectangle :: rotate (double angle)
{
    this->angle = angle;
}

void Rectangle::scale(double scale)
{
    width *= scale;
    height *= scale;
}

void Rectangle::print(std::ostream& os) const
{
    os << "Rectangle: "<<width<<"x"<<height<<std::endl;
    os << "Color: "<<color.r<<" "<<color.g<<" "<<color.b<< std::endl;
    os << "id: "<< id<<std::endl;
}

std::vector<Point> Rectangle::getVertices() const
{
    
    std::vector<Point> v;
    v.reserve(4);
    
    
    v.push_back(upperLeft);
    v.push_back(Point(v[0].X + width, v[0].Y));
    v.push_back(Point(v[0].X + width, v[0].Y - height));
    v.push_back(Point(v[0].X, v[0].Y - height));
    
    for(auto &vertices : v)
    {
        vertices.rotate(angle);
    }
    
    return v;
}
