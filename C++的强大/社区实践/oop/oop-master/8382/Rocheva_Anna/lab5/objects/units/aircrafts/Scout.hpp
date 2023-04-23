#ifndef LABOOP_SCOUT_HPP
#define LABOOP_SCOUT_HPP

#include "Aircraft.hpp"
#include "../FactoryMethod.hpp"

class Scout : public Aircraft{
public:
    Scout() {setAttributes(100, 300, 100); unitName = SCOUT;};
    char getName() final {return 's';};
    Unit& operator+=(NeutralObject &object) final;
};

class ScoutFactoryMethod : public FactoryMethod{
public:
    Unit* createUnit() const override { return new Scout();};
};



#endif //LABOOP_SCOUT_HPP
