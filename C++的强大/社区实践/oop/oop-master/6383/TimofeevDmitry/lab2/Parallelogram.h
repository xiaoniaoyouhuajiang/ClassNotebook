#ifndef LAB2_PARALLELOGRAM_H
#define LAB2_PARALLELOGRAM_H

#include <vector>
#include <cmath>
#include "Shape.h"

class Parallelogram: public Shape{
public:
    // по смежным сторонам и углу
    Parallelogram(std::string color,double angle, double a, double b);
    void applyForAnyPoint(std::function<void(Point&)> const & f) override ;
    std::string toString() const override ;
    double getA();
    double getB();

protected:
    void onTransformed() override ;
    explicit Parallelogram(std::string color);
    std::vector<Point> pts;
    double a; // сторона для ромба и п-ма
private:
    double b; // для ромба не видна
};
#endif //LAB2_PARALLELOGRAM_H
