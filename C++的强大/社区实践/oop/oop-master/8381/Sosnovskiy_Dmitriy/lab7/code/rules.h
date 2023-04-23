#pragma once

#include <vector>
#include <map>

#include "enums.h"
#include "custom_classes.h"

class IRule{
protected:
    unsigned int playersAmount;
    unsigned int maximumEntitiesAmount;
    unsigned int fieldRowsAmount;
    unsigned int fieldColumnsAmount;
    std::vector<LandscapeType> landscapes;
    std::vector<NeutralObjectInfo*> neutralObjects;
    std::map<unsigned int, CoordsInfo*> bases;
    unsigned int playersAmountLeftToWin = 1;
public:
    virtual ~IRule() = default;
    unsigned int getPlayersAmount() { return playersAmount; }
    unsigned int getMaximumEntitiesAmount() { return maximumEntitiesAmount; }
    unsigned int getFieldRowsAmount() { return fieldRowsAmount; }
    unsigned int getFieldColumnsAmount() { return  fieldColumnsAmount; }
    unsigned int getWinState() { return  playersAmountLeftToWin; }

    std::vector<LandscapeType> getLandscapes() { return landscapes; }
    std::vector<NeutralObjectInfo*> getNeutralObjects() { return neutralObjects; }
    std::map<unsigned int, CoordsInfo*> getBases() { return bases; }
    virtual RuleType getRuleType() = 0;
    virtual PlayersOrder getPlayersOrder() = 0;
};


class FirstRule : public IRule{
public:
    FirstRule() {
        this->playersAmount = 2;
        this->maximumEntitiesAmount = 10;
        this->fieldRowsAmount = 5;
        this->fieldColumnsAmount = 5;
        this->landscapes = std::vector<LandscapeType>{
                    GROUND, GROUND, GROUND, MOUNTAINS, GROUND,
                    GROUND, GROUND, WATER, GROUND, MOUNTAINS,
                    GROUND, WATER, WATER, WATER, GROUND,
                    MOUNTAINS, GROUND, WATER, GROUND, GROUND,
                    GROUND, MOUNTAINS, GROUND, GROUND, GROUND };
        this->neutralObjects = std::vector<NeutralObjectInfo*> {
                new NeutralObjectInfo(BANNER, new CoordsInfo(1, 1)),
                new NeutralObjectInfo(TEMPLE, new CoordsInfo(3, 1)),
                new NeutralObjectInfo(FORGE, new CoordsInfo(1, 3)),
                new NeutralObjectInfo(TOWER, new CoordsInfo(3, 3)) };
        this->bases = std::map<unsigned int, CoordsInfo*>{ {0, new CoordsInfo(0,2)} , {1, new CoordsInfo(4, 2)}};
    }

    RuleType getRuleType() override { return FIRST; }
    PlayersOrder getPlayersOrder() override { return USUAL; }
};


class SecondRule : public IRule{
public:
    SecondRule() {
        this->playersAmount = 4;
        this->maximumEntitiesAmount = 16;
        this->fieldRowsAmount = 6;
        this->fieldColumnsAmount = 6;
        this->landscapes = std::vector<LandscapeType>{
                    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND,
                    GROUND, GROUND, MOUNTAINS, MOUNTAINS, GROUND, GROUND,
                    GROUND, MOUNTAINS, WATER, WATER, MOUNTAINS, GROUND,
                    GROUND, MOUNTAINS, WATER, WATER, MOUNTAINS, GROUND,
                    GROUND, GROUND, MOUNTAINS, MOUNTAINS, GROUND, GROUND,
                    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND };
        this->neutralObjects = std::vector<NeutralObjectInfo*> {
                new NeutralObjectInfo(BANNER, new CoordsInfo(1, 1)),
                new NeutralObjectInfo(TEMPLE, new CoordsInfo(4, 1)),
                new NeutralObjectInfo(FORGE, new CoordsInfo(1, 4)),
                new NeutralObjectInfo(TOWER, new CoordsInfo(4, 4)) };
        this->bases = std::map<unsigned int, CoordsInfo*>{ {0, new CoordsInfo(0, 0)},
                                                           {1, new CoordsInfo(0, 5)},
                                                           {2, new CoordsInfo(5, 0)},
                                                           {3, new CoordsInfo(5, 5)}};
    }

    RuleType getRuleType() override { return SECOND; }
    PlayersOrder getPlayersOrder() override { return REVERSIVE; }
};
