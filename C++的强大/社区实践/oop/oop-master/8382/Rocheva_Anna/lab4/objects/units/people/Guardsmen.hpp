#ifndef LABOOP_GUARDSMEN_HPP
#define LABOOP_GUARDSMEN_HPP


#include "People.hpp"
#include "../FactoryMethod.hpp"

class Guardsmen : public People{
public:
    Guardsmen() {setAttributes(200, 100, 100); unitName = GUARDSMEN;};
    char getName() final {return 'g';};
    Unit& operator+=(NeutralObject &object) final;
};

class GuardsmenFactoryMethod : public FactoryMethod{
public:
    Unit* createUnit() const override { return new Guardsmen();};
};

#endif //LABOOP_GUARDSMEN_HPP
