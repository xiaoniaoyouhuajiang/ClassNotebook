#ifndef LABOOP_INFANTRY_HPP
#define LABOOP_INFANTRY_HPP

#include "People.hpp"
#include "../FactoryMethod.hpp"

class Infantry : public People{
public:
    Infantry() {setAttributes(100, 100, 100); unitName = INFANTRY;};
    char getName() final {return 'i';};
    Unit& operator+=(NeutralObject &object) final;
};

class InfantryFactoryMethod : public FactoryMethod{
public:
    Unit* createUnit() const override { return new Infantry();};
};


#endif //LABOOP_INFANTRY_HPP
