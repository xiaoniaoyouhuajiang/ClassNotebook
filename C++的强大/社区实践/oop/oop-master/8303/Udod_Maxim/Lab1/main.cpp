#include <iostream>
#include "GameField.h"
#include "Units/Archer/CrossBowMan.h"
#include "Units/Factory/ArcherFactory.h"
#include "Units/Factory/WizardFactory.h"
#include "Units/Factory/InfantryFactory.h"

void example1(){

    GameField field(3, 3);

    CrossBowMan *crossBowMan = ArcherFactory().createWeack();

    field.addObject(crossBowMan, 0, 0);

    for (auto *obj : field) {
        std::cout << obj << std::endl;
    }

    Point nextPoint(2, 2);
    field.moveObject(crossBowMan, nextPoint);

    std::cout << std::endl;
    for (auto *obj : field) {
        std::cout << obj << std::endl;
    }

    field.deleteObject(crossBowMan);

    std::cout << std::endl;
    for (auto *obj : field) {
        std::cout << obj << std::endl;
    }

}

void example2(){

    FireMage *mage = WizardFactory().createWeack();
    SwordMan *swordMan = InfantryFactory().createStrong();

    GameField fieldOne(2, 3);

    fieldOne.addObject(mage, 2, 2);
    fieldOne.addObject(mage, 2, 0);
    fieldOne.addObject(mage, 1, 2);

    fieldOne.addObject(swordMan, 1, 1);

    std::cout << std::endl;
    for (auto *obj : fieldOne) {
        std::cout << obj << std::endl;
    }

    GameField fieldTwo(fieldOne);
    std::cout << std::endl;
    for (auto *obj : fieldTwo) {
        std::cout << obj << std::endl;
    }

}

void example3(){

    BlockBowMan *blockBowMan = ArcherFactory().createStrong();
    FireMage *fireMage = WizardFactory().createWeack();
    SpearMan *spearMan = InfantryFactory().createWeack();
    SwordMan *swordMan = InfantryFactory().createStrong();

    GameField field(3);

    field.addObject(fireMage, 0, 0);
    field.addObject(blockBowMan, 0, 1);
    field.addObject(spearMan, 0, 2);
    field.addObject(swordMan, 1, 0);

    std::cout << std::endl;
    for (auto *obj : field) {
        std::cout << obj << std::endl;
    }

    Point p1(1, 0);
    Point p2(2, 0);
    field.moveObject(fireMage, p1);
    field.moveObject(fireMage, p2);

    std::cout << std::endl;
    for (auto *obj : field) {
        std::cout << obj << std::endl;
    }

}

int main() {

    example3();

    return 0;
}
