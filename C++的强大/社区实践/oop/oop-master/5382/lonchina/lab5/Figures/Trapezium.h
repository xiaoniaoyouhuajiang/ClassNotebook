#ifndef LONCHINA_TRAPEZIUM_H
#define LONCHINA_TRAPEZIUM_H

#include "AbstractShape.h"
#include "Point.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

class Trapezium: public AbstractShape
{
private:
    std::vector<Point> coord;
    Point center;
public:
    // конструктор трапеции
    Trapezium(std::vector<Point> & coord, Point & center);

    // вывод трапеции
    void draw();

    // сдвиг трапеции
    void moveTo();

    // поворот трапеции
    void rotateOn(double angle);

    // масштабирование трапеции
    void scaleOn(double coef);

    void calculateArea();
};

#endif //LONCHINA_TRAPEZIUM_H
