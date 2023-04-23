#include "Memento.hpp"

/*
 в документе:

 width, height
 land x y
 ...
 land x y
 count obj          ! Даже если 0, то нужно писать 0
 obj x y
 ...
 obj x y
 int countBases
 Gamer
 xBase yBase
 baseHealth
 numUnits
 unitName x y attack defense health

 */

void Memento::loadGameFromDoc() {
    gameState = new GameState;

    if (!(stateDoc >> (gameState->size).first >> (gameState->size).second)){
        correct = false;
        return;
    }
    if ((gameState->size).first < 1 || (gameState->size).second < 1){
        correct = false;
        return;
    }


    int count = (gameState->size).first * (gameState->size).second;
    while (count){

        int landName;
        auto *landCoordinates = new Coordinates;
        stateDoc >> landName;
        if (landName < 0 || landName > MAXLANDNAME){
            correct = false;
            return;
        }
        stateDoc >> landCoordinates->x >> landCoordinates->y;
        if (landCoordinates->x < 0 || landCoordinates->x >= gameState->size.first){
            correct = false;
            return;
        }
        if (landCoordinates->y < 0 || landCoordinates->y >= gameState->size.second){
            correct = false;
            return;
        }

        gameState->lands.emplace_back(landName, landCoordinates);
        count--;
    } // land

    stateDoc >> count;
    while (count){
        int objName;
        auto *objCoordinates = new Coordinates;
        if (!(stateDoc >> objName)){
            correct = false;
            return;
        }
        if (objName < 0 || objName > MAXOBJNAME){
            correct = false;
            return;
        }
        if (!(stateDoc >> objCoordinates->x >> objCoordinates->y)){
            correct = false;
            return;
        }
        if (objCoordinates->x < 0 || objCoordinates->x >= gameState->size.first){
            correct = false;
            return;
        }
        if (objCoordinates->y < 0 || objCoordinates->y >= gameState->size.second){
            correct = false;
            return;
        }
        gameState->objects.emplace_back(objName, objCoordinates);
        count--;
    } // obj

    int countBases;
    stateDoc >> countBases;
    if (countBases < 1){
        correct = false;
        return;
    }

    while (countBases){
        std::string name;
        if (!(stateDoc >> name)){
            correct = false;
            return;
        }
        auto *currentBase = new BaseState;
        auto *baseCoordinates = new Coordinates;
        if (!(stateDoc >> baseCoordinates->x >> baseCoordinates->y)){
            correct = false;
            return;
        }
        if (baseCoordinates->x < 0 || baseCoordinates->x >= gameState->size.first){
            correct = false;
            return;
        }
        if (baseCoordinates->y < 0 || baseCoordinates->y >= gameState->size.second){
            correct = false;
            return;
        }

        currentBase->coordinates = baseCoordinates;
        if (!(stateDoc >> currentBase->health)){
            correct = false;
            return;
        }
        if (currentBase->health < 0){
            correct = false;
            break;
        }
        if (!(stateDoc >> currentBase->numUnits)){
            correct = false;
            return;
        }
        if (currentBase->numUnits < 0){
            correct = false;
            return;
        }

        int countUnit = currentBase->numUnits;

        while (countUnit){

            auto* currentUnit = new UnitState;
            if (!(stateDoc >> currentUnit->UnitName)){
                correct = false;
                return;
            }
            if (currentUnit->UnitName > MAXUNITNAME){
                correct = false;
                return;
            }

            auto unitCoordinate = new Coordinates;
            if (!(stateDoc >> unitCoordinate->x >> unitCoordinate->y)){
                correct = false;
                return;
            }
            if (unitCoordinate->x < 0 || unitCoordinate->x >= gameState->size.first){
                correct = false;
                return;
            }
            if (unitCoordinate->y < 0 || unitCoordinate->x >= gameState->size.second){
                correct = false;
                return;
            }

            currentUnit->coordinates = unitCoordinate;
            if (!(stateDoc >> currentUnit->attack >> currentUnit->defense >> currentUnit->health)){
                correct = false;
                return;
            }
            currentBase->units.push_back(currentUnit);
            countUnit--;
        }
        gameState->bases[name] = currentBase;
        countBases--;
    }

    correct = true;
}

