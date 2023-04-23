#include "Manager.hpp"

void Manager::startGame() {
    startCommand = new StartGameCommand;
    startCommand->execute(gameField);
    printField();
}

void Manager::printMenu() {

    std::cout << "====================" << std::endl;
    std::cout << "1. Create new unit." << std::endl;
    std::cout << "2. Delete unit." << std::endl;
    std::cout << "3. Move unit." << std::endl;
    std::cout << "4. Attack unit." << std::endl;
    std::cout << "5. New action with object" << std::endl;
    std::cout << "6. Print health of base." << std::endl;
    std::cout << "7. Print units in base." << std::endl;
    std::cout << "8. Print field." << std::endl;
    std::cout << "9. Print units attributes." << std::endl;
    std::cout << "0. Finish this game." << std::endl;
    std::cout << "====================" << std::endl;

}

void Manager::makeChoice() {

    int choice;
    while (choice > 0){
        std::cin >> choice;
        switch (choice){
            case 1:
                createUnitCommand = new CreateUnitCommand;
                createUnitCommand->execute(gameField);
                break;
            case 2:
                deleteUnitCommand = new DeleteUnitCommand;
                deleteUnitCommand->execute(gameField);
                break;
            case 3:
                moveUnitCommand = new MoveUnitCommand;
                moveUnitCommand->execute(gameField);
                break;
            case 4:
                attackUnitCommand = new AttackUnitCommand;
                attackUnitCommand->execute(gameField);
                break;
            case 5:
                actionWithObjectCommand = new ActionWithObjectCommand;
                actionWithObjectCommand->execute(gameField);
                break;
            case 6:
                std::cout << "Base health:" << std::endl;
                std::cout << gameField->getBase()->getHealth()->getValue() << std::endl;
                break;
            case 7:
                gameField->getBase()->printUnits();
                break;
            case 8:
                printField();
                break;
            case 9:
                unitsAttributesCommand = new UnitsAttributesCommand;
                unitsAttributesCommand->execute(gameField);
                break;
        }
        if (choice != 0)
            printMenu();
    }
}

void Manager::printField() {

    int fieldHeight = gameField->getHeight();
    int fieldWidth = gameField->getWidth();

    std::cout << "\n\tGame Field:\n";
    for (int i = 0; i < fieldHeight; i++) {
        for (int k = 0; k < fieldWidth; k++) {
            std::cout << "-------";
        }

        std::cout << std::endl;

        for (int j = 0; j < fieldWidth; j++) {
            std::cout << "|";

            std::cout << gameField->getCell(i, j)->getLandscape()->getName();
            std::cout << "    ";

            if ((gameField->getCell(i, j))->isBase())
                std::cout << "+";
            else if ((gameField->getCell(i, j))->isObject())
                std::cout << (gameField->getCell(i, j))->getObject()->getName();
            else
                std::cout << " ";

        }

        std::cout << "|" << std::endl;

        for (int j = 0; j < fieldWidth; j++) {

            std::cout << "|   ";

            if (!((gameField->getCell(i, j))->isEmpty()))
                std::cout << (gameField->getCell(i, j))->getUnit()->getName();
            else
                std::cout << " ";

            std::cout << "  ";
        }

        std::cout << "|" << std::endl;

        for (int j = 0; j < fieldWidth; j++) {
            std::cout << "|";
            std::cout << "      ";
        }
        std::cout << "|" << std::endl;


        if (i == fieldHeight - 1) {
            for (int k = 0; k < fieldWidth; k++) {
                std::cout << "-------";
            }
        }
    }
    std::cout << std::endl << std::endl;

}
