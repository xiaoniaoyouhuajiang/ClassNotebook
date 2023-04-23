#ifndef OOPLAB5VALERIA_5_H
#define OOPLAB5VALERIA_5_H

#include "lab2.h"
#include "lab3.h"
#include "lab4.h"

#include <functional>

// вспомогательные методы
// функция-предикат для немодифицирующего алгоритма
bool isEqual(Shape *s1,Shape *s2)
{
    if(s1 == s2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//функция-предикат для модифицирующего алогритма
bool redis(Shape *s)
{
    Color shapeColor = s->getColor();
    if(shapeColor.red >= 100 && shapeColor.green < 100 && shapeColor.blue < 100)
    {
       return true;
    }
    else
    {
        return false;
    }
}

// создаем вектор случайных фигур с размером 1000
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

// 1) Проверка двух неупорядоченных диапазонов на равенство по определенному критерию.
bool checkLists(stepik::list< stepik::shared_ptr<Shape> > &first,
                stepik::list< stepik::shared_ptr<Shape> > &second,
                std::function<bool (Shape*, Shape*)> pred)
{
    if(first.size() == second.size())
    {
        stepik::list_iterator< stepik::shared_ptr<Shape> > itFirst = first.begin(), itSecond = second.begin();
        while(itFirst != first.end())
        {
            if (!pred(itFirst->get(), itSecond->get()))
            {
                return false;
            }
            itFirst++;
            itSecond++;
        }
        return true;
    }
    else
    {
        return false;
    }
}


// 2) Удалить элементы, удовлетворяющие заданному критерию.
void eraseElement(stepik::list< stepik::shared_ptr<Shape> > &container,
                  std::function<bool (Shape*)> pred)
{
    stepik::list_iterator< stepik::shared_ptr<Shape> > itContainer = container.begin();
    while(itContainer != container.end())
    {
        if (!pred(itContainer->get()))
        {
            container.erase(itContainer);
        }
//        else{
            itContainer++;
//        }
    }
}


#endif //OOPLAB5VALERIA_5_H
