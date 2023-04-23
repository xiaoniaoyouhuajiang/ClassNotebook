#ifndef LONCHINA_CIRCLE_H
#define LONCHINA_CIRCLE_H

#include "AbstractShape.h"
#include "Point.h"

#include <vector>
#include <iostream>
#include <cmath>

class Circle: public AbstractShape
{
private:
    std::vector<Point> coord;
    Point center;
public:
    // конструктор круга
    Circle(std::vector<Point> & coord, Point & center);

    // вывод круга
    void draw();

    // сдвиг круга
    void moveTo();

    // поворот круга
    void rotateOn(double angle);

    // масштабирование круга
    void scaleOn(double coef);

    void calculateArea();
};

#endif //LONCHINA_CIRCLE_H
