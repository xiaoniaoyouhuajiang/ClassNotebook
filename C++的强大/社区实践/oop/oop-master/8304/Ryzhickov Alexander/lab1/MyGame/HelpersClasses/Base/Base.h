//
// Created by Alex on 05.03.2020.
//

#ifndef MYGAME_BASE_H
#define MYGAME_BASE_H


#include <vector>
#include "../../Units/Unit.h"
#include "../../HelpersClasses/Factories/UnitFactory.h"
class Base{
private:
    const int xPosition;
    const int yPosition;
    int healthBase;
    const int maxCountUnitsOnBase;
    const int maxCountUnitsInGame;
    int countUnitsOnBase;
    int countUnitsInGame;
    int money;
    Unit **units;
    UnitFactory *factory;
public:
    explicit Base(Unit **units, int x,int y, int maxCountUnitsInGame);
    ~Base();
    void addSwordsmen();
    void addSpearmen();
    void addArcherWithShortBow();
    void addArcherWithLongBow();
    void addArbalester();
    void addHeavyCavalry();
    void addLightCavalry();
    void handleEvent(const Unit& unit);
    int getCountUnitsInGame() const;
    std::vector<int> vectorDeleteUnits;

    const int getXPosition() const;

    const int getYPosition() const;

private:
    void addUnit(Unit *unit);
};


#endif //MYGAME_BASE_H
