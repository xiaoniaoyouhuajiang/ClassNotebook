#include <iostream>
#include "Field/Field.h"
#include "Units/Factories/SwordsmenFactory.h"
#include "Units/Factories/WizardFactory.h"
#include "Units/Factories/ArcherFactory.h"


int main() {
    int x, y;
    std::cout << "Enter field size: ";
    std::cin >> x >> y;
    Field game(x, y);
    int key = 0;
    while (key != 4){
        game.print();
        std::cout << "\n> 1 - Create Unit\n";
        std::cout << "> 2 - Delete Unit\n";
        std::cout << "> 3 - Move Unit\n";
        std::cout << "> 4 - exit\n";
        std::cin >> key;
        int coordX, coordY;
        switch (key){
            case 1:
                int unit;
                std::cout << "Enter unitType: 1-Knight 2-Squire 3-Archmage 4-Druid 5-Bowman 6-Crossbowman\n";
                std::cin >> unit;
                std::cout << "\nEnter coordinates: ";
                std::cin >> coordX >> coordY;
                if (unit == 1) {
                    Knight *knight = SwordsmenFactory().createStrong();
                    if(!game.addObject(coordX, coordY, knight)){
                        std::cout << "\nFailed";
                        delete knight;
                    }
                } else if (unit == 2) {
                    Squire *squire = SwordsmenFactory().createCommon();
                    if(!game.addObject(coordX, coordY, squire)){
                        std::cout << "\nFailed";
                        delete squire;
                    }
                } else if (unit == 3) {
                    Archmage *arch = WizardFactory().createStrong();
                    if(!game.addObject(coordX, coordY, arch)){
                        std::cout << "\nFailed";
                        delete arch;
                    }
                } else if (unit == 4) {
                    Druid *druid = WizardFactory().createCommon();
                    if(!game.addObject(coordX, coordY, druid)){
                        std::cout << "\nFailed";
                        delete druid;
                    }
                } else if (unit == 5) {
                    Bowman *bowman = ArcherFactory().createCommon();
                    if(!game.addObject(coordX, coordY, bowman)){
                        std::cout << "\nFailed";
                        delete bowman;
                    }
                } else if (unit == 6) {
                    Crossbowman *crossbowman = ArcherFactory().createStrong();
                    if(!game.addObject(coordX, coordY, crossbowman)){
                        std::cout << "\nFailed";
                        delete crossbowman;
                    }
                } else
                    std::cout << "\nIncorrect unit";
                break;
            case 2:
                std::cout << "\nEnter coordinates of unit: ";
                std::cin >> coordX >> coordY;
                if(!game.deleteObject(coordX, coordY))
                    std::cout << "\nFailed";
                break;
            case 3:
                std::cout << "\nEnter coordinates of unit: ";
                std::cin >> coordX >> coordY;
                int toX, toY;
                std::cout << "\nEnter target coordinates: ";
                std::cin >> toX >> toY;
                if (!game.moveObject(game.getObject(coordX, coordY), toX, toY)){
                    std::cout << "\nFailed";
                }
                break;
            default:
                break;
        }
    }


    return 0;
}
