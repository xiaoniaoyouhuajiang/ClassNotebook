#ifndef LABOOP_CANNON_HPP
#define LABOOP_CANNON_HPP

#include "GroundForce.hpp"
#include "../FactoryMethod.hpp"

class Cannon : public GroundForce{
public:
    Cannon() {setAttributes(300, 100, 100); unitName = CANNON;};
    char getName() final {return 'c';};
    Unit& operator+=(NeutralObject &object) final;
};

class CannonFactoryMethod : public FactoryMethod{
public:
    Unit* createUnit() const override { return new Cannon();};
};


#endif //LABOOP_CANNON_HPP
