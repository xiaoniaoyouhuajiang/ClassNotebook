#include "figure.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "figure.hpp"

namespace stepik
{
    //Color
    std::ostream& operator<<(std::ostream& os, const Color& tr)
    {
        os << "#" << std::setw(6) << std::setfill('0') << std::hex << tr.color;
        
        return os;
    }
    
    
    //Point
    std::ostream& operator << (std::ostream& os, const Point& tr)
    {
        os << "(" << tr.X << "," << tr.Y << ")";
        
        return os;
    }
    
    Point Point::operator + (Point const& t) const
    {
        Point a(X + t.X, Y + t.Y);
        
        return a;
    }
    
    //Shape
    unsigned int Shape::nextid = 0;
    
    double Shape::intersect(Point const& A, Point const& B, Point const& C, Point const& D) const
    {
        return (rotateLineInfo(A, B, C)*rotateLineInfo(A, B, D) <= 0) && (rotateLineInfo(C, D, A)*rotateLineInfo(C, D, B) < 0);
    }
    
    double Shape::rotateLineInfo(Point const& point0, Point const& point1, Point const& c) const
    {
        return (point1.getX() - point0.getX())*(c.getY() - point1.getY()) - (point1.getY() - point0.getY())*(c.getX() - point1.getX());
    }
    
    bool Shape::isInsideOfAnother(const Shape& other) const
    {
        if (!pointLocal(other.cord)) return 0;
        
        for (Point ipoint : other.point)
        {
            if (!pointLocal(ipoint+other.cord)) return 0;
        }
        
        return 1;
    }
    
    bool Shape::pointLocal(Point const&  a) const
    {
        if (point.size() == 0) return 0;
        if ((rotateLineInfo(cord,point[0] + cord, a) < 0) || (rotateLineInfo(cord,point[point.size()-1] + cord,a) > 0)) return 0;
        
        int leftPoint = 0, rightPoint = point.size() - 1, middlePoint;
        while ((rightPoint - leftPoint) > 1) {
            middlePoint = (leftPoint+rightPoint)/2;
            if (rotateLineInfo(cord,point[middlePoint]+cord,a) < 0)
                rightPoint = middlePoint;
            else
                leftPoint = middlePoint;
        }
        
        return !intersect(cord,a,point[leftPoint]+cord,point[rightPoint]+cord);
    }
    
    void Shape::scale(double coef) {
        for (Point &ipoint : point) {
            ipoint.scale(coef);
        }
    }
    
    void Shape::rotate(double angle) {
        for (Point &ipoint : point) {
            ipoint.rotate(angle);
        }
    }
    
    
    //Triangle
    std::ostream& Triangle::print(std::ostream& os) const{
        os << "Triangle(" << cord << ";" << cord+point[0] << ";" << cord+point[1]
        << ");" << color << ";id:" << id;
        return os;
    }
    
    //Rhombus
    std::ostream& Rhombus::print(std::ostream& os) const{
        os << "Rhombus(" << cord << ";" << cord+point[0] << ";" << cord+point[1]
        << ";" << cord+point[2] << ");" << color<< ";id:" << id;
        return os;
    }
    
    Rhombus::Rhombus(double leng, double angle) {
        cord = Point(0, 0);
        point.push_back(Point(leng, 0));
        point.push_back(Point(leng*(cos(angle)+1), leng*sin(angle)));
        point.push_back(Point(leng*cos(angle), leng*sin(angle)));
    }
    
    
    //Parallelogram
    std::ostream& Parallelogram::print(std::ostream& os) const {
        os << "Parallelogram(" << cord << ";" << cord+point[0] << ";" << cord+point[1]
        << ";" << cord+point[2] << ");" << color << ";id:" << id;
        return os;
    }
    
    Parallelogram::Parallelogram(double width, double height) {
        cord = Point(0, 0);
        point.push_back(Point(width, 0));
        point.push_back(Point(width, height));
        point.push_back(Point(0, height));
    }
}
