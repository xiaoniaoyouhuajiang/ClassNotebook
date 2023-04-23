#ifndef LAB5_H
#define LAB5_H

#include <algorithm>

#include "lab2.h"
#include "lab3.h"
#include "lab4.h"

stepik::list< stepik::shared_ptr<Shape> > createRandomShapeList(unsigned int size)
{
    stepik::list< stepik::shared_ptr<Shape> > l;
    for(unsigned int i = 0; i < size; i++)
    {
        Shape* tmp = Shape::createRandomShape();
        l.push_back(stepik::shared_ptr<Shape>(tmp));
    }
    return l;
}

bool isInside(const stepik::shared_ptr<Shape> &s)
{
    Shape* base = new Quadrate(-4, -1, -4, 3, 0, 3, 0, -1, Color());
    bool res = s.get()->IsInsideOfAnother(*base);
    delete base;
    return res;
}





#endif // LAB5_H
