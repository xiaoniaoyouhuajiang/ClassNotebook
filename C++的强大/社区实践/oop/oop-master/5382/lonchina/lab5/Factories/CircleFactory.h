#ifndef LONCHINA_CIRCLEFACTORY_H
#define LONCHINA_CIRCLEFACTORY_H

#include "AbstractFactory.h"
#include "../Figures/Point.h"
#include "../libs/library.h"
#include "../Figures/Circle.h"

// фабрика для создания кругов
class CircleFactory: public AbstractFactory
{
public:
    AbstractShape* createShape(std::vector<Point> & coord, Point & center, int dots, std::string figure);
};

#endif //LONCHINA_CIRCLEFACTORY_H
