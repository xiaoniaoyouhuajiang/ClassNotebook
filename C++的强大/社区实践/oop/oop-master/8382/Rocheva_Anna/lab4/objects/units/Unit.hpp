#ifndef LABOOP_UNIT_HPP
#define LABOOP_UNIT_HPP

#include <iostream>
#include <vector>
#include "../neutralObjects/NeutralObject.hpp"

#include "attributes/Health.hpp"
#include "attributes/Attack.hpp"
#include "attributes/Defense.hpp"

#include "../Subject.hpp"
#include "../Observer.hpp"


enum UnitName {INFANTRY, GUARDSMEN, FIGHTER, SCOUT, CANNON, TANK};

// component
class Unit : public Subject{
public:
    Unit(Unit&unit);
    Unit&operator=(Unit &unit);
    Unit(Unit &&unit);
    Unit& operator=(Unit &&unit);
    void changeAttributes(int attack, int defense, int health);
    void setAttributes(int attack, int defense, int health);
    void printAttributeValues();
    void setCoordinates(int x, int y) final;
    int getHealthValue() {return health->getValue();};
    int getAttackValue() {return attack->getValue();};
    int getDefenseValue() {return defense->getValue();};
    Coordinates * getCoordinates() final {return coordinates;};
    UnitName getUnitName() {return unitName;};
    virtual ~Unit() = default;
    virtual Unit& operator+=(NeutralObject &object) = 0;
    void notifyObservers(std::string *newAction) final;
    void addObservers(Observer *observer) final;
protected:
    explicit Unit() {};
    UnitName unitName;
private:
    std::vector <Observer*> observers;
    Coordinates *coordinates;
    Attack *attack;
    Defense *defense;
    Health *health;
};

#endif //LABOOP_UNIT_HPP
