#ifndef UNIT_H
#define UNIT_H
#include <string>
#include <iostream>
#include "attributes.h"
#include "subject.h"
#include "basecomponent.h"

class Unit : public Subject, public BaseComponent
{
public:
    Unit();
    void deapth();
    void getDamage(int);
    void setAttributes(int, int, int);
    void setName(std::string);
    void setArmyType(std::string);
    std::string getName();
    std::string getArmyType();
    int getArmor();
    int getAttack();
    int getHealth();
    void armorAdd(int);
    void attackAdd(int);
    void healthAdd(int);

private:
    Attributes *attributes = new Attributes;
    std::string armyType;
    std::string name;

    friend std::ostream& operator<< (std::ostream& out, const Unit& unit);
};

#endif // UNIT_H
