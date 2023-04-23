#ifndef LABOOP_FACTORYMETHOD_HPP
#define LABOOP_FACTORYMETHOD_HPP

#include "Unit.hpp"

class FactoryMethod {
public:
    virtual ~FactoryMethod(){};
    virtual Unit* createUnit() const = 0;
};


#endif //LABOOP_FACTORYMETHOD_HPP
