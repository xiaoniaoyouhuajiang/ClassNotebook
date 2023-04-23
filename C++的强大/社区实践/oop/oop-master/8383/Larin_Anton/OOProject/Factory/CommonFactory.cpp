//
// Created by anton on 5/26/20.
//

#include "CommonFactory.h"

#include "../GameObject/FlyWeight.h"
#include "../Exeptions/AttemptToSetNeutralBaseException.h"

CommonFactory::CommonFactory(const std::shared_ptr<Mediator> &mediator) : mediator(mediator) {
    initParams(100, 200, 100, 1, .8, 50, 100, 2, 5, 5, 10, 5, 10, 2, 7, 25, 25, 50, 500, 100, 1, 100, 25, 1000, 999,
               25);
    initFactories();
}

CommonFactory::CommonFactory() {
    initParams(100, 200, 100, 1, .8, 50, 100, 2, 5, 5, 10, 5, 10, 2, 7, 25, 25, 50, 500, 100, 1, 100, 25, 1000, 999,
               25);
    initFactories();
}

void CommonFactory::initFactories() {
    rangerFactory = std::make_unique<RangerFactory>(health, armour, dmgmul, abPower, abRange, mbAgility, mbRange,
                                                    enhancedAbRange);
    powerfulFactory = std::make_unique<PowerfulFactory>(health, armour, dmgmul, abPower, abRange, mbAgility, mbRange,
                                                        enhancedPower);
    agileFactory = std::make_unique<AgileFactory>(health, armour, dmgmul, abPower, abRange, mbAgility, mbRange,
                                                  enhancedAgility);
    marathonerFactory = std::make_unique<MarathonerFactory>(health, armour, dmgmul, abPower, abRange, mbAgility,
                                                            mbRange, enhancedMbRange);
    toughFactory = std::make_unique<ToughFactory>(health, armour, dmgmul, abPower, abRange, mbAgility, mbRange,
                                                  enhancedHealth);
    vampireFactory = std::make_unique<VampireFactory>(health, armour, dmgmul, abPower, abRange, mbAgility, mbRange,
                                                      vampiricMultiplyer);
    spikyFactory = std::make_unique<SpikyFactory>(steepness, terrainDamage);
    steepFactory = std::make_unique<SteepFactory>(steepness, enhancedSteepness);
    hollyFactory = std::make_unique<HollyFactory>(steepness, terrainHeal);
    baseFactory = std::make_unique<BaseFactory>(baseLim, baseHealth, baseArmour, baseDmgmul);
    healFactory = std::make_unique<HealFactory>(healAmount);
    trapFactory = std::make_unique<TrapFactory>(trapDmg);
    blockFactory = std::make_unique<BlockFactory>(blockHealth);
    pitFactory = std::make_unique<PitFactory>(pitHealth, pitDmg);

}

void CommonFactory::initParams(int health, int enhancedHealth, int armour, float dmgmul, float vampiricMultiplyer,
                               int abPower, int enhancedPower, int abRange, int enhancedAbRange, int mbAgility,
                               int enhancedAgility, int mbRange, int enhancedMbRange, int steepness,
                               int enhancedSteepness, int terrainDamage, int terrainHeal, int baseLim,
                               int baseHealth, int baseArmour, float baseDmgmul,
                               int blockHealth = 100, int healAmount = 25, int pitHealth = 1000, int pitDmg = 999,
                               int trapDmg = 25) {
    this->health = health;
    this->enhancedHealth = enhancedHealth;
    this->armour = armour;
    this->dmgmul = dmgmul;
    this->vampiricMultiplyer = vampiricMultiplyer;
    this->abPower = abPower;
    this->enhancedPower = enhancedPower;
    this->abRange = abRange;
    this->enhancedAbRange = enhancedAbRange;
    this->mbAgility = mbAgility;
    this->enhancedAgility = enhancedAgility;
    this->mbRange = mbRange;
    this->enhancedMbRange = enhancedMbRange;
    this->steepness = steepness;
    this->enhancedSteepness = enhancedSteepness;
    this->terrainDamage = terrainDamage;
    this->terrainHeal = terrainHeal;
    this->baseLim = baseLim;
    this->baseHealth = baseHealth;
    this->baseArmour = baseArmour;
    this->baseDmgmul = baseDmgmul;
    this->blockHealth = blockHealth;
    this->healAmount = healAmount;
    this->pitHealth = pitHealth;
    this->pitDmg = pitDmg;
    this->trapDmg = trapDmg;
}

