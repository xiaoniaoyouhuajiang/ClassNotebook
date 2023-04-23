#include "triangle.h"

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3, const Color& color)
    :Shape(Point((p1.x+p2.x+p3.x)/3, (p1.y+p2.y+p3.y)/3), color)
{
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    a = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
    b = sqrt((p2.x - p3.x)*(p2.x - p3.x) + (p2.y - p3.y)*(p2.y - p3.y));
    c = sqrt((p3.x - p1.x)*(p3.x - p1.x) + (p3.y - p1.y)*(p3.y - p1.y));
    if( (a+b) <= c || (a+c) <= b && (c+b) <= a){
        throw std::logic_error("Not a triangle");
    }
}

Triangle::Triangle(const Triangle& other)
    :Shape(other.pos, other.color),
     points(other.points),
     a(other.a),
     b(other.b),
     c(other.c)
{
    angle = other.angle;
}

void Triangle::move(const Point& p){
    double x_diff = p.x - pos.x;
    double y_diff = p.y - pos.y;
    pos.x += x_diff;
    pos.y += y_diff;
    for(auto& el : points){
        el.x += x_diff;
        el.y += y_diff;
    }
}

void Triangle::scale(double scale){
    for(auto& el : points){
        el.x *= scale;
        el.y *= scale;
    }
    a = sqrt((points[0].x - points[1].x)*(points[0].x - points[1].x)
            + (points[0].y - points[1].y)*(points[0].y - points[1].y));
    b = sqrt((points[1].x - points[1].x)*(points[1].x - points[2].x)
            + (points[1].y - points[2].y)*(points[1].y - points[2].y));
    c = sqrt((points[2].x - points[0].x)*(points[2].x - points[0].x)
            + (points[2].y - points[0].y)*(points[2].y - points[0].y));
}

void Triangle::turn(double angle){
    Point t(pos.x, pos.y);
    move(Point(0, 0));
    this->angle += angle;
    double x, y;
    for(auto& el : points){
        x = el.x;
        y = el.y;
        el.x = x*cos(this->angle*M_PI/180) - y*sin(this->angle*M_PI/180);
        el.y = x*sin(this->angle*M_PI/180) + y*cos(this->angle*M_PI/180);
    }
    move(t);
}

std::vector<double> Triangle::sides(){
    return std::vector<double>{a, b, c};
}

Point Triangle::operator[](int ind){
    if(ind >= points.size()){
        throw std::out_of_range("Index > points.size");
    }
    return points[ind];
}

std::ostream& operator<<(std::ostream& os, Triangle& s){
    os << "---Triangle---\n";
    os << (Shape&)s;
    std::vector<double> sides = s.sides();
    os << "Points: \n" <<"("<< s[0].x << ", " << s[0].y << ")" << '\n';
    os << "(" << s[1].x << ", " << s[1].y << ")" << "\n";
    os << "(" << s[2].x << ", " << s[2].y << ")" << "\n";
    os << "Sides: " << sides[0] << " " << sides[1] << " " << sides[2] << '\n';
    os << "--------------\n";
}
