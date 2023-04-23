#include <iostream>
#include "Field/Field.h"

#include "AbstractFactory/ConcreteFactoryMagicHero.h"
#include "AbstractFactory/ConcreteFactoryStrongHero.h"
#include "Base/Base.h"
#include "NeutralObject/NeutralObject.h"
#include "NeutralObject/MedicalKit.h"
#include "NeutralObject/PowerPotion.h"
#include "NeutralObject/Stone.h"
#include "Game/Game.h"

int main() {
    //system("chcp 65001");

    std::cout << "Hello, Player!" << std::endl;
    Game* game = new Game(12,12,5,0,0,4);
    game->createElfOnUnicorn(1,5);
    game->createMagician(7,9);
    game->createArcher(4,0);
    game->attack(7,9,4,0);
    game->createMedicalKit(2,2);
    game->createPowerPotion(6,6);
    game->createShild(10,10);
    game->createStone(2,8);
    game->infoAboutBase();
    game->printField();
    delete game;
    return 0;
}
