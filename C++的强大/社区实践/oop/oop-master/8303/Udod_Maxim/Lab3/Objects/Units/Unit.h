//
// Created by shenk on 14.02.2020.
//

#ifndef UNTITLED13_UNIT_H
#define UNTITLED13_UNIT_H


#include <vector>
#include <ostream>
#include "../../Armor/Armor.h"
#include "../../Weapon/Weapon.h"
#include "../../Point.h"
#include "../GameObject.h"
#include "../../Observers/UnitObserver.h"
#include "../../Landscapes/LandscapeProxy.h"
#include "../Neutrals/NeutralObject.h"

enum class UnitType{

    INFANTRY,
    WIZARD,
    ARCHER

};

class Unit: public GameObject {

protected:

    std::vector<UnitObserver*> observers;

    UnitType unitType;

    Armor &armor;
    Weapon &weapon;
    int health;

    void print(std::ostream &stream) const override;

public:

    Unit(const Unit &other);
    Unit(UnitType unitType, Armor &armor, Weapon &weapon, int health);

    Weapon &getWeapon(){ return weapon; }
    Armor &getArmor(){ return armor; }

    void move(Point position);
    void attack(Unit &other);
    void damage(int damage);
    void heal(int hp);

    void addObserver(UnitObserver *observer);
    Unit& operator=(const Unit &other);
    Unit& operator<<(NeutralObject *neutralObject);

    UnitType getUnitType(){ return unitType; }

    int getHealth();

};

#endif //UNTITLED13_UNIT_H
