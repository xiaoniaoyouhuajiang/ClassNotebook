#pragma once

#include <vector>
#include <QString>
#include <QFile>
#include "QTextStream"
#include "enums.h"
#include "custom_classes.h"
#include "exception.h"

class BaseSnapshot{
public:
    int healthAmount;
    CoordsInfo* coordinates;
    unsigned int possessorId;
    BaseSnapshot(int healthAmount, unsigned int possessorId, CoordsInfo* cords):
        healthAmount(healthAmount), possessorId(possessorId) {
        this->coordinates = cords;
    }
};


class UnitSnapshot {
public:
    UnitType type;
    unsigned int healthAmount;
    unsigned int possessorId;
    CoordsInfo* coordinates;
    UnitSnapshot(UnitType type, unsigned int healthAmount, unsigned int possessorId, CoordsInfo* coordinates):
        healthAmount(healthAmount), possessorId(possessorId){
        this->type = type;;
        this->coordinates = coordinates;
    }
};

class FieldSnapshot{
public:
    unsigned int rowsAmount;
    unsigned int columnsAmount;
    unsigned int maximumEntitiesAmount;
    unsigned int currentEntitiesAmount;

    std::vector<UnitSnapshot*> units;
    std::vector<LandscapeType> landscapes;
    std::vector<NeutralObjectInfo*> neutralObjects;

    FieldSnapshot(unsigned int rowsAmount, unsigned int columnsAmount, unsigned int maximumEntitiesAmount, unsigned int currentEntitiesAmount,
                  std::vector<UnitSnapshot*> unitSnapshots,
                  std::vector<LandscapeType> landscapes,
                  std::vector<NeutralObjectInfo*> neutralObjectsInfo) :
        rowsAmount(rowsAmount), columnsAmount(columnsAmount), maximumEntitiesAmount(maximumEntitiesAmount), currentEntitiesAmount(currentEntitiesAmount)
    {
        this->units = unitSnapshots;
        this->landscapes = landscapes;
        this->neutralObjects = neutralObjectsInfo;
    }
};

class GameSnapshot{
public:
    RuleType ruleType;
    FieldSnapshot* fieldSnapshot;
    std::vector<BaseSnapshot*> bases;

    std::vector<unsigned int> playersAlive;

    unsigned int currentPlayer;

    GameSnapshot(RuleType ruleType, FieldSnapshot* fieldSnapshot, std::vector<BaseSnapshot*> bases, unsigned int currentPlayer,
                 std::vector<unsigned int> playersAlive)
    {
        this->ruleType = ruleType;
        this->fieldSnapshot = fieldSnapshot;
        this->bases = bases;
        this->currentPlayer = currentPlayer;
        this->playersAlive = playersAlive;
    }
};



class GameSnapshotCaretaker
{
public:
    GameSnapshotCaretaker() { }

