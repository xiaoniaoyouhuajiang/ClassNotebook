#include "Manager.hpp"

void Manager::startGame(Rules *rules1) {
    rules = rules1;
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

    std::cout << "===First gamer===" << std::endl;
    createGamer();
    std::cout << "===Second gamer:===" << std::endl;
    createGamer();

    startCommand = new StartGameCommand;
    setLogger();
    startCommand->execute(gameField, nullptr, proxy, nullptr);
    setBases();
    printField();
}

void Manager::setBases() {

    if (!bases.empty()){
        for (auto & base : bases){
            (gameField->getCell(base.second->getCoordinates()->x, base.second->getCoordinates()->y))->deleteBase();
            bases[base.first]->deleteBase();
        }
    }

    std::vector<Gamer*> gamerNames;
    for (auto & gamer : bases)
        gamerNames.push_back(gamer.first);

    switch (rules->getStartCondition()){
        case ANGLE: {
            gameField->setBase(0, 0);
            bases[gamerNames.front()]->setCoordinates(0, 0);
            bases[gamerNames.front()]->setExistVal();
            proxy->setLog("The base of " + gamerNames.front()->getGamerName() + " is set in a cell (0,0)");
            std::cout << "The base of " << gamerNames.front()->getGamerName() << " is set in a cell (0,0)" << std::endl;
            proxy->print();
            int x = gameField->getWidth() - 1;
            int y = gameField->getHeight() - 1;
            gameField->setBase(x, y);
            bases[gamerNames.back()]->setCoordinates(x, y);
            bases[gamerNames.back()]->setExistVal();
            proxy->setLog(
                    "The base of " + gamerNames.back()->getGamerName() + " is set in a cell (" + std::to_string(x) +
                    "," + std::to_string(y) + ")");
            std::cout << "The base of " << gamerNames.back()->getGamerName() << " is set in a cell (" << x << "," << y << ")" << std::endl;
            break;
        }
        case CENTER: {
            int x = (gameField->getWidth()-1)/2-1;
            int y = (gameField->getHeight()-1)/2-1;
            if (y == 0){
                y++;
            }
            gameField->setBase(x, y);
            bases[gamerNames.front()]->setCoordinates(x, y);
            bases[gamerNames.front()]->setExistVal();
            proxy->setLog(
                    "The base of " + gamerNames.front()->getGamerName() + " is set in a cell (" + std::to_string(x) +
                    "," + std::to_string(y) + ")");
            std::cout << "The base of " << gamerNames.front()->getGamerName() << " is set in a cell (" << x << "," << y << ")" << std::endl;
            proxy->print();
            x = (gameField->getWidth()-1)/2+1;
            y = (gameField->getHeight()-1)/2+1;
            gameField->setBase(x, y);
            bases[gamerNames.back()]->setCoordinates(x, y);
            bases[gamerNames.back()]->setExistVal();
            proxy->setLog(
                    "The base of " + gamerNames.back()->getGamerName() + " is set in a cell (" + std::to_string(x) +
                    "," + std::to_string(y) + ")");
            std::cout << "The base of " << gamerNames.back()->getGamerName() << " is set in a cell (" << x << "," << y << ")" << std::endl;
            break;
        }
    }
    proxy->print();
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
    if (choice == 1 || choice == 2){
        std::cout << "With writing field status?" << std::endl;
        std::cout << "1: With writing\nother: Without writing" << std::endl;
        std::cin >> choice;
        if (choice == 1){
            proxy->setFormat(1);
        } else {
            proxy->setFormat(0);
        }
    }
}

void Manager::printMenu() {

    std::cout << "====================" << std::endl;
    std::cout << "1. Create new unit." << std::endl;
   // std::cout << "2. Delete unit." << std::endl;
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
    std::cout << "13. Print base coordinates." << std::endl;
    std::cout << "14. Attack enemy base." << std::endl;
    std::cout << "20. Start new game." << std::endl;
    std::cout << "0. Finish this game." << std::endl;
    std::cout << "====================" << std::endl;
}

