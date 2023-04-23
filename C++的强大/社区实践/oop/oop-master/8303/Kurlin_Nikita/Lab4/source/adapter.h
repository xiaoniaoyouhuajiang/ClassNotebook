#ifndef ADAPTER_H
#define ADAPTER_H

#include <iostream>
#include <sstream>
#include "Units/unit.h"

class Base;
class GameField;

class Adapter
{

public:
    Adapter();
    static std::string unitCreation(Unit*, int, int, int);
    static std::string unitMoving(Unit*, int, int, int);
    static std::string baseCreation(Base*);
    static std::string fieldCreation(GameField*);
    static std::string unitDeletion(Unit*, int, int);
    static std::string baseDamage(Base*);
    static std::string baseDestruction(Base*);
    static std::string unitDamage(Unit*, int, int);
};

#endif // ADAPTER_H
