#include "../headers/facade.hpp"
#include <iostream>
#include <string>
#include "../headers/serializer.hpp"
#include "../headers/parser.hpp"


Facade::Facade(uint32_t height, uint32_t width) {
    gc = GameSingleton::getGameController(height, width);
}

FacadeResultCode Facade::startGame() {
    std::cout << "The game has started!" << std::endl;
    return FacadeResultCode::SUCCESS;
}

FacadeResultCode Facade::updateState() {
    auto gameController = GameSingleton::getGameController();
    auto rules = gameController->getRules();
    auto radiant = gameController->getRadiantBase();
    auto dire = gameController->getDireBase();
    auto logger = gameController->getLogger();
    char result = rules->check(radiant, dire);
    if (result == 0) {
        logger->appendBuffer(std::string("Dire won!\n"));
        return FacadeResultCode::ERROR;
    }
    if (result == 1) {
        logger->appendBuffer(std::string("Radiant won!\n"));
        return FacadeResultCode::ERROR;
    }
    return FacadeResultCode::SUCCESS;
}

FacadeResultCode Facade::updateScreen() {
    for (int i = 0; i < 100; i++)
        std::cout << "\n";
    auto gameController = GameSingleton::getGameController();
    gameController->getLogger()->log();
    gameController->getLogger()->cleanBuffer();
    gameController->getMap()->draw();
    return FacadeResultCode::SUCCESS;
}

Facade::~Facade(){
    delete gc;
}

FacadeResultCode Facade::handle(char command, char arg) {
    FacadeResultCode res;
    switch (command)
    {
    case 'q':
        res = handleQ(arg);
        break;
    case 'e':
        res = handleE(arg);
        break;
    case 'p':
        res = handleP(arg);
        break;
    case 'l':
        res = handleL(arg);
        break;
    case 'v':
        res = handleV(arg);
        break;
    case 's':
        res = handleS(arg);
        break;
    case 'c':
        res = handleC(arg);
        break;
    //case 'b':
    //    res = handleB(arg);
    //    break;
    case 'm':
        res = handleM(arg);
        break;
    case 'a':
        res = handleA(arg);
        break;
    case 'n':
        res = handleN(arg);
        break;
    default:
        throw UnknownCommandException(command);
        break;
    }
    return res;
}

FacadeResultCode Facade::handleQ(char arg) {
    return FacadeResultCode::ERROR;
}

FacadeResultCode Facade::handleE(char arg) {
    try {
        gc->setCurrentHero(gc->getCurrentBase()->next());
    } catch (NoNextException& e) {
        gc->getLogger()->appendBuffer(e.what());
    } catch (std::exception& e) {
        gc->getLogger()->appendBuffer(e.what());
    }
    return FacadeResultCode::SUCCESS;
}

FacadeResultCode Facade::handleP(char arg) {
    if (gc->getCurrentBase() == gc->getRadiantBase()) {
        gc->setBase(gc->getDireBase());
        gc->setCurrentHero(gc->getDireBase()->getCurrentUnit());
    }
    else {
        gc->setBase(gc->getRadiantBase());
        gc->setCurrentHero(gc->getRadiantBase()->getCurrentUnit());
    }
    nullifystep();
    return FacadeResultCode::SUCCESS;
}

FacadeResultCode Facade::handleL(char arg) {
    std::string path;
    std::cout << "Input path: ";
    std::cin >> path;
    std::cin.get();
    try {
        auto unserializer = new Unserializer(path);
        unserializer->unserialize();
        delete unserializer;
    } catch (FileErrorException& e) {
        gc->getLogger()->appendBuffer(e.what());
        return FacadeResultCode::ERROR;
    } catch (UnserializerException& e) {
        gc->getLogger()->appendBuffer(e.what());
        return FacadeResultCode::ERROR;
    } catch (std::exception& e) {
        gc->getLogger()->appendBuffer(e.what());
        return FacadeResultCode::ERROR;
    }
    return FacadeResultCode::SUCCESS;
}

FacadeResultCode Facade::handleV(char arg) {
    try {
        if (arg == 't') {
            gc->setLogger(new TerminalLogger());
        }
        if (arg == 'f') {
            gc->setLogger(new FileLogger());
        }
    } catch (FileErrorException& e) {
        gc->getLogger()->appendBuffer(e.what());
        return FacadeResultCode::ERROR;
    } catch (std::exception& e) {
        gc->getLogger()->appendBuffer(e.what());
        return FacadeResultCode::ERROR;
    }
    return FacadeResultCode::SUCCESS;
}

FacadeResultCode Facade::handleS(char arg) {
    std::string path;
    std::cout << "Input path: ";
    std::cin >> path;
    std::cin.get();
    try {
        auto serializer = new Serializer(path);
        serializer->serialize();
        delete serializer;
    } catch (FileErrorException& e) {
        gc->getLogger()->appendBuffer(e.what());
        return FacadeResultCode::ERROR;
    } catch (std::exception& e) {
        gc->getLogger()->appendBuffer(e.what());
        return FacadeResultCode::ERROR;
    }
    return FacadeResultCode::SUCCESS;
}

