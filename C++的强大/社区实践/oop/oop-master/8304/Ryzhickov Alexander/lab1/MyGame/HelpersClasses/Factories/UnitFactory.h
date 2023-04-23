//
// Created by Alex on 03.03.2020.
//

#ifndef MYGAME_UNITFACTORY_H
#define MYGAME_UNITFACTORY_H


#include "../../Units/Infantry/Swordmen.h"
#include "../../Units/Infantry/Spearmen.h"
#include "../../Units/Cavalry/LightCavalry.h"
#include "../../Units/Cavalry/HeavyCavalry.h"
#include "../../Units/LongRangeIUnits/Arbalester.h"
#include "../../Units/LongRangeIUnits/Archer.h"
#include "../../Trappings/Weapons/MeleeWeapons/Axe.h"
#include "../../Trappings/Weapons/MeleeWeapons/Spear.h"
#include "../../Trappings/Weapons/MeleeWeapons/Sword.h"
#include "../../Trappings/Weapons/RangedWeapons/Crossbow.h"
#include "../../Trappings/Weapons/RangedWeapons/LongBow.h"
#include "../../Trappings/Weapons/RangedWeapons/ShortBow.h"
#include "../../Trappings/Armors/CavalryArmor/CavalryArmor.h"
#include "../../Trappings/Armors/InfantryArmor/InfantryArmor.h"
#include "../../Trappings/Armors/LongRangeUnitsArmor/LongRangeUnitsArmor.h"

class UnitFactory {
public:
    UnitFactory();
    ~UnitFactory();
    Swordmen* getSwordsmen();
    Spearmen* getSpearmen();
    LightCavalry* getLightCavalry();
    HeavyCavalry* getHeavyCavalry();
    Arbalester* getArbalester();
    Archer* getArcherWithShortBow();
    Archer* getArcherWithLongBow();

private:
    Axe *axe;
    Spear *spear;
    Sword *sword;
    Crossbow *crossbow;
    LongBow *longBow;
    ShortBow *shortBow;
    CavalryArmor *cavalryArmor;
    InfantryArmor *infantryArmor;
    LongRangeUnitsArmor *longRangeUnitsArmor;
};


#endif //MYGAME_UNITFACTORY_H