void Manager::makeChoice() {
    int choice = 1;
    bool next = true;
    int currentGamer = 1;
    int enemy = 0;
    while (choice > 0){
        if (next){
            enemy = currentGamer;
            currentGamer = rules->getCurrentGamer();
        }
        std::cout << gamers[currentGamer]->getGamerName() << "'s turn:" << std::endl;
        std::cin >> choice;
        switch (choice){
            case 1:
                if (!(bases[gamers[currentGamer]]->isExist())){
                    std::cout << "No base to create new unit." << std::endl;
                    next = false;
                    break;
                }
                createUnitCommand = new CreateUnitCommand;
                proxy->setLog(gamers[currentGamer]->getGamerName() + " creates new unit.");
                proxy->print();
                createUnitCommand->execute(gameField, bases[gamers[currentGamer]], proxy, bases[gamers[enemy]]);
                next = true;
                if (checkWin(currentGamer, enemy)){
                    return;
                }
                break;

            case 2:
                deleteUnitCommand = new DeleteUnitCommand;
                proxy->setLog(gamers[currentGamer]->getGamerName() + " deletes unit.");
                proxy->print();
                deleteUnitCommand->execute(gameField, bases[gamers[currentGamer]], proxy, bases[gamers[enemy]]);
                next = true;
                if (checkWin(enemy, currentGamer)){
                    return;
                }
                break;
            case 3:
                moveUnitCommand = new MoveUnitCommand;
                proxy->setLog(gamers[currentGamer]->getGamerName() + " moves unit.");
                proxy->print();
                moveUnitCommand->execute(gameField, bases[gamers[currentGamer]], proxy, bases[gamers[enemy]]);
                next = true;
                break;
            case 4:
                attackUnitCommand = new AttackUnitCommand;
                proxy->setLog(gamers[currentGamer]->getGamerName() + " want to attacks another unit.");
                proxy->print();
                attackUnitCommand->execute(gameField, bases[gamers[currentGamer]], proxy, bases[gamers[enemy]]);
                next = true;
                if (checkWin(currentGamer, enemy)){
                    return;
                }
                break;
            case 5:
                actionWithObjectCommand = new ActionWithObjectCommand;
                proxy->setLog(gamers[currentGamer]->getGamerName() + " wants to make action of his unit with the object.");
                proxy->print();
                actionWithObjectCommand->execute(gameField, bases[gamers[currentGamer]], proxy, bases[gamers[enemy]]);
                next = true;
                if (checkWin(currentGamer, enemy)){
                    return;
                }
                break;
            case 6:
                proxy->setLog(gamers[currentGamer]->getGamerName() + " prints the health of his base.");
                proxy->print();
                if (bases[gamers[currentGamer]]->isExist()){
                    std::cout << "Base health:" << std::endl;
                    std::cout << bases[gamers[currentGamer]]->getHealth()->getValue() << std::endl;
                }
                else {
                    std::cout << "Base doesnt exists." << std::endl;
                }
                next = false;
                break;
            case 7:
                proxy->setLog(gamers[currentGamer]->getGamerName() + " prints his units.");
                proxy->print();
                bases[gamers[currentGamer]]->printUnits();
                next = false;
                break;
            case 8:
                proxy->setLog(gamers[currentGamer]->getGamerName() + " prints game field.");
                proxy->print();
                printField();
                next = false;
                break;
            case 9:
                proxy->setLog(gamers[currentGamer]->getGamerName() + " prints units's attributes.");
                proxy->print();
                unitsAttributesCommand = new UnitsAttributesCommand;
                unitsAttributesCommand->execute(gameField, bases[gamers[currentGamer]], proxy, bases[gamers[enemy]]);
                next = false;
                break;
            case 10:
                proxy->setLog(gamers[currentGamer]->getGamerName() + " changes logger.");
                proxy->print();
                delete proxy;
                setLogger();
                next = false;
                break;
            case 11:
                proxy->setLog(gamers[currentGamer]->getGamerName() + " saves the game.");
                proxy->print();
                saveGame();
                next = false;
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
            case 13:{
                if (bases[gamers[currentGamer]]->isExist()){
                    int name = currentGamer;
                    std::cout << "Base of gamer " << gamers[name]->getGamerName() << " have coordinates (";
                    std::cout << bases[gamers[name]]->getCoordinates()->x << ",";
                    std::cout << bases[gamers[name]]->getCoordinates()->y << ")" << std::endl;
                }
                else {
                    std::cout << "Base doesnt exists." << std::endl;
                }
                next = false;
                break;
            }
            case 14:{
                attackBaseCommand = new AttackBaseCommand;
                proxy->setLog(gamers[currentGamer]->getGamerName() + " want to attacks enemy base.");
                proxy->print();
                attackBaseCommand->execute(gameField, bases[gamers[currentGamer]], proxy, bases[gamers[enemy]]);
                next = true;
                if (checkWin(currentGamer, enemy)){
                    return;
                }
                break;
            }
            case 20:{
                std::cout << "Rules:" << std::endl;
                std::cout << "1: Kill units\n2: Damage bases\nother: auto(Kill units)" << std::endl;
                int rule;
                std::cin >> rule;
                switch (rule){
                    case 1:{
                        rules = new KillUnits;
                        break;
                    }
                    case 2:{
                        rules = new DamageBase;
                        break;
                    }
                    default:
                        rules = new KillUnits;
                }
                startCommand->execute(gameField, nullptr, proxy, nullptr);
                setBases();
                printField();
                break;
            }
        }
        if (choice != 0)
            printMenu();
    }
}

bool Manager::checkWin(int currentGamer, int enemy) {
    if (rules->isWin(bases[gamers[enemy]])){
        std::cout << "===========! This is " << gamers[currentGamer]->getGamerName() << "'s VICTORY !===========" << std::endl;
        proxy->setLog(gamers[currentGamer]->getGamerName() + " won.");
        proxy->print();
        return true;
    }
    std::swap(currentGamer, enemy);
    if (rules->isWin(bases[gamers[enemy]])){
        std::cout << "===========! This is " << gamers[currentGamer]->getGamerName() << "'s VICTORY !===========" << std::endl;
        proxy->setLog(gamers[currentGamer]->getGamerName() + " won.");
        proxy->print();
        return true;
    }
    return false;
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

            if ((gameField->getCell(i, j))->isBase()){
                std::cout << "+";
            }
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
    gamers[bases.size()-1] = gamer;
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

    int gamersCount = 0;
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

        gamers[gamersCount] = currentGamer;
        bases[currentGamer] = currentBase;
        gamersCount++;
    }

    if (first)
        setLogger();
    printField();
}

