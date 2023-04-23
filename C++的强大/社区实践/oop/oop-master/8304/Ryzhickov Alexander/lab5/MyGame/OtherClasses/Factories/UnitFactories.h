//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_UNITFACTORIES_H
#define GAME_UNITFACTORIES_H


#include "../../UnitAmunition/Weapon/ColdSteel/Axe.h"
#include "../../UnitAmunition/Weapon/ColdSteel/Spear.h"
#include "../../UnitAmunition/Weapon/ColdSteel/Sword.h"
#include "../../UnitAmunition/Weapon/RangeWeapons/Bow.h"
#include "../../UnitAmunition/Weapon/RangeWeapons/Rod.h"
#include "../../UnitAmunition/Armor/AttackUnitArmor/AttackUnitArmor.h"
#include "../../UnitAmunition/Armor/HeavyUnitArmor/HeavyUnitArmor.h"
#include "../../UnitAmunition/Armor/RangeUnitArmor/RangeUnitArmor.h"
#include "../../Units/AttackInfantry/Swordmen.h"
#include "../../Units/AttackInfantry/Spearmen.h"
#include "../../Units/HeavyInfantry/Knight.h"
#include "../../Units/RangedUnits/Archer.h"
#include "../../Units/HeavyInfantry/King.h"
#include "../../Units/RangedUnits/Magician.h"

class UnitFactory{
public:
    UnitFactory();
    ~UnitFactory();
    Swordmen* getSwordsmen(int x,int y);
    Spearmen* getSpearmen(int x,int y);
    Knight* getKnight(int x,int y);
    King* getKing(int x,int y);
    Archer* getArcher(int x,int y);
    Magician* getMagician(int x,int y);

    Swordmen* loadSwordsmen(int x,int y,int numberInArray, int health,int armor,int damage,int attackBonus);
    Spearmen* loadSpearmen(int x,int y,int numberInArray, int health,int armor,int damage,int attackBonus);
    Knight* loadKnight(int x,int y,int numberInArray, int health,int armor,int damage,int attackBonus);
    King* loadKing(int x,int y,int numberInArray, int health,int armor,int damage,int attackBonus);
    Archer* loadArcher(int x,int y,int numberInArray, int health,int armor,int damage,int attackBonus);
    Magician* loadMagician(int x,int y,int numberInArray, int health,int armor,int damage,int attackBonus);

private:
    Axe *axe;
    Spear *spear;
    Sword *sword;
    Bow *bow;
    Rod *rod;
    AttackUnitArmor *attackUnitArmor;
    HeavyUnitArmor *heavyUnitArmor;
    RangeUnitArmor *rangeUnitArmor;
};


#endif //GAME_UNITFACTORIES_H