    void saveGameState(QString saveFileName, GameSnapshot* gameState){
        QFile file(saveFileName);

        file.open(QIODevice::Append | QIODevice::Truncate);

        QTextStream stream(&file);

        stream << "RULE_TYPE" << "\n";

        if(gameState->ruleType == FIRST)
            stream << 1 << "\n";
        else if (gameState->ruleType == SECOND){
            stream << 2 << "\n";
        }

        stream << "CURRENT_PLAYER" << "\n";

        stream << gameState->currentPlayer << "\n";

        stream << "PLAYERS_ALIVE" << "\n";

        stream << gameState->playersAlive.size() << "\n";

        for(unsigned int i = 0; i < gameState->playersAlive.size(); i++)
        {
            stream << gameState->playersAlive[i] << " ";
        }

        if(gameState->playersAlive.size() != 0) stream << "\n";

        stream << "FIELD" << "\n";
        stream << gameState->fieldSnapshot->rowsAmount << " " << gameState->fieldSnapshot->columnsAmount << " "
               << gameState->fieldSnapshot->maximumEntitiesAmount << " " << gameState->fieldSnapshot->currentEntitiesAmount << "\n";

        stream << "LANDSCAPES" << "\n";
        for(unsigned int i = 0; i < gameState->fieldSnapshot->landscapes.size(); i++)
        {
            switch (gameState->fieldSnapshot->landscapes[i]) {
                case MOUNTAINS:
                    stream << "Mountains\n";
                    break;
                case WATER:
                    stream << "Water\n";
                    break;
                case GROUND:
                    stream << "Ground\n";
                    break;
            }
        }

        stream << "NEUTRAL_OBJECTS" << "\n";

        stream << gameState->fieldSnapshot->neutralObjects.size() << "\n";

        for(unsigned int i = 0; i < gameState->fieldSnapshot->neutralObjects.size(); i++)
        {
            QString objectClass;

            if(gameState->fieldSnapshot->neutralObjects[i]->type == BANNER) {
                objectClass = "Banner";
            } else if (gameState->fieldSnapshot->neutralObjects[i]->type == TOWER){
                objectClass = "Tower";
            } else if (gameState->fieldSnapshot->neutralObjects[i]->type == TEMPLE){
                objectClass = "Temple";
            } else if (gameState->fieldSnapshot->neutralObjects[i]->type == FORGE){
                objectClass = "Forge";
            }

            stream << objectClass << "\n";
            stream << gameState->fieldSnapshot->neutralObjects[i]->coordinate->row << " "
                   <<  gameState->fieldSnapshot->neutralObjects[i]->coordinate->column << "\n";
        }

        stream << "BASES" << "\n";
        stream << gameState->bases.size() << "\n";
        for(unsigned int i = 0; i < gameState->bases.size(); i++)
        {
            stream << gameState->bases[i]->possessorId << " "
                   << gameState->bases[i]->coordinates->row << " " << gameState->bases[i]->coordinates->column << " "
                   << gameState->bases[i]->healthAmount << "\n";
        }

        stream << "UNITS" << "\n";
        stream << gameState->fieldSnapshot->units.size() << "\n";

        for(unsigned int i = 0; i < gameState->fieldSnapshot->units.size(); i++)
        {
            QString unitClass;

            if(gameState->fieldSnapshot->units[i]->type == CRIT_ARCHER){
                unitClass = "CritArcher";
            } else if (gameState->fieldSnapshot->units[i]->type == ABSORB_ARCHER){
                unitClass = "AbsorbArcher";
            } else if (gameState->fieldSnapshot->units[i]->type == CRIT_INFANTRY) {
                unitClass = "CritInfantry";
            } else if (gameState->fieldSnapshot->units[i]->type == ABSORB_INFANTRY) {
                unitClass = "AbsorbInfantry";
            } else if (gameState->fieldSnapshot->units[i]->type == CRIT_CAVALRY) {
                unitClass = "CritCavalry";
            } else if (gameState->fieldSnapshot->units[i]->type == ABSORB_CAVALRY)
                unitClass = "AbsorbCavalry";

            stream << unitClass << "\n";
            stream << gameState->fieldSnapshot->units[i]->coordinates->row << " " << gameState->fieldSnapshot->units[i]->coordinates->column << " "
                   << gameState->fieldSnapshot->units[i]->possessorId << " "
                   << gameState->fieldSnapshot->units[i]->healthAmount << "\n";
        }

        file.close();
    }

    GameSnapshot* loadGameState(QString fileName)
    {
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);

        QTextStream stream(&file);
        QString line;
        stream >> line;

        if(line != "RULE_TYPE")
            throw new Exception(206, "Error in save file", "Error in line that should be named RULE_TYPE");

        stream >> line;

        bool* flag = new bool();
        unsigned int ruleTypeId = line.toUInt(flag);
        if(*flag == false) throw new Exception(214, "Error in save file", "Error in the rule type id in the save file.");

        RuleType ruleType;
        if(ruleTypeId == 1) ruleType = FIRST;
        else if(ruleTypeId == 2) ruleType = SECOND;
        else throw new Exception(206, "Error in save file", "Error in line that should be named RULE_TYPE");

        stream >> line;
        if(line != "CURRENT_PLAYER")
            new Exception(222, "Error in save file", "Error in line that should be named CURRENT_PLAYER");

