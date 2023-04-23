//
// Created by Mila
//

#include "Game.h"
#include "../NeutralObject/MedicalKit.h"
#include "../NeutralObject/PowerPotion.h"
#include "../NeutralObject/Shild.h"
#include "../NeutralObject/Stone.h"

Game::Game(int height, int width, int controlMax, int baseX, int baseY, int controlUnits) {
    counter = 0;
    field = new Field(height, width, controlMax);
    units = new Unit*[field->getControlMax()];//выделяем место для массива
    base = new Base(field, units, ++counter, controlUnits);//controlUnits всегда должен быть минимум на 1 меньше чем controlMax
    field->appendElement(baseX,baseY,base);

}

Game::~Game() {
    for (int i = base->getCountUnit(); i > -1 ; i--) {

        if(dynamic_cast<Archer *>(units[i]) != nullptr) {
            auto *archer = dynamic_cast<Archer *>(units[i]);
            delete archer;
        }
        else if(dynamic_cast<Magician *>(units[i]) != nullptr) {
            auto *magician = dynamic_cast<Magician *>(units[i]);
            delete magician;
        }
        else if(dynamic_cast<ElfOnUnicorn *>(units[i]) != nullptr) {
            auto *elfOnUnicorn = dynamic_cast<ElfOnUnicorn *>(units[i]);
            delete elfOnUnicorn;
        }
        else if(dynamic_cast<KnightOnHorse *>(units[i]) != nullptr) {
            auto *knightOnHorse = dynamic_cast<KnightOnHorse *>(units[i]);
            delete knightOnHorse;
        }
        else if(dynamic_cast<Gnome *>(units[i]) != nullptr) {
            auto *gnome = dynamic_cast<Gnome *>(units[i]);
            delete gnome;
        }
        else if(dynamic_cast<Knight *>(units[i]) != nullptr) {
            auto *knight = dynamic_cast<Knight *>(units[i]);
            delete knight;
        }
        //delete(units[i]);

    }
    delete(units);
    delete(field);
    delete(base);
}

void Game::createArcher(int x, int y) {
    base->createUnit(1,x,y);
}

void Game::createMagician(int x, int y) {
    base->createUnit(2,x,y);
}

void Game::createElfOnUnicorn(int x, int y) {
    base->createUnit(4,x,y);
}

void Game::createKnightOnHorse(int x, int y) {
    base->createUnit(3,x,y);
}

void Game::createKnight(int x, int y) {
    base->createUnit(5,x,y);
}

void Game::createGnome(int x, int y) {
    base->createUnit(6,x,y);
}

void Game::moveUnit(int lastX, int lastY, int newX, int newY) {
    field->move(lastX,lastY,newX,newY);
}

void Game::attack(int lastX, int lastY, int newX, int newY) {
    field->attack(lastX, lastY, newX, newY);
}

void Game::printField() {
    field->drawField();

}

void Game::createMedicalKit(int x, int y) {
    field->addNeutralObject(x,y, new MedicalKit());
}

void Game::createPowerPotion(int x, int y) {
    field->addNeutralObject(x,y, new PowerPotion());
}

void Game::createShild(int x, int y) {
    field->addNeutralObject(x,y, new Shild());

}

void Game::createStone(int x, int y) {
    field->addNeutralObject(x,y, new Stone());
}

void Game::infoAboutBase() {
    base->sayInfoAboutBase();

}
