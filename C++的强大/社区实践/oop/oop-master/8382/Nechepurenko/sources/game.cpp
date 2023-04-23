#include "../headers/game.hpp"
#include "../headers/exceptions.hpp"


Map* GameController::getMap() {
    return map;
}

ObjectStorage* GameController::getObjectStorage() {
    return objectStorage;
}

void GameController::moveObject(Object* au, std::shared_ptr<MapCell> map_cell) {
    if (!au)
        return;
    std::shared_ptr<MapCell> mc = this->objectStorage->getCellPtr(au);
    mc->setObject(nullptr);
    map_cell->setObject(au);
    this->objectStorage->setObject(au, map_cell);
    return;
}

Base* GameController::getCurrentBase() {
    return currentBase;
}
DireBase* GameController::getDireBase() {
    return dire;
}
RadiantBase* GameController::getRadiantBase() {
    return radiant;
}
void GameController::setBase(Base* newBase) {
    currentBase = newBase;
}
Unit* GameController::getCurrentHero() {
    if (!currentHero)
        throw NoCurrentPlayerException(getCurrentBase());
    return currentHero;
}
void GameController::setCurrentHero(Unit* newHero) {
    currentHero = newHero;
}

GameController::GameController(uint32_t map_width, uint32_t map_height){
    this->map = new Map(map_width, map_height);
    this->objectStorage = new ObjectStorage();
    this->rules = new GameRules<FirstRule>();
    this->radiant = new RadiantBase(this->rules->getRule()->getMaxUnits());
    this->dire = new DireBase(this->rules->getRule()->getMaxUnits());
    this->objectStorage->setObject(radiant, map->getMapCell(map->getHeight() - 1, 0));
    this->objectStorage->setObject(dire, map->getMapCell(0, map->getWidth() - 1));
    if (this->rules->getRule()->getWhosFirst() == 1){
        this->currentBase = radiant;
    } else {
        this->currentBase = dire;
    }
}

GameController::~GameController(){
    delete this->map;
    delete this->logger;
    delete this->rules;
}

void GameController::setLogger(Logger* newLogger) {
    delete logger;
    logger = newLogger;
}

Logger* GameController::getLogger() {
    return logger;
}


GameController* GameSingleton::getGameController(uint32_t map_height, uint32_t map_width){
    if (gc == nullptr) {
        gc = new GameController(map_height, map_width);
    }
    return gc;
}

void GameSingleton::deleteGameController() {
    delete gc;
    gc = nullptr;
}
GameController* GameSingleton::gc = nullptr;

int Rule::getMaxUnits() {
    return maxUnits;
}

int Rule::getMovesOnIter() {
    return movesOnIter;
}

int Rule::getWhosFirst() {
    return firstMove;
}

char FirstRule::win(RadiantBase* radiant, DireBase* dire) {
    if (radiant->getCurrent() == 0 && radiant->getCreated() == maxUnits){
        return 0;
    }
    if (dire->getCurrent() == 0 && dire->getCreated() == maxUnits){
        return 1;
    }
    return 2;
}

char SecondRule::win(RadiantBase* radiant, DireBase* dire) {
    if (radiant->getDied() > 0){
        return 0;
    }
    if (dire->getDied() > 0){
        return 1;
    }
}

GameRules<FirstRule>* GameController::getRules() {
    return rules;
}