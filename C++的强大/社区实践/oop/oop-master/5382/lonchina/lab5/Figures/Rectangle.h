#ifndef LONCHINA_RECTANGLE_H
#define LONCHINA_RECTANGLE_H

#include "AbstractShape.h"
#include "Point.h"

#include <vector>
#include <iostream>
#include <cmath>

class Rectangle: public AbstractShape
{
private:
    std::vector<Point> coord;
    Point center;
public:
    // конструктор Треугольника
    Rectangle(std::vector<Point> & coord, Point & center);

    // вывод треугольника
    void draw();

    // сдвиг треугольника
    void moveTo();

    // поворот треугольника
    void rotateOn(double angle);

    // масштабирование треугольника
    void scaleOn(double coef);

    void calculateArea();
};

#endif //LONCHINA_RECTANGLE_H
