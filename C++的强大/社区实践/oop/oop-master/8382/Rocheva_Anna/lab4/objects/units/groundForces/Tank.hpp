#ifndef LABOOP_TANK_HPP
#define LABOOP_TANK_HPP

#include "GroundForce.hpp"
#include "../FactoryMethod.hpp"

class Tank : public GroundForce{
public:
    Tank() {setAttributes(300, 200, 100); unitName = TANK;};
    char getName() final {return 't';};
    Unit& operator+=(NeutralObject &object) final;
};

class TankFactoryMethod : public FactoryMethod{
public:
    Unit* createUnit() const override { return new Tank();};
};


#endif //LABOOP_TANK_HPP
