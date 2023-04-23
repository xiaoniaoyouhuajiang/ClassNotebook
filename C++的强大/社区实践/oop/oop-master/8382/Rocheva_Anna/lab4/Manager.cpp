#include "Manager.hpp"

void Manager::startGame() {
    startCommand = new StartGameCommand;
    setLogger();
    startCommand->execute(gameField, nullptr, proxy);
    printField();
}

void Manager::setLogger(){
    std::cout << "Write logs in:" << std::endl;
    std::cout << "1: File\n2: Terminal\nother: No need to write logs" << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice){
        case 1:
            proxy = new LogProxy(FILE_LOG);
            break;
        case 2:
            proxy = new LogProxy(TERMINAL_LOG);
            break;
        default:
            proxy = new LogProxy(NO_LOG);
            break;
    }
    std::cout << "With writing field status?" << std::endl;
    std::cout << "1: With writing\nother: Without writing" << std::endl;
    std::cin >> choice;
    if (choice == 1){
        proxy->setFormat(1);
    }
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
    std::cout << "10. Change logger." << std::endl;
    std::cout << "0. Finish this game." << std::endl;
    std::cout << "====================" << std::endl;

}

void Manager::makeChoice() {
    int choice = 1;
    while (choice > 0){
        std::cin >> choice;
        switch (choice){
            case 1:
                createUnitCommand = new CreateUnitCommand;
                proxy->setLog("User creates new unit.");
                proxy->print();
                createUnitCommand->execute(gameField, bases.begin()->second, proxy);
                break;
            case 2:
                deleteUnitCommand = new DeleteUnitCommand;
                proxy->setLog("User deletes unit.");
                proxy->print();
                deleteUnitCommand->execute(gameField, bases.begin()->second, proxy);
                break;
            case 3:
                moveUnitCommand = new MoveUnitCommand;
                proxy->setLog("User moves unit.");
                proxy->print();
                moveUnitCommand->execute(gameField, bases.begin()->second, proxy);
                break;
            case 4:
                attackUnitCommand = new AttackUnitCommand;
                proxy->setLog("User want to attacks another unit.");
                proxy->print();
                attackUnitCommand->execute(gameField, bases.begin()->second, proxy);
                break;
            case 5:
                actionWithObjectCommand = new ActionWithObjectCommand;
                proxy->setLog("User wants to make action of his unit with the object.");
                proxy->print();
                actionWithObjectCommand->execute(gameField, bases.begin()->second, proxy);
                break;
            case 6:
                proxy->setLog("User prints the health of his base.");
                proxy->print();
                std::cout << "Base health:" << std::endl;
                std::cout << bases.begin()->second->getHealth()->getValue() << std::endl;
                break;
            case 7:
                proxy->setLog("User prints his units.");
                proxy->print();
                bases.begin()->second->printUnits();
                break;
            case 8:
                proxy->setLog("User prints game field.");
                proxy->print();
                printField();
                break;
            case 9:
                proxy->setLog("User prints units's attributes.");
                proxy->print();
                unitsAttributesCommand = new UnitsAttributesCommand;
                unitsAttributesCommand->execute(gameField, bases.begin()->second, proxy);
                break;
            case 10:
                proxy->setLog("User changes logger.");
                proxy->print();
                delete proxy;
                setLogger();
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

void Manager::createGamer() {
    std::cout << "Enter gamer name:" << std::endl;
    std::string name;
    std::cin >> name;
    auto gamer = new Gamer(name);
    bases[gamer] = new Base;
}

