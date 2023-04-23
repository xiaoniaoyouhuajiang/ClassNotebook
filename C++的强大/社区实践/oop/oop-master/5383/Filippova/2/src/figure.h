#ifndef Figure_h
#define Figure_h


#include <iostream>
#include <string>
#include <vector>
#include "point.h"

struct Color
{
    unsigned char r, g, b;
    Color(unsigned char _r = 0, unsigned char _g = 0, unsigned char _b = 0) : r(_r), g(_g), b(_b) {}
};

class Shape{
protected:
    static size_t counter;
    size_t id;
    Color color;
    double angle;
    virtual void print(std::ostream& os) const = 0;
    
public:
    Shape(double angle) : id(counter++), angle(angle), color(Color()) {}
    virtual void move_to(const Point &p)=0;
    virtual void scale(double scale = 1)=0;
    virtual void rotate (double angle = 0);
    Color get_color();
    void set_color(Color color);
    virtual ~Shape(){}
    friend std::ostream& operator << (std::ostream& os, const Shape& p);
    
    // дополнительное задание
    double distance(const Point &p) const;
    virtual std::vector<Point> getVertices() const = 0;
};

#endif




