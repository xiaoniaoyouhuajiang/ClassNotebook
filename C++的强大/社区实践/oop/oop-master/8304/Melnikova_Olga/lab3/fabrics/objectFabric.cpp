#include "objectFabric.h"

Archer* objectFabric::createArcher(int num) {
    Archer* newArcher = new Archer();
    newArcher->isUnit = true;
    Health setHealth(newArcher);
    newArcher->health = setHealth._health;
    newArcher->shieldEnabled = false;
    newArcher->numBase = num;
    newArcher->isArcher = true;
    return newArcher;
}
CrossBowMan* objectFabric::createCrossbowman(int num) {
    CrossBowMan* newCrossBowMan = new CrossBowMan();
    newCrossBowMan->isUnit = true;
    Health setHealth(newCrossBowMan);
    newCrossBowMan->health = setHealth._health;
    newCrossBowMan->shieldEnabled = false;
    newCrossBowMan->numBase = num;
    newCrossBowMan->isCrossBowMan = true;
    return newCrossBowMan;
}
HeavyRider* objectFabric::createHeavyRider(int num) {
    HeavyRider* newHeavyRider = new HeavyRider();
    newHeavyRider->isUnit = true;
    Health setHealth(newHeavyRider);
    newHeavyRider->health = setHealth._health;
    newHeavyRider->shieldEnabled = false;
    newHeavyRider->numBase = num;
    newHeavyRider->isHeavyRider = true;
    return newHeavyRider;
}
LightRider* objectFabric::createLightRider(int num) {
    LightRider* newLightRider = new LightRider();
    newLightRider->isUnit = true;
    Health setHealth(newLightRider);
    newLightRider->health = setHealth._health;
    newLightRider->shieldEnabled = false;
    newLightRider->numBase = num;
    newLightRider->isLightRider = true;
    return newLightRider;
}
Knight* objectFabric::createKnight(int num) {
    Knight* newKnight = new Knight();
    newKnight->isUnit = true;
    Health setHealth(newKnight);
    newKnight->health = setHealth._health;
    newKnight->shieldEnabled = false;
    newKnight->numBase = num;
    newKnight->isKnight = true;
    return newKnight;
}
SpearMan* objectFabric::createSpearman(int num) {
    SpearMan* newSpearMan = new SpearMan;
    newSpearMan->isUnit = true;
    Health setHealth(newSpearMan);
    newSpearMan->health = setHealth._health;
    newSpearMan->shieldEnabled = false;
    newSpearMan->numBase = num;
    newSpearMan->isSpearMan = true;
    return newSpearMan;
}
Base* objectFabric::createBase(int x, int y, bool numbase) {
    Base* createBase = new Base(x, y, numbase);
    createBase->isBase = true;
    Health setHealth(createBase);
    createBase->health = setHealth._health;
    createBase->numBase = numbase;
    return createBase;
}
PowerUp* objectFabric::createPowerUp(){
    PowerUp* newPowerUp = new PowerUp();
    newPowerUp->isNeutral = true;
    newPowerUp->numBase = -1;
    return newPowerUp;
}
Shield* objectFabric::createShield(){
    Shield* newShield = new Shield();
    newShield->isNeutral = true;
    newShield->numBase = -1;
    return newShield;
}
MedicineChest* objectFabric::createMedicineChest(){
    MedicineChest* newMedicineChest = new MedicineChest();
    newMedicineChest->isNeutral = true;
    newMedicineChest->numBase = -1;
    return newMedicineChest;
}
Horse* objectFabric::createHorse(){
    Horse* newHorse = new Horse();
    newHorse->isNeutral = true;
    newHorse->numBase = -1;
    return newHorse;
}