        stream >> line;
        unsigned int currentPlayer = line.toUInt(flag);
        if(*flag == false) throw new Exception(226, "Error in save file", "Error in the current player value");


        stream >> line;
        if(line != "PLAYERS_ALIVE") new Exception(231, "Error in save file", "Error in line that should be named PLAYERS_ALIVE");

        std::vector<unsigned int> playersAlive;

        stream >> line;
        unsigned int  playersAliveAmount = line.toUInt(flag);
        if(*flag == false) new Exception(237, "Error in save file", "Error in the players alive amount");;


        for(unsigned int i = 0; i < playersAliveAmount; i++)
        {
            stream >> line;
            unsigned int playerNumber = line.toUInt(flag);
            if(*flag == false) new Exception(244, "Error in save file", "Error in the one of numbers of players alive");


            playersAlive.push_back(playerNumber);

        }


        stream >> line;
        if(line != "FIELD") new Exception(253, "Error in save file", "Error in line that should be named FIELD");


        stream >> line;
        unsigned int rowsAmount = line.toUInt(flag);
        if(*flag == false) new Exception(258, "Error in save file", "Error in the field rows value");


        stream >> line;
        unsigned int columnsAmount = line.toUInt(flag);
        if(*flag == false) new Exception(263, "Error in save file", "Error in the field columns value");


        stream >> line;
        unsigned int maximumEntitiesAmount = line.toUInt(flag);
        if(*flag == false) new Exception(268, "Error in save file", "Error in the field maximum entities value");


        stream >> line;
        unsigned int currentEntitiesAmount = line.toUInt(flag);
        if(*flag == false) new Exception(273, "Error in save file", "Error in the field current entities value");


        stream >> line;
        if(line != "LANDSCAPES") throw new Exception(277, "Error in save file", "Error in line that should be named LANDSCAPES");


        std::vector<LandscapeType> landscapes;

        for(unsigned int i = 0; i < rowsAmount*columnsAmount; i++)
        {
            stream >> line;
            if(line == "Mountains"){
                landscapes.push_back(MOUNTAINS);
            } else if (line == "Water"){
                landscapes.push_back(WATER);
            } else if (line == "Ground"){
                landscapes.push_back(GROUND);
            } else { throw new Exception(291, "Error in save file", "Error in the landscape name number " + QString::number(i+1)); }
        }

        stream >> line;
        if(line != "NEUTRAL_OBJECTS") throw new Exception(295, "Error in save file", "Error in line that should be named NEUTRAL_OBJECTS");


        std::vector<NeutralObjectInfo*> neutralObjectsInfo;

        stream >> line;
        unsigned int neutralObjectsAmount = line.toUInt(flag);
        if(*flag == false) throw new Exception(302, "Error in save file", "Error in the neutral objects amount value");

        for(unsigned i = 0; i < neutralObjectsAmount; i++)
        {
            NeutralObjectType objType;
            stream >> line;
            if(line == "Forge"){
                objType = FORGE;
            } else if (line == "Temple"){
                objType = TEMPLE;
            } else if (line == "Tower"){
                objType = TOWER;
            } else if (line == "Banner"){
                objType = BANNER;
            } else throw new Exception(316, "Error in save file", "Error in the neutral object name number: " + QString::number(i+1));


            stream >> line;
            int row = line.toInt(flag);
            if(*flag == false) throw new Exception(321, "Error in save file", "Error in the neutral object row number, neutral object number: " + QString::number(i+1));


            stream >> line;
            int column = line.toInt(flag);
            if(*flag == false) throw new Exception(321, "Error in save file", "Error in the neutral object column number, neutral object number: " + QString::number(i+1));
            if(row < 0 || row >= rowsAmount || column < 0 || column >= columnsAmount) throw new Exception(321, "Error in save file", "Error in the neutral object coords, out-of-range to field size. Object number: " + QString::number(i+1));
            neutralObjectsInfo.push_back(new NeutralObjectInfo(objType, new CoordsInfo(row, column)));
        }

