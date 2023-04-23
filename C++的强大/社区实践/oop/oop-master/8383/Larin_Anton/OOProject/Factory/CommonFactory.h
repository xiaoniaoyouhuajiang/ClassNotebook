//
// Created by anton on 5/26/20.
//

#ifndef OOPROJECT_COMMONFACTORY_H
#define OOPROJECT_COMMONFACTORY_H

#include <memory>
#include <cassert>

#include "Unit/AgileFactory.h"
#include "Unit/MarathonerFactory.h"
#include "Unit/PowerfulFactory.h"
#include "Unit/RangerFactory.h"
#include "Unit/VampireFactory.h"
#include "Unit/ToughFactory.h"
#include "Terrain/HollyFactory.h"
#include "Terrain/SpikyFactory.h"
#include "Terrain/SteepFactory.h"
#include "Entity/BlockFactory.h"
#include "Entity/PitFactory.h"
#include "Entity/TrapFactory.h"
#include "Entity/HealFactory.h"
#include "Base/BaseFactory.h"

#include "../GameObject/FlyWeight.h"

#include "../Exeptions/MediatorNotSetException.h"

class Mediator;

class CommonFactory {
public:

    CommonFactory(const std::shared_ptr<Mediator> &mediator);

    CommonFactory();


    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion, CommonClass objectClass);
    void setBase(std::shared_ptr<Base> base, Devotion devotion);
private:
    void initFactories();

    void initParams(int health, int enhancedHealth, int armour, float dmgmul, float vampiricMultiplyer,
                    int abPower, int enhancedPower, int abRange, int enhancedAbRange, int mbAgility,
                    int enhancedAgility, int mbRange, int enhancedMbRange, int steepness,
                    int enhancedSteepness, int terrainDamage, int terrainHeal,int baseLim,
                    int baseHealth,int baseArmour,float baseDmgmul,
                    int blockHealth,int healAmount,int pitHealth,int pitDmg,int trapDmg);
private:
    std::shared_ptr<Mediator> mediator;
public:
    void setMediator(const std::shared_ptr<Mediator> &mediator);

private:
    FlyWeight flyWeight;

    std::unique_ptr<RangerFactory> rangerFactory;
    std::unique_ptr<PowerfulFactory> powerfulFactory;
    std::unique_ptr<AgileFactory> agileFactory;
    std::unique_ptr<MarathonerFactory> marathonerFactory;
    std::unique_ptr<ToughFactory> toughFactory;
    std::unique_ptr<VampireFactory> vampireFactory;
    std::unique_ptr<SpikyFactory> spikyFactory;
    std::unique_ptr<SteepFactory> steepFactory;
    std::unique_ptr<HollyFactory> hollyFactory;
    std::unique_ptr<BaseFactory> baseFactory;
    std::unique_ptr<HealFactory> healFactory;
    std::unique_ptr<TrapFactory> trapFactory;
    std::unique_ptr<BlockFactory> blockFactory;
    std::unique_ptr<PitFactory> pitFactory;


    int health = 100;
    int enhancedHealth=200;
    int armour = 100;
    float dmgmul = 1;
    float vampiricMultiplyer=.8;
    int abPower=50;
    int enhancedPower=100;
    int abRange=2;
    int enhancedAbRange=5;
    int mbAgility=5;
    int enhancedAgility=10;
    int mbRange=5;
    int enhancedMbRange=10;

    int steepness = 2;
    int enhancedSteepness = 7;
    int terrainDamage = 25;
    int terrainHeal = 25;

    int baseLim=50;
    int baseHealth=500;
    int baseArmour=100;
    float baseDmgmul=1;

    int blockHealth=100;
    int healAmount=25;
    int pitHealth=1000;
    int pitDmg=999;
    int trapDmg=25;

    std::shared_ptr<Base> lightBase;
public:
    const std::shared_ptr<Base> &getLightBase() const;

    const std::shared_ptr<Base> &getDarkBase() const;

private:
    std::shared_ptr<Base> darkBase;







};


#endif //OOPROJECT_COMMONFACTORY_H
