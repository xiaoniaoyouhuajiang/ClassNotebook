#include "objectFabric.h"

Archer* objectFabric::createArcher() {
    Archer* newArcher = new Archer();
    Health setHealth(newArcher);
    newArcher->health = setHealth._health;
    newArcher->shieldEnabled = false;
    return newArcher;
}
CrossBowMan* objectFabric::createCrossbowman() {
    CrossBowMan* newCrossBowMan = new CrossBowMan();
    Health setHealth(newCrossBowMan);
    newCrossBowMan->health = setHealth._health;
    newCrossBowMan->shieldEnabled = false;
    return newCrossBowMan;
}
HeavyRider* objectFabric::createHeavyRider() {
    HeavyRider* newHeavyRider = new HeavyRider();
    Health setHealth(newHeavyRider);
    newHeavyRider->health = setHealth._health;
    newHeavyRider->shieldEnabled = false;
    return newHeavyRider;
}
LightRider* objectFabric::createLightRider() {
    LightRider* newLightRider = new LightRider();
    Health setHealth(newLightRider);
    newLightRider->health = setHealth._health;
    newLightRider->shieldEnabled = false;
    return newLightRider;
}
Knight* objectFabric::createKnight() {
    Knight* newKnight = new Knight();
    Health setHealth(newKnight);
    newKnight->health = setHealth._health;
    newKnight->shieldEnabled = false;
    return newKnight;
}
SpearMan* objectFabric::createSpearman() {
    SpearMan* newSpearMan = new SpearMan;
    Health setHealth(newSpearMan);
    newSpearMan->health = setHealth._health;
    newSpearMan->shieldEnabled = false;
    return newSpearMan;
}
Base* objectFabric::createBase(int x, int y, bool numbase) {
    Base* createBase = new Base(x, y, numbase);
    Health setHealth(createBase);
    createBase->health = setHealth._health;
    return createBase;
}
PowerUp* objectFabric::createTree(){
    PowerUp* newPowerUp = new PowerUp();
    return newPowerUp;
}
Shield* objectFabric::createChield(){
    Shield* newShield = new Shield();
    return newShield;
}
MedicineChest* objectFabric::createMedicineChest(){
    MedicineChest* newMedicineChest = new MedicineChest();
    return newMedicineChest;
}
Horse* objectFabric::createHorse(){
    Horse* newHorse = new Horse();
    return newHorse;
}
