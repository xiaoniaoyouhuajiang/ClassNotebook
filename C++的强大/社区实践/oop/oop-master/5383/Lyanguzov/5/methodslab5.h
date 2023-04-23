#ifndef METHODSLAB5_H
#define METHODSLAB5_H

#include "shape.h"
#include "vectorstepik.h"
#include "sharedpointer.h"

// создаем вектор случайных фигур с размером size
stepik::vector< stepik::shared_ptr<Shape> > createRandomShapeVector(unsigned int size)
{
    stepik::vector< stepik::shared_ptr<Shape> > v;
    for(unsigned int i = 0; i < size; i++)
    {
        Shape* tmp = Shape::createRandomShape();
        v.push_back(stepik::shared_ptr<Shape>(tmp));
    }
    return v;
}

// функция-предикат для немодифицирующего алгоритма
//bool isIntersectWith(Shape *s)
//{
//    Round base(0, 0, 10);
//    int res = s->intersect(base);
//    if(res == 0)
//    {
//        return false;
//    }
//    else
//    {
//        return true;
//    }
//}

bool isIntersectWith(const stepik::shared_ptr<Shape> &s)
{
    Round base(0, 0, 10);
    int res = s.get()->intersect(base);
    if(res == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool cmp(const stepik::shared_ptr<Shape> &first, const stepik::shared_ptr<Shape> &second)
{
    return (first.get()->getId() < second.get()->getId());
}

void dividedifferentElelments(const stepik::vector<stepik::shared_ptr<Shape> > &first,
                         const stepik::vector<stepik::shared_ptr<Shape> > &second,
                         stepik::vector<stepik::shared_ptr<Shape> > &difference);

stepik::vector< stepik::shared_ptr<Shape> > makeSortedDifference(stepik::vector< stepik::shared_ptr<Shape> > &first,
                stepik::vector< stepik::shared_ptr<Shape> > &second)
{
    stepik::vector< stepik::shared_ptr<Shape> >difference;
    dividedifferentElelments(first, second, difference);
    dividedifferentElelments(second, first, difference);

    std::sort(difference.begin(), difference.end(), cmp);

    return difference;
}

void dividedifferentElelments(const stepik::vector< stepik::shared_ptr<Shape> > &first,
                              const stepik::vector< stepik::shared_ptr<Shape> > &second,
                              stepik::vector< stepik::shared_ptr<Shape> > &difference)
{
    for(auto it1 : first)
    {
        bool isFinded = false;
        for(auto it2 : second)
        {
            if(*it1.get() == *it2.get())
            {
                isFinded = true;
                break;
            }
        }
        if(!isFinded)
        {
            difference.push_back(it1);
        }
    }
}

#endif // METHODSLAB5_H
