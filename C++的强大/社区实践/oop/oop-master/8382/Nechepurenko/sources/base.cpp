#include "../headers/base.hpp"
#include "../headers/game.hpp"
#include "../headers/exceptions.hpp"

void Base::setCurrentUnit(Unit* unit) {
    currentUnit = unit;
}

int Base::getCurrent() {
    return curUnits;
}

int Base::getCreated() {
    return createdUnits;
}

int Base::getMax() {
    return maxUnits;
}

std::vector<Unit*> Base::getUnits() {
    return units;
}

void Base::setCurrent(int newCurrent) {
    curUnits = newCurrent;
}

void Base::setCreated(int newCreated) {
    createdUnits = newCreated;
}
void Base::setMax(int newMax) {
    maxUnits = newMax;
}

void Base::setDied(int newDied) {
    unitsDied = newDied;
}

int Base::getDied(){
    return unitsDied;
}

void Base::setUnits(const std::vector<Unit*> &units) {
    this->units.assign(units.begin(), units.end());
}

Unit* Base::getCurrentUnit() {
    //if (currentUnit) {
        return currentUnit;
    //}
    //throw 31;
}

Unit* Base::next() {
    if (units.size() > 0) {
        currentUnitPos = (1 + currentUnitPos) % units.size();
        auto name = (units[currentUnitPos])->getName();
        GameSingleton::getGameController()->getLogger()->appendBuffer(
            std::string("Switched to ") + name + std::string("\n")
        );
        return units[currentUnitPos];
    }
    throw NoNextException(this);
}

void DireBase::describe(){
    std::string res;
    res += std::to_string(curUnits) + " current units at Dire Base. Units are:\n";
    for (auto unit : units){
        if (unit == currentUnit) res += "* ";
        res += unit->getName() + "\n";
    }
    GameSingleton::getGameController()->getLogger()->appendBuffer(res);
}
void RadiantBase::describe(){
    std::string res;
    res += std::to_string(curUnits) + " current units at Radiant Base. Units are:\n";
    for (auto unit : units){
        if (unit == currentUnit) res += "* ";
        res += unit->getName() + "\n";
    }
    GameSingleton::getGameController()->getLogger()->appendBuffer(res);
}

Unit* DireBase::createUnit(ObjectType t, UnitParamList* p) {
    auto gc = GameSingleton::getGameController();
    if (createdUnits == maxUnits) {
        gc->getLogger()->appendBuffer(std::string("Youve reached the limit of units!\n"));
        return nullptr;
    }
    auto map = gc->getMap();
    auto width = map->getWidth();
    auto height = map->getHeight();
    auto cell = map->getMapCell(1, width - 2);
    if (cell){
        if (!cell->getObject()){
            curUnits++;
            createdUnits++;
            Unit* au = this->factory->createHero(t, p);
            gc->getObjectStorage()->registerObject(au, gc->getMap()->getMapCell(1, width - 2), this); // todo
            gc->getObjectStorage()->setBase(au, this);
            units.push_back(au);
            currentUnit = au;
            currentUnitPos = (size_t) units.size() - 1;
            GameSingleton::getGameController()->getLogger()->appendBuffer(std::string("Radiant Unit has been created!\n"));
            return au;
        } else {
            GameSingleton::getGameController()->getLogger()->appendBuffer(std::string("Cannot create new unit, prev stays at base\n"));
        }
    }
    return nullptr;
}
Unit* RadiantBase::createUnit(ObjectType t, UnitParamList* p) {
    auto gc = GameSingleton::getGameController();
    if (createdUnits == maxUnits) {
        gc->getLogger()->appendBuffer(std::string("Youve reached the limit of units!\n"));
        return nullptr;
    }
    auto map = gc->getMap();
    auto width = map->getWidth();
    auto height = map->getHeight();
    auto cell = map->getMapCell(height - 2, 1);
    if (cell){
        if (!cell->getObject()){
            curUnits++;
            createdUnits++;
            Unit* au = this->factory->createHero(t, p);
            gc->getObjectStorage()->registerObject(au, gc->getMap()->getMapCell(height - 2, 1), this); // todo
            gc->getObjectStorage()->setBase(au, this);
            units.push_back(au);
            currentUnit = au;
            currentUnitPos = (size_t) units.size() - 1;
            GameSingleton::getGameController()->getLogger()->appendBuffer(std::string("Radiant Unit has been created!\n"));
            return au;
        } else {
            GameSingleton::getGameController()->getLogger()->appendBuffer(std::string("Cannot create new unit, prev stays at base\n"));
        }
    }
    return nullptr;
}

void Base::unitDied(Unit* au) {
    curUnits--;
    unitsDied++;
}


void Base::deleteObject(Unit* o){
    GameSingleton::getGameController()->getObjectStorage()->deleteObject(o);
    GameSingleton::getGameController()->getObjectStorage()->eraseBase(o);
    units.erase(std::remove(units.begin(), units.end(), o), units.end());
    if ((int) units.size() == 0) {
        currentUnit = nullptr;
    } else {
        currentUnit = next();
    }
    currentUnitPos--;
    this->unitDied(o);
}
