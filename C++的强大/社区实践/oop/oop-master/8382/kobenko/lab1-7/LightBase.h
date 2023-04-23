//
// Created by vlad on 02.06.2020.
//

#ifndef UNTITLED_LIGHTBASE_H
#define UNTITLED_LIGHTBASE_H
#include "LightArmy.h"
#include "Field.h"
#include <cstdlib>

class LightBase {
public:
    LightBase();
    static int CreateUnits();
    static int ControlUnits(Field&);
    static LightArcher createLightArcher();
    static LightInfantry createLightInfantry();
    static LightCavalry createLightCavalry();
    int checkBase() const;
    void getDamage(int);
public:
    char type;
    int y;
    int x;
    int health;
};


#endif //UNTITLED_LIGHTBASE_H