std::shared_ptr<GameObject> CommonFactory::createObject(int x, int y, Devotion devotion, CommonClass objectClass) {
    if(!mediator)throw MediatorNotSetException("CommonFactory");

    auto ptr = std::shared_ptr<GameObject>(nullptr);
    switch (objectClass) {
        case CommonClass::NONE:{
            ptr = std::shared_ptr<GameObject>(nullptr);
            break;
        }
        case CommonClass::TheRanger: {
            ptr = rangerFactory->createObject(x, y, devotion);
            ptr->setMediator(mediator);
            break;
        }
        case CommonClass::ThePowerful: {
            ptr = powerfulFactory->createObject(x, y, devotion);
            ptr->setMediator(mediator);
            break;
        }
        case CommonClass::TheAgile: {
            ptr = agileFactory->createObject(x, y, devotion);
            ptr->setMediator(mediator);
            break;
        }
        case CommonClass::TheMarathoner: {
            ptr = marathonerFactory->createObject(x, y, devotion);
            ptr->setMediator(mediator);
            break;
        }
        case CommonClass::TheTough: {
            ptr = toughFactory->createObject(x, y, devotion);
            ptr->setMediator(mediator);
            break;
        }
        case CommonClass::TheVampire: {
            ptr = vampireFactory->createObject(x, y, devotion);
            ptr->setMediator(mediator);
            break;
        }
        case CommonClass::SpikyTerrain: {
            ptr = spikyFactory->createObject(x, y, devotion);
            ptr->setMediator(mediator);
            break;
        }
        case CommonClass::SteepTerrain: {
            ptr = steepFactory->createObject(x, y, devotion);
            ptr->setMediator(mediator);
            break;
        }
        case CommonClass::HollyTerrain: {
            ptr = hollyFactory->createObject(x, y, devotion);
            ptr->setMediator(mediator);
            break;
        }
        case CommonClass::HealEntity: {
            ptr = healFactory->createObject(x, y, devotion);
            ptr->setMediator(mediator);
            break;
        }
        case CommonClass::TrapEntity: {
            ptr = trapFactory->createObject(x, y, devotion);
            ptr->setMediator(mediator);
            break;
        }
        case CommonClass::BlockEntity: {
            ptr = blockFactory->createObject(x, y, devotion);
            ptr->setMediator(mediator);
            break;
        }
        case CommonClass::PitEntity: {
            ptr = pitFactory->createObject(x, y, devotion);
            ptr->setMediator(mediator);
            break;
        }
        case CommonClass::Base: {
            auto bPtr = baseFactory->createBase(x, y, devotion);
            //std::cout << "CF USECOUNT" << bPtr.use_count() << std::endl;
            if (devotion == Devotion::Neuter)throw AttemptToSetNeutralBaseException("CommonFactory");
            setBase(bPtr, devotion);
            //std::cout << "CF USECOUNT" << bPtr.use_count() << std::endl;
            ptr = std::static_pointer_cast<GameObject>(bPtr);
            break;
        };
    }
    ptr->setFlyWeight(flyWeight.getFlyWeight(objectClass,devotion));
    return ptr;
}

void CommonFactory::setBase(std::shared_ptr<Base> base, Devotion devotion) {
    switch (devotion) {
        case Devotion::Neuter:
            throw AttemptToSetNeutralBaseException("CommonFactory");
            break;
        case Devotion::Light: {
            this->lightBase = base;
            break;
        }
        case Devotion::Dark: {
            this->darkBase = base;
            break;
        }
    }
    assert(base->getDevotion() == devotion);
    try {
        rangerFactory->setBase(base, devotion);
        powerfulFactory->setBase(base, devotion);
        agileFactory->setBase(base, devotion);
        marathonerFactory->setBase(base, devotion);
        toughFactory->setBase(base, devotion);
        vampireFactory->setBase(base, devotion);
    }catch (AttemptToSetNeutralBaseException &e){
        std::cerr<<e;
        exit(1);
    }
    base.reset();
}

void CommonFactory::setMediator(const std::shared_ptr<Mediator> &mediator) {
    CommonFactory::mediator = mediator;
}

const std::shared_ptr<Base> &CommonFactory::getLightBase() const {
    return lightBase;
}

const std::shared_ptr<Base> &CommonFactory::getDarkBase() const {
    return darkBase;
}




