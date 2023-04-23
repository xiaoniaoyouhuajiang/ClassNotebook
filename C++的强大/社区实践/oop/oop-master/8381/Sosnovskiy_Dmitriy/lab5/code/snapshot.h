#pragma once

#include <vector>
#include <QString>
#include <QFile>
#include "QTextStream"
#include "enums.h"

class CoordsInfo{
public:
    unsigned int row;
    unsigned int column;
    CoordsInfo(unsigned int row, unsigned int column) :
        row(row), column(column) { }
};

class BaseSnapshot{
public:
    unsigned int healthAmount;
    CoordsInfo* coordinates;
    unsigned int possessorId;
    BaseSnapshot(unsigned int healthAmount, unsigned int possessorId, CoordsInfo* cords):
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

class NeutralObjectInfo{
public:
    NeutralObjectType type;
    CoordsInfo* coordinate;
    NeutralObjectInfo(NeutralObjectType type, CoordsInfo* coordinate){
        this->type = type;
        this->coordinate = coordinate;
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
    unsigned int playersAmount;
    FieldSnapshot* fieldSnapshot;
    std::vector<BaseSnapshot*> bases;

    std::vector<unsigned int> playersAlive;

    unsigned int currentPlayer;

    GameSnapshot(unsigned int playersAmount, FieldSnapshot* fieldSnapshot, std::vector<BaseSnapshot*> bases, unsigned int currentPlayer,
                 std::vector<unsigned int> playersAlive)
    {
        this->playersAmount = playersAmount;
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

        stream << "PLAYERS_AMOUNT" << "\n";

        stream << gameState->playersAmount << "\n";

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

        if(line != "PLAYERS_AMOUNT") throw std::invalid_argument("Error");

        stream >> line;

        bool* flag = new bool();
        unsigned int playersAmount = line.toUInt(flag);
        if(*flag == false) throw std::invalid_argument("Error");


        stream >> line;
        if(line != "CURRENT_PLAYER") throw std::invalid_argument("Error");


        stream >> line;
        unsigned int currentPlayer = line.toUInt(flag);
        if(*flag == false) throw std::invalid_argument("Error");




        stream >> line;
        if(line != "PLAYERS_ALIVE") throw std::invalid_argument("Error");

        std::vector<unsigned int> playersAlive;

        stream >> line;
        unsigned int  playersAliveAmount = line.toUInt(flag);
        if(*flag == false) throw std::invalid_argument("Error");


        for(unsigned int i = 0; i < playersAliveAmount; i++)
        {
            stream >> line;
            unsigned int playerNumber = line.toUInt(flag);
            if(*flag == false) throw std::invalid_argument("Error");


            playersAlive.push_back(playerNumber);

        }


        stream >> line;
        if(line != "FIELD") throw std::invalid_argument("Error");


        stream >> line;
        unsigned int rowsAmount = line.toUInt(flag);
        if(*flag == false) throw std::invalid_argument("Error");


        stream >> line;
        unsigned int columnsAmount = line.toUInt(flag);
        if(*flag == false) throw std::invalid_argument("Error");


        stream >> line;
        unsigned int maximumEntitiesAmount = line.toUInt(flag);
        if(*flag == false) throw std::invalid_argument("Error");


        stream >> line;
        unsigned int currentEntitiesAmount = line.toUInt(flag);
        if(*flag == false) throw std::invalid_argument("Error");


        stream >> line;
        if(line != "LANDSCAPES") throw std::invalid_argument("Error");



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
            } else { throw std::invalid_argument("Error");
 }
        }

        stream >> line;
        if(line != "NEUTRAL_OBJECTS") throw std::invalid_argument("Error");


        std::vector<NeutralObjectInfo*> neutralObjectsInfo;

        stream >> line;
        unsigned int neutralObjectsAmount = line.toUInt(flag);
        if(*flag == false) throw std::invalid_argument("Error");


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
            } else throw std::invalid_argument("Error");


            stream >> line;
            unsigned int row = line.toUInt(flag);
            if(*flag == false) throw std::invalid_argument("Error");


            stream >> line;
            unsigned int column = line.toUInt(flag);
            if(*flag == false) throw std::invalid_argument("Error");


            neutralObjectsInfo.push_back(new NeutralObjectInfo(objType, new CoordsInfo(row, column)));
        }

        stream >> line;
        if(line != "BASES") throw std::invalid_argument("Error");


        stream >> line;
        unsigned int basesSize = line.toUInt(flag);
        if(*flag == false) throw std::invalid_argument("Error");



        std::vector<BaseSnapshot*> bases;

        for(unsigned i = 0; i < basesSize; i++)
        {
            stream >> line;
            unsigned int possessorId = line.toUInt(flag);
            if(*flag == false) throw std::invalid_argument("Error");


            stream >> line;
            unsigned int row = line.toUInt(flag);
            if(*flag == false) throw std::invalid_argument("Error");


            stream >> line;
            unsigned int column = line.toUInt(flag);
            if(*flag == false) throw std::invalid_argument("Error");


            stream >> line;
            unsigned int health = line.toUInt(flag);
            if(*flag == false) throw std::invalid_argument("Error");


            BaseSnapshot* snapshot = new BaseSnapshot(health, possessorId, new CoordsInfo(row, column));
            bases.push_back(snapshot);
        }

        stream >> line;
        if(line != "UNITS") throw std::invalid_argument("Error");


        stream >> line;
        unsigned int unitsAmount = line.toUInt(flag);
        if(*flag == false) throw std::invalid_argument("Error");


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
            } else throw std::invalid_argument("Error");



            stream >> line;
            unsigned int row = line.toUInt(flag);
            if(*flag == false) throw std::invalid_argument("Error");


            stream >> line;
            unsigned int column = line.toUInt(flag);
            if(*flag == false) throw std::invalid_argument("Error");


            stream >> line;
            unsigned int possessorId = line.toUInt(flag);
            if(*flag == false) throw std::invalid_argument("Error");


            stream >> line;
            unsigned int health = line.toUInt(flag);
            if(*flag == false) throw std::invalid_argument("Error");


            UnitSnapshot* snapshot = new UnitSnapshot(unitType, health, possessorId, new CoordsInfo(row, column));

            units.push_back(snapshot);
        }



        return new GameSnapshot(playersAmount,
                                new FieldSnapshot(rowsAmount, columnsAmount, maximumEntitiesAmount, currentEntitiesAmount,
                                                  units, landscapes, neutralObjectsInfo),
                                bases, currentPlayer, playersAlive);
    }


};
