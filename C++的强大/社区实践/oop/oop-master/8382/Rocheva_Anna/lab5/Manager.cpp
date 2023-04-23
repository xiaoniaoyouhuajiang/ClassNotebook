#include "Manager.hpp"

void Manager::startGame() {
    std::cout << "Continue other game?\n1 - Yes\nOther - No" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice == 1){
        while(true){
            std::cout << "Enter path for state doc: (to create new game enter '+')" << std::endl;
            std::string statePath;
            std::cin >> statePath;
            if (statePath == "+")
                break;
            auto memento = new Memento(statePath);
            memento->loadGameFromDoc();
            if (memento->getCorrectFlag()){
                loadGame(memento, true);
                std::cout << "Game is load." << std::endl;
                return;
            }
            else {
                std::cout << "Not right format." << std::endl;
            }
        }
    }
    createGamer();
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
    } else {
        proxy->setFormat(0);
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
    std::cout << "11. Save this game." << std::endl;
    std::cout << "12. Load last saved game." << std::endl;
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
            case 11:
                proxy->setLog("User saves the game.");
                proxy->print();
                saveGame();
                break;
            case 12: {
                proxy->setLog("User loads the last game.");
                proxy->print();
                std::cout << "From doc or not?\n1 - from doc\nOther - not from doc" << std::endl;
                int docChoice;
                std::cin >> docChoice;
                if (docChoice == 1) {
                    while(true){
                        std::cout << "Enter path for state doc: (to undo action enter '-')" << std::endl;
                        std::string statePath;
                        std::cin >> statePath;
                        if (statePath == "-")
                            break;
                        auto memento = new Memento(statePath);
                        memento->loadGameFromDoc();
                        if (memento->getCorrectFlag()){
                            loadGame(memento, true);
                            std::cout << "Game is load." << std::endl;
                            break;
                        }
                        else {
                            std::cout << "Not right format." << std::endl;
                        }
                    }
                    break;
                }
                if (mementos.empty()) {
                    proxy->setLog("No saved games.");
                    proxy->print();
                    break;
                }
                loadGame(mementos.back(), false);
                mementos.pop_back();
                break;
            }
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

void Manager::saveGame() {
    std::cout << "Enter path (if you dont want to save game in a doc, enter '-'):" << std::endl;
    std::string path;
    std::cin >> path;

    auto memento = new Memento(path);
    memento->saveGame(gameField, bases);
    if (path == "-")
        mementos.push_back(memento);
}

void Manager::loadGame(Memento *memento, bool first) {

    auto gameState = new GameState;
    gameState = memento->getGameState();

    gameField = new GameField(gameState->size.first, gameState->size.second);
    for (int i = 0; i < gameField->getHeight(); i++)
        for (int j = 0; j < gameField->getWidth(); j++)
            gameField->getCell(i, j)->deleteObject();

    for (auto & land : gameState->lands){
        gameField->getCell(land.second->x, land.second->y)->setLandscape(land.first);
    }

    for (auto & obj : gameState->objects){
        gameField->getCell(obj.second->x, obj.second->y)->setObject(obj.first);
    }

    for (auto & gamer : gameState->bases){

        auto *currentGamer = new Gamer(gamer.first);
        auto *currentBase = new Base;

        currentBase->setCoordinates(gamer.second->coordinates->x, gamer.second->coordinates->y);
        gameField->getCell(gamer.second->coordinates->x, gamer.second->coordinates->y)->setBase();
        currentBase->setHealth(gamer.second->health);

        for (auto & unit : gamer.second->units){

            switch (unit->UnitName){
                case 0:
                    gameField->createUnit(INFANTRY, unit->coordinates->x, unit->coordinates->y, currentBase);
                    break;
                case 1:
                    gameField->createUnit(GUARDSMEN, unit->coordinates->x, unit->coordinates->y, currentBase);
                    break;
                case 2:
                    gameField->createUnit(FIGHTER, unit->coordinates->x, unit->coordinates->y, currentBase);
                    break;
                case 3:
                    gameField->createUnit(SCOUT, unit->coordinates->x, unit->coordinates->y, currentBase);
                    break;
                case 4:
                    gameField->createUnit(CANNON, unit->coordinates->x, unit->coordinates->y, currentBase);
                    break;
                case 5:
                    gameField->createUnit(TANK, unit->coordinates->x, unit->coordinates->y, currentBase);
                    break;
            }

            currentBase->updateUnitAttributes(gameField->getCell(unit->coordinates->x, unit->coordinates->y),
                    unit->attack, unit->defense, unit->health);
        }

        bases[currentGamer] = currentBase;
    }

    if (first)
        setLogger();
    printField();
}

