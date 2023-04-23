#pragma once
#include <map>
#include "field.h"
#include "base.h"

class Game
{

private:
    Field* field;
    std::map<unsigned int, Base*> bases;

public:
    Game(unsigned int fieldRowSize, unsigned int fieldColumnSize, unsigned int maximumEntities,
         unsigned int playersAmount)
    {
        field = new Field(fieldRowSize, fieldColumnSize, maximumEntities);
    }

    unsigned int getRowsAmount()
    {
        return field->getRowsAmount();
    }
    unsigned int getColumnsAmount()
    {
        return field->getColumnsAmount();
    }


    void addBase(unsigned int row, unsigned int column, unsigned int possessorId)
    {
        Base* base = new Base(field, row, column, possessorId);
        bases[possessorId] = base;
    }

    void addUnit(unsigned int row, unsigned int column, UnitType unitType, unsigned int possessorId)
    {
        bases[possessorId]->createUnit(unitType, row, column);
    }

    void moveUnit(unsigned int rowFrom, unsigned int columnFrom,
                  unsigned int rowTo, unsigned int columnTo, unsigned int actorId)
    {
        field->moveUnit(rowFrom, columnFrom, rowTo, columnTo, actorId);
    }

    void attack(unsigned int rowFrow, unsigned int columnFrom,
                unsigned int rowTo, unsigned int columnTo, unsigned int actorId)
    {
        field->commitFight(rowFrow, columnFrom, rowTo, columnTo, actorId);
    }

   QString getBaseInfo(unsigned int possessorId)
   {
       return bases[possessorId]->getInfo();
   }

    CreatureType getCreatureType(unsigned int row, unsigned int column)
    {
        if(field->getCell(row, column)->hasCreature())
            return field->getCell(row, column)->getCreature()->getCreatureType();
        else
            throw std::invalid_argument("no creature");
    }

    UnitType getUnitType(unsigned int row, unsigned int column)
    {
        if(field->getCell(row, column)->hasCreature() &&
                field->getCell(row, column)->getCreature()->getCreatureType() == UNIT)
        {
            return dynamic_cast<UnitInterface*>(field->getCell(row, column)->getCreature())->getType();
        }
        else
            throw std::invalid_argument("no unit");
    }

    NeutralObjectType getNeutralObjectType(unsigned int row, unsigned int column)
    {
        if(field->getCell(row, column)->hasNeutralObject())
            return field->getCell(row, column)->getNeutralObject()->getType();
        else
            throw std::invalid_argument("no object");
    }

    LandscapeType getLandscapeType(unsigned int row, unsigned int column)
    {
        return field->getCell(row, column)->getLandscape()->getType();
    }

    bool isPlayerAlive(unsigned int playerNumber)
    {
        return bases[playerNumber]->isDemolished()? false: true;
    }
};