        stream >> line;
        if(line != "BASES") throw new Exception(332, "Error in save file", "Error in line that should be named BASES");


        stream >> line;
        int basesSize = line.toInt(flag);
        if(*flag == false) throw new Exception(337, "Error in save file", "Error in the bases amount value.");
        if(basesSize < 0) throw new Exception(338, "Error in save file", "Error in the bases amount value");
        std::vector<BaseSnapshot*> bases;

        for(unsigned int i = 0; i < basesSize; i++)
        {
            stream >> line;
            int possessorId = line.toInt(flag);
            if(*flag == false) throw new Exception(345, "Error in save file", "Error in the possessor id value");


            stream >> line;
            int row = line.toInt(flag);
            if(*flag == false) throw new Exception(345, "Error in save file", "Error in the base row number value");


            stream >> line;
            int column = line.toInt(flag);
            if(*flag == false) throw new Exception(345, "Error in save file", "Error in the base column number value");


            stream >> line;
            int health = line.toInt(flag);
            if(*flag == false)  new Exception(345, "Error in save file", "Error in the base health value");
            if(possessorId < 0 || row < 0 || row >= rowsAmount || column < 0 || column >= columnsAmount)
                throw new Exception(361, "Error in save file", "Error in the base data, base number: " + QString::number(i+1));
            BaseSnapshot* snapshot = new BaseSnapshot(health, possessorId, new CoordsInfo(row, column));
            bases.push_back(snapshot);
        }

        stream >> line;
        if(line != "UNITS") throw new Exception(368, "Error in save file", "Error in line that should be named UNITS");


        stream >> line;
        int unitsAmount = line.toInt(flag);
        if(*flag == false) throw new Exception(373, "Error in save file", "Error in the units amount value");
        if(unitsAmount < 0)  throw new Exception(373, "Error in save file", "Error in the units amount value");

        std::vector<UnitSnapshot*> units;

        for(unsigned int i = 0; i < unitsAmount; i++)
        {
            UnitType unitType;
            stream >> line;

            if(line == "AbsorbCavalry") {
                unitType = ABSORB_CAVALRY;
            } else if (line == "CritCavalry") {
                unitType = CRIT_CAVALRY;
            } else if (line == "AbsorbArcher") {
                unitType = ABSORB_ARCHER;
            } else if (line == "CritArcher") {
                unitType = CRIT_ARCHER;
            } else if (line == "AbsorbInfantry"){
                unitType = ABSORB_INFANTRY;
            } else if (line == "CritInfantry") {
                unitType = CRIT_INFANTRY;
            } else throw new Exception(395, "Error in save file", "Error in the unit class name, unit number: " + QString::number(i));


            stream >> line;
            int row = line.toInt(flag);
            if(*flag == false) throw new Exception(400, "Error in save file", "Error in the units row number, unit number: " + QString::number(i));


            stream >> line;
            int column = line.toInt(flag);
            if(*flag == false) throw  new Exception(405, "Error in save file", "Error in the units column number, unit number: " + QString::number(i));


            stream >> line;
            int possessorId = line.toInt(flag);
            if(*flag == false) throw  new Exception(410, "Error in save file", "Error in the units possessor id number, unit number: " + QString::number(i));


            stream >> line;
            int health = line.toInt(flag);
            if(*flag == false) throw  new Exception(415, "Error in save file", "Error in the units health value, unit number: " + QString::number(i));
            if(row < 0 || row >= rowsAmount || column < 0 || column >= columnsAmount || possessorId < 0) throw new Exception(373, "Error in save file", "Error in the unit data, unit number: " + QString::number(i+1));

            UnitSnapshot* snapshot = new UnitSnapshot(unitType, health, possessorId, new CoordsInfo(row, column));

            units.push_back(snapshot);
        }

        return new GameSnapshot(ruleType,
                                new FieldSnapshot(rowsAmount, columnsAmount, maximumEntitiesAmount, currentEntitiesAmount,
                                                  units, landscapes, neutralObjectsInfo),
                                bases, currentPlayer, playersAlive);
    }


};
