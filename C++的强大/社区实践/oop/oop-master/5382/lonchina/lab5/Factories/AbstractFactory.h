#ifndef LONCHINA_ABSTRACTFACTORY_H
#define LONCHINA_ABSTRACTFACTORY_H

#include <vector>
#include "../Figures/AbstractShape.h"
#include "../Figures/Point.h"

// абстрактная фабрика объектов, для создания фигур
class AbstractFactory {
public:
    virtual AbstractShape* createShape(std::vector<Point> & coord, Point & center, int dots, std::string figure) = 0;
    virtual ~AbstractFactory() {}
};

#endif //LONCHINA_ABSTRACTFACTORY_H
