#ifndef LONCHINA_TRAPEZIUMFACTORY_H
#define LONCHINA_TRAPEZIUMFACTORY_H

#include "AbstractFactory.h"
#include "../Figures/Point.h"
#include "../Figures/Trapezium.h"
#include "../libs/library.h"

// фабрика создания трапеций
class TrapeziumFactory: public AbstractFactory
{
public:
    AbstractShape* createShape(std::vector<Point> & coord, Point & center, int dots, std::string figure);
};

#endif //LONCHINA_TRAPEZIUMFACTORY_H
