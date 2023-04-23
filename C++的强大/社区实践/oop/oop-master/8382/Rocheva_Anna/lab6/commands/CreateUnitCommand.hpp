#ifndef LABOOP_CREATEUNITCOMMAND_HPP
#define LABOOP_CREATEUNITCOMMAND_HPP

#include "Command.hpp"

class CreateUnitCommand : public Command{
public:
    void execute(GameField *gameField, Base *base, LogProxy *logger, Base *enemyBase) final {
        std::cout << "1. Create Infantry." << std::endl;
        std::cout << "2. Create Guardsmen." << std::endl;
        std::cout << "3. Create Fighter." << std::endl;
        std::cout << "4. Create Tank." << std::endl;
        std::cout << "5. Create Scout." << std::endl;
        std::cout << "6. Create Cannon." << std::endl;
        int choice;
        std::cin >> choice;
        if (choice < 1 || choice > 6){
            std::cout << "Incorrect choice." << std::endl; return;
        }
        int x, y;

        int count = 0;
        while (count < 3){

            std::cout << "New coordinate:\nx:";
            std::cin >> x;
            std::cout << "y:";
            std::cin >> y;
            if (x < 0 || y < 0 || x > gameField->getWidth()-1 || y > gameField->getHeight()-1){
                std::cout << "Incorrect coordinates." << std::endl;
            }
            else if (base->getCoordinates()->x == x && base->getCoordinates()->y == y){
                std::cout << "Incorrect coordinates." << std::endl;
            }
            else if (enemyBase->getCoordinates()->x == x && enemyBase->getCoordinates()->y == y){
                std::cout << "Incorrect coordinates." << std::endl;
            }
            else if (abs(base->getCoordinates()->x - x) > 1 || abs(base->getCoordinates()->y - y) > 1){
                std::cout << "Too far. Enter new coordinates: " << std::endl;
                std::cout << "x:";
                std::cin >> x;
                std::cout << "y:";
                std::cin >> y;
            }
            else {
                break;
            }
            count++;
        }
        if (count == 3){
            std::cout << "Failed to create unit." << std::endl;
            return;
        }

        switch (choice){
            case 1:
                gameField->createUnit(INFANTRY, x, y, base);
                break;
            case 2:
                gameField->createUnit(GUARDSMEN, x, y, base);
                break;
            case 3:
                gameField->createUnit(FIGHTER, x, y, base);
                break;
            case 4:
                gameField->createUnit(TANK, x, y, base);
                break;
            case 5:
                gameField->createUnit(SCOUT, x, y, base);
                break;
            case 6:
                gameField->createUnit(CANNON, x, y, base);
                break;
        }
        if (logger->getFormat() == 1) {
            auto adapter = new Adapter(gameField);
            adapter->setLogger(logger);
            adapter->setLog(gameField->getLogString());
            adapter->print();
        } else {
            logger->setLog(gameField->getLogString());
            logger->print();
        }
    }
};


#endif //LABOOP_CREATEUNITCOMMAND_HPP
