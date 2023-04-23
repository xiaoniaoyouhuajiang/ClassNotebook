#ifndef LONCHINA_RECTANGLEFACTORY_H
#define LONCHINA_RECTANGLEFACTORY_H

#include "AbstractFactory.h"
#include "../Figures/AbstractShape.h"
#include "../Figures/Rectangle.h"
#include "../Figures/Point.h"
#include "../libs/library.h"

// фабрика создания треугольников
class RectangleFactory: public AbstractFactory
{
public:
    AbstractShape* createShape(std::vector<Point> & coord, Point & center, int dots, std::string figure);
};

#endif //LONCHINA_RECTANGLEFACTORY_H