void Memento::saveGame(GameField *gameField, std::map <Gamer*, Base*> fieldBases) {

    bool statePath = true;
    if (path == "-")
        statePath = false;

    gameState = new GameState;
    gameState->size = std::make_pair(gameField->getWidth(), gameField->getHeight());
    if (statePath){
        stateDoc << gameState->size.first << " " << gameState->size.second << std::endl;
    }

    for (int i = 0; i < gameField->getHeight(); i++){
        for (int j = 0; j < gameField->getWidth(); j++){

            auto *coordinates = new Coordinates;
            coordinates->x = j;
            coordinates->y = i;
            int name;
            switch (gameField->getCell(j, i)->getLandscape()->getLandName()){
                case GRASS:
                    name = 0;
                    break;
                case MOUNTAINS:
                    name = 1;
                    break;
                case FOREST:
                    name = 2;
                    break;
                case SWAMP:
                    name = 3;
                    break;
            }
            gameState->lands.emplace_back(name, coordinates);
            if (statePath)
                stateDoc << name << " " << coordinates->x << " " << coordinates->y << std::endl;

        }
    } // lands

    for (int i = 0; i < gameField->getHeight(); i++){
        for (int j = 0; j < gameField->getWidth(); j++){

            if (!(gameField->getCell(j, i)->isObject()))
                continue;

            auto *coordinates = new Coordinates;
            coordinates->x = j;
            coordinates->y = i;
            int name;

            // {BAR, HOSPITAL, SHOP, TRAIN}
            switch (gameField->getCell(j, i)->getObject()->getObjName()){
                case BAR:
                    name = 0;
                    break;
                case HOSPITAL:
                    name = 1;
                    break;
                case SHOP:
                    name = 2;
                    break;
                case TRAIN:
                    name = 3;
                    break;
            }
            gameState->objects.emplace_back(name, coordinates);
        }
    } // objects

    if (statePath){
        int countObj = gameState->objects.size();
        stateDoc << countObj << std::endl;
        for (auto & obj : gameState->objects){
            stateDoc << obj.first << " " << obj.second->x << " " << obj.second->y << std::endl;
        }
    }


    int countBases = fieldBases.size();
    if (statePath)
        stateDoc << countBases << std::endl;

    for (auto & base : fieldBases){

        auto currentBase = new BaseState;
        currentBase->coordinates = base.second->getCoordinates();
        currentBase->health = base.second->getHealth()->getValue();

        if (statePath){
            stateDoc << base.first->getGamerName() << std::endl;
            stateDoc << currentBase->coordinates->x << " " << currentBase->coordinates->y << std::endl;
            stateDoc << currentBase->health << std::endl;
            stateDoc << base.second->getUnits().size() << std::endl;
        }

        for (auto & unit : base.second->getUnits()){
            auto *currentUnit = new UnitState;
            currentUnit->coordinates = unit->getCoordinates();
            //{INFANTRY, GUARDSMEN, FIGHTER, SCOUT, CANNON, TANK}
            switch (unit->getUnitName()){
                case INFANTRY:
                    currentUnit->UnitName = 0;
                    break;
                case GUARDSMEN:
                    currentUnit->UnitName = 1;
                    break;
                case FIGHTER:
                    currentUnit->UnitName = 2;
                    break;
                case SCOUT:
                    currentUnit->UnitName = 3;
                    break;
                case CANNON:
                    currentUnit->UnitName = 4;
                    break;
                case TANK:
                    currentUnit->UnitName = 5;
                    break;
            }
            currentUnit->health = unit->getHealthValue();
            currentUnit->attack = unit->getAttackValue();
            currentUnit->defense = unit->getDefenseValue();
            currentBase->units.push_back(currentUnit);
            if (statePath){
                stateDoc << currentUnit->UnitName << " " << currentUnit->coordinates->x << " " << currentUnit->coordinates->y;
                stateDoc << " " << currentUnit->attack << " " << currentUnit->defense << " " << currentUnit->health << std::endl;
            }

        } // units

        currentBase->numUnits = currentBase->units.size();
        gameState->bases[base.first->getGamerName()] = currentBase;

    }
}
