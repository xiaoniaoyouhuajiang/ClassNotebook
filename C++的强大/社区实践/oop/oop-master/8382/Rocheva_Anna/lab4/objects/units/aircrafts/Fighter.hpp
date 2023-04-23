#ifndef LABOOP_FIGHTER_HPP
#define LABOOP_FIGHTER_HPP

#include "Aircraft.hpp"
#include "../FactoryMethod.hpp"

class Fighter : public Aircraft{
public:
    Fighter() {setAttributes(300, 100, 100); unitName = FIGHTER;};
    char getName() final {return 'f';};
    Unit& operator+=(NeutralObject &object) final;
};

class FighterFactoryMethod : public FactoryMethod{
public:
    Unit* createUnit() const override { return new Fighter();};
};


#endif //LABOOP_FIGHTER_HPP
