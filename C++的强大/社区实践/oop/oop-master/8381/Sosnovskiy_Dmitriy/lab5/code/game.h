#pragma once
#include <map>

#include "field.h"
#include "base.h"
#include "snapshot.h"

class Game{

private:
    Field* field;
    std::map<unsigned int, Base*> bases;

    std::vector<unsigned int> playersAlive;

    unsigned int totalPlayersAmount;

    unsigned int currentPlayer;

    void switchCurrentPlayer()
    {
        for(int i = 0; i < playersAlive.size(); i++)
        {
            if(isPlayerAlive(playersAlive[i]) == false)
            {
                playersAlive.erase(playersAlive.begin() + i);
                i--;
            }
        }

        do{
            currentPlayer = (currentPlayer + 1) % totalPlayersAmount;
        } while (isPlayerAlive(currentPlayer) == false);

    }

public:
    Game(unsigned int fieldRowSize, unsigned int fieldColumnSize, unsigned int maximumEntities, unsigned int playersAmount)
    {
        this->totalPlayersAmount = playersAmount;

        for(unsigned int i = 0; i < playersAmount; i++){
            playersAlive.push_back(i);
        }

        currentPlayer = 0;

        field = new Field(fieldRowSize, fieldColumnSize, maximumEntities);
    }

    unsigned int getCurrentPlayer() { return currentPlayer; }

    unsigned int getTotalPlayersAmonut() { return totalPlayersAmount; }

    Game(GameSnapshot* snapshot)
    {
        field = new Field(snapshot->fieldSnapshot);

        for(unsigned int i = 0; i < snapshot->playersAmount; i++)
        {
            addBase(snapshot->bases[i]->coordinates->row,
                    snapshot->bases[i]->coordinates->column,
                    snapshot->bases[i]->possessorId);
        }

        this->totalPlayersAmount = snapshot->playersAmount;
        this->currentPlayer = snapshot->currentPlayer;

        for(unsigned i = 0; i < snapshot->fieldSnapshot->units.size(); i++)
        {
            addUnit(snapshot->fieldSnapshot->units[i]->coordinates->row,
                    snapshot->fieldSnapshot->units[i]->coordinates->column,
                    snapshot->fieldSnapshot->units[i]->type,
                    snapshot->fieldSnapshot->units[i]->possessorId);

            field->getCell(snapshot->fieldSnapshot->units[i]->coordinates->row,
                           snapshot->fieldSnapshot->units[i]->coordinates->column)
                    ->getCreature()->setHealth(snapshot->fieldSnapshot->units[i]->healthAmount);
        }
    }

    unsigned int getRowsAmount() { return field->getRowsAmount(); }
    unsigned int getColumnsAmount() { return field->getColumnsAmount(); }

    // exception here?
    void addBase(unsigned int row, unsigned int column, unsigned int possessorId){

        if(bases.count(possessorId) == 1) throw std::invalid_argument("already has that possessor");

        Base* base = new Base(field, row, column, possessorId);
        bases[possessorId] = base;
    }

    void addUnit(unsigned int row, unsigned int column, UnitType unitType, unsigned int possessorId){
        if(bases.count(possessorId) == 0) throw std::invalid_argument("no such possessor");
        try {
            bases[possessorId]->createUnit(unitType, row, column);
            switchCurrentPlayer();
        } catch (...) {

        }{}
    }

    void moveUnit(unsigned int rowFrom, unsigned int columnFrom,
                  unsigned int rowTo, unsigned int columnTo, unsigned int actorId)
    {
        field->moveUnit(rowFrom, columnFrom, rowTo, columnTo, actorId);
        switchCurrentPlayer();
    }

    void attack(unsigned int rowFrow, unsigned int columnFrom,
                unsigned int rowTo, unsigned int columnTo, unsigned int actorId)
    {
        field->commitFight(rowFrow, columnFrom, rowTo, columnTo, actorId);
        switchCurrentPlayer();
    }

   QString getBaseInfo(unsigned int possessorId)
   {
       return bases[possessorId]->getInfo();
   }

    CreatureType getCreatureType(unsigned int row, unsigned int column){
        if(field->getCell(row, column)->hasCreature())
            return field->getCell(row, column)->getCreature()->getCreatureType();
        else {
            throw std::invalid_argument("no_creature");
        }
    }

    UnitType getUnitType(unsigned int row, unsigned int column)
    {
        if(field->getCell(row, column)->hasCreature() &&
                field->getCell(row, column)->getCreature()->getCreatureType() == UNIT){
                return dynamic_cast<IUnit*>(field->getCell(row, column)->getCreature())->getType();
        }
        else throw std::invalid_argument("no_unit");
    }

    NeutralObjectType getNeutralObjectType(unsigned int row, unsigned int column)
    {
        if(field->getCell(row, column)->hasNeutralObject())
            return field->getCell(row, column)->getNeutralObject()->getType();
        else throw std::invalid_argument("no object");
    }

    LandscapeType getLandscapeType(unsigned int row, unsigned int column){
        return field->getCell(row, column)->getLandscape()->getType();
    }

    bool isPlayerAlive(unsigned int playerNumber)
    {
        return bases[playerNumber]->isDemolished()? false: true;
    }

    GameSnapshot* createSnapshot(){
        FieldSnapshot* fieldSnapshot = field->createSnapshot();

        std::vector<BaseSnapshot*> basesSnapshots;

        for(unsigned int i = 0; i < bases.size(); i++)
        {
            basesSnapshots.push_back(bases[i]->createSnapshot());
        }

        GameSnapshot* gameSnapshot = new GameSnapshot(basesSnapshots.size(), fieldSnapshot, basesSnapshots, currentPlayer, playersAlive);

        return gameSnapshot;
    }
};
