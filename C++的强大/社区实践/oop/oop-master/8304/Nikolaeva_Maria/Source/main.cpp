#include <iostream>
#include "GameField/gamefield.h"
#include "Unit/swordsman.h"
#include "Unit/liveshield.h"
#include "Factory/unitfactory.h"
#include "Factory/liveshieldfactory.h"
#include "Factory/archerfactory.h"

#include <Windows.h>

void printField(GameField* field) {
    system("cls");
    std::string buffer;

    for (int i = 0; i < field->getHeight(); ++i) {
        for (int j = 0; j < field->getWidth(); ++j) {
            if (field->getCell(j, i)->isEmpty()) {
                buffer += ". ";
            }
            else {
                buffer += field->getCell(j, i)->getUnit()->draw();
                buffer += ' ';
            }
        }
        buffer += "\n";
    }

    std::cout << buffer;
}


void testIt() {
    GameField gameField(5, 5);
    Mediator mediator(&gameField);
    LiveShield unit(&mediator);

    gameField.addUnit(&unit);

    for (auto it = gameField.getIterator(); it.hasNext(); ++it) {
        if ((*it).isEmpty()) {
            std::cout << ". ";
        }
        else {
            std::cout << "U ";
        }
    }
}

void testFactory() {
    GameField gameField(5, 5);
    Mediator mediator(&gameField);

    UnitFactory* factory = new LiveShieldFactory;
    Unit* unit = factory->createUnit(&mediator);
    gameField.addUnit(unit);
    delete  factory;
    factory = new ArcherFactory;
    unit = factory->createUnit(&mediator);
    unit->setCoordinate(new Point2D(1,1));
    gameField.addUnit(unit);

    printField(&gameField);
}


int main()
{
    //testIt();
    testFactory();

    return 0;
}
