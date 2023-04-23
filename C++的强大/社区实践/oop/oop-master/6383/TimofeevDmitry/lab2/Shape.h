// Timofeev Dmitry № 17 var 6
// Треугольник, ромб, параллелограмм

#ifndef LAB2_SHAPE_H
#define LAB2_SHAPE_H
#include <ostream>
#include <functional>
#include <cmath>


struct Point {
    double x;
    double y;
    Point(double x, double y):x(x),y(y){}
};

double length(Point const & a,Point const & b);

struct Color{
    std::string def;
    explicit Color(std::string def):def(def){}
};

class Shape{
public:
    void translate(double x, double y);
    void rotate(double angle);
    void scale(double scale);
    Color const & getColor() const;
    void setColor(Color const &color);
    virtual std::string toString()const =0;
protected:
    virtual void onTransformed()= 0;
    virtual void applyForAnyPoint(std::function<void(Point&)> const & f)= 0;
    explicit Shape(std::string color);
    unsigned long getId() const ;

private:
    Color color;
    unsigned long id;
};


std::ostream &operator<< (std::ostream &os, Shape const &f);
#endif //LAB2_SHAPE_H