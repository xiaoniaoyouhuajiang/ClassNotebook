#include <iostream>
#include "Game/Game.h"
#include "OtherClasses/NeutralObjects/Generators/ArmorGenerator.h"
#include "OtherClasses/Landscapes/ProxyLandscape.h"
#include "OtherClasses/NeutralObjects/Generators/HealthGenerator.h"
#include "OtherClasses/NeutralObjects/Generators/GoldGenerator.h"
#include "OtherClasses/NeutralObjects/Client.h"
#include "Logging/TerminalLog/TerminalLog.h"
#include "Logging/FileLog/FileLog.h"
#include "Logging/ProxyLogger/ProxyLogger.h"

int main() {

    Game *game = new Game();

    game->addKnight(1, 1);
    game->addMagician(2, 1);
    game->addKing(2, 2);
    game->addArcher(3, 4);
    game->addSwordsmen(5, 4);
    game->addSpearmen(6, 4);
//    game->updateUnitPosition(6,4,6,5);
    game->attackUnit(5,4,6,4);

    delete game;

    /*ProxyLogger proxyLogger;
    proxyLogger.logMessage("hello");
    proxyLogger.logMessage("from user");
    proxyLogger.switchWriteMode();
    proxyLogger.logMessage("buy");
    proxyLogger.logMessage("buy");*/

    /*TerminalLog terminalLog;
    terminalLog.logMessage("hello");
    terminalLog.logMessage("user is done");*/

    //terminalLog.setLogMessage("hello from user");
//    std::cout << terminalLog;
    //terminalLog.log();

    /*FileLog fileLog("C:\\Users\\Alex\\Desktop\\out.txt");
    fileLog.logMessage("hello from user");
    fileLog.logMessage("user is done");*/
    /*fileLog.setLogMessage("hello");
    fileLog.log();

    fileLog.setLogMessage("hello");
    fileLog.log();
    fileLog.setLogMessage("hello");

    fileLog.log();*/



    //Game *game = new Game();


    // Демонстрационный пример работы генератора черех перегрузку оператора []
    /* auto *unitFactory = new UnitFactory();
     Swordmen *swordsmen = unitFactory->getSwordsmen();
     std::cout << swordsmen->getArmor() << "\n";
     auto *armorGenerator = new ArmorGenerator;
     (*armorGenerator)[swordsmen->getArmorForGenerator()];
     std::cout << swordsmen->getArmor();*/

    /*auto *unitFactory = new UnitFactory();
    Unit *archer = unitFactory->getArcher(0, 0);
    Landscape *forest = new ForestLandscape();
    auto *proxyLandscape = new ProxyLandscape(forest);
    std::cout << archer->getAttackBonus() << std::endl;

    proxyLandscape->setBonus(archer);

    std::cout << archer->getAttackBonus() << std::endl;*/

    /* auto *unitFactory = new UnitFactory();
     Unit *archer = unitFactory->getArcher(0, 0);
     auto *armorGenerator = new ArmorGenerator;
     auto *healthGenerator = new HealthGenerator;
     auto *goldGenerator = new GoldGenerator;

     std::cout << archer->getHealth() << " " << archer->getArmor() << "\n";

     Client client;
     client.setStrategy(healthGenerator);
     client.useStrategy(archer);

     std::cout << archer->getHealth() << " " << archer->getArmor() << "\n";*/


    /*int array [4];
    game->getInformationAboutEnvironment(array,9,4);

    for (int i = 0; i < 4; ++i) {
        std::cout << array[i] << " ";
    }*/

    //std::cout << "\n";

    //delete (game);

    /*if (typeid(*swordsmen) == typeid(RangedUnit)) {
        return 25;
    } else {
        return 0;
    }*/

    //std::cout << std::is_same<decltype(swordsmen), class Archer>::value <<std::endl;;

    //if(dynamic_cast<AttackUnitArmor *>(swordsmen) != nullptr) std::cout << "br";
    return 0;
}