FacadeResultCode Facade::handleC(char arg) {
    if (arg == 'b') {
        Unit* u = gc->getCurrentBase()->createUnit(ObjectType::BOGATYR, new UnitParamList(
            ObjectType::BOGATYR,
            std::string("BOGATYR") + std::to_string(iter)
        ));
        gc->setCurrentHero(u);
    }
    if (arg == 'm') {
        Unit* u = gc->getCurrentBase()->createUnit(ObjectType::MULTIARCHER, new UnitParamList(
            ObjectType::MULTIARCHER,
            std::string("MULTIARCHER") + std::to_string(iter)
        ));
        gc->setCurrentHero(u);
    }
    if (arg == 'w') {
        Unit* u = gc->getCurrentBase()->createUnit(ObjectType::WINDARCHER, new UnitParamList(
            ObjectType::WINDARCHER,
            std::string("WINDARCHER") + std::to_string(iter)
        ));
        gc->setCurrentHero(u);
    }
    if (arg == 't') {
        Unit* u = gc->getCurrentBase()->createUnit(ObjectType::TAMPLIER, new UnitParamList(
            ObjectType::TAMPLIER,
            std::string("TAMPLIER") + std::to_string(iter)
        ));
        gc->setCurrentHero(u);
    }
    step();
    return FacadeResultCode::SUCCESS;
}

FacadeResultCode Facade::handleB(char arg) {
    if (arg == 'd') {
        gc->getDireBase()->describe();
    }
    if (arg == 'r'){
        gc->getRadiantBase()->describe();
    }
    return FacadeResultCode::SUCCESS;
}

FacadeResultCode Facade::handleM(char arg) {
    try {
        if (arg == 'w') {
            gc->getCurrentHero()->moveUp();
        }
        if (arg == 'a') {
            gc->getCurrentHero()->moveLeft();
        }
        if (arg == 'd') {
            gc->getCurrentHero()->moveRight();
        }
        if (arg == 's') {
            gc->getCurrentHero()->moveDown();
        }
    } catch (NoCurrentPlayerException& e) {
        gc->getLogger()->appendBuffer(e.what());
    }
    step();
    return FacadeResultCode::SUCCESS;
}

FacadeResultCode Facade::handleA(char arg) {
    try {
        auto position = gc->getObjectStorage()->getCoords(gc->getCurrentHero());
        gc->getCurrentHero()->attack(position.first, position.second);
    } catch (NoCurrentPlayerException& e) {
        gc->getLogger()->appendBuffer(e.what());
    }
    step();
    return FacadeResultCode::SUCCESS;
}

FacadeResultCode Facade::handleN(char arg) {
    try {
        auto unserializer = new Unserializer(std::string("saves/newgame.sav"));
        unserializer->unserialize();
        delete unserializer;
        nullifystep();
    } catch (FileErrorException& e) {
        gc->getLogger()->appendBuffer(e.what());
        return FacadeResultCode::ERROR;
    } catch (UnserializerException& e) {
        gc->getLogger()->appendBuffer(e.what());
        return FacadeResultCode::ERROR;
    } catch (std::exception& e) {
        gc->getLogger()->appendBuffer(e.what());
        return FacadeResultCode::ERROR;
    }
    return FacadeResultCode::SUCCESS;
}

void Facade::inc() {
    iter++;
}

void Facade::step() {
    steps++;
}

void Facade::nullifystep() {
    steps = 0;
}

void Facade::log() {
    gc->getLogger()->log();
}

FacadeResultCode Facade::mainLoop() {
    std::string commandBuffer;
    CommandParser* commandParser = new CommandParser(); 
    ParsedStruct command = {'.', '.'};
    while (1) {
        inc();
        handleB(gc->getCurrentBase() == gc->getDireBase() ? 'd' : 'r');
        updateScreen();
        std::cout << "Command:";
        std::getline(std::cin, commandBuffer);
        try {
            command = commandParser->parse(commandBuffer);
        } catch(UnknownCommandException& e) {
            gc->getLogger()->appendBuffer(e.what());
        } catch (const std::exception& e) {
            std::cout << "Error!" << e.what() <<  std::endl;
            break;
        }
        try {
            auto res = handle(command.command, command.arg);
            if (res == FacadeResultCode::ERROR){
                log();
                break;
            }
        } catch (UnknownCommandException& e) {
            gc->getLogger()->appendBuffer(e.what());
        }
        try {
            auto res = updateState();
            if (res == FacadeResultCode::ERROR){
                log();
                break;
            }
        } catch (std::exception& e) {
            gc->getLogger()->appendBuffer(e.what());
            break;
        }
        if (steps % gc->getRules()->getRule()->getMovesOnIter() == 0 && steps != 0)
            handleP();
        command = {'.', '.'};
    }
    delete commandParser;
    return FacadeResultCode::SUCCESS;
}