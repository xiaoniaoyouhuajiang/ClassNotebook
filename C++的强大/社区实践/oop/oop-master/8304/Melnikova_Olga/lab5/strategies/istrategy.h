#pragma once

#include "objects/units/unit.h"
//class Unit;

class IStrategy  //интерфейс какой-то стратегии (зав. от юнита)
{
public:
    virtual void interact(Unit* unit) = 0;
    virtual ~IStrategy();
    int operator++ (int a){
        a+=1;
        return a;
    }
    
};
