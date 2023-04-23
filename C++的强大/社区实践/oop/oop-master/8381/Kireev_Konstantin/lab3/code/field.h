#pragma once
#include "unitsinterface.h"
#include "cellInterface.h"
#include "fightmediator.h"
#include <stdexcept>

class Field
{
private:

    cellInterface*** fieldModel;
    friend class FieldIteator;
    unsigned int rowsAmount;
    unsigned int columnsAmount;
    unsigned int maximumEntitiesAmount;
    unsigned int currentEntitiesAmount;

public:
    Field(unsigned int rowsAmount, unsigned int columnsAmount, unsigned int maximumEntitiesAmount);
    Field(const Field& field);
    Field(Field&& field);
    ~Field();

    unsigned int getRowsAmount() const;
    unsigned int getColumnsAmount() const;
    unsigned int getMaximumEntitiesAmount() const;

    void setMaximumEntitiesAmount(unsigned int newMaximumEntitiesAmount);

    void placeCreature(unsigned int row, unsigned int columnn, CreatureInterface* creature);

    void moveUnit(unsigned int rowNumberFrom, unsigned int columnNumberFrom,
                  unsigned int rowNumberTo, unsigned int columnNumberTo,
                  unsigned int actorId);

    cellInterface* getCell(unsigned int rowNumber, unsigned int columnNumber);

    void commitFight(unsigned int rowFrom, unsigned int columnFrom,
                     unsigned int rowTo, unsigned int columnTo,
                     unsigned int actorId);

    QString getAsString();

    void onUnitDestroyed()
    {
        currentEntitiesAmount--;
    }

    void generateLandscapes()
    {
        for(unsigned int i = 0; i < rowsAmount; i++)
        {
            for(unsigned int j = 0; j < columnsAmount; j++ )
            {
                int temp = rand() % 3;
                if(temp == 0)
                    fieldModel[i][j]->setLandscape(new Ground());
                else if(temp == 1)
                    fieldModel[i][j]->setLandscape(new Water());
                else if(temp == 2)
                    fieldModel[i][j]->setLandscape(new Mountains());
            }
        }

        for(unsigned int i = 0; i < rowsAmount; i++)
        {
            for(unsigned int j = 0; j < columnsAmount; j++)
            {
                int chance = rand() % 3;
                if(chance != 1) continue;
                int temp = rand() % 4;
                if(fieldModel[i][j]->canHoldCreature() == false) continue;
                if(temp == 0)
                    fieldModel[i][j]->setNeutralObject(new Village());
                else if(temp == 1)
                    fieldModel[i][j]->setNeutralObject(new GunSmith());
                else if(temp == 2)
                    fieldModel[i][j]->setNeutralObject(new ArmorHouse());
                else if(temp == 3)
                    fieldModel[i][j]->setNeutralObject(new BoostTower());

            }
        }
    }

};

class FieldIteator{
private:
    Field* field;

    unsigned int currentRow;
    unsigned int currentColumn;
public:
    FieldIteator(Field* fieldAttachedTo)
    {
        this->field = fieldAttachedTo;
        currentRow = 0;
        currentColumn = 0;
    }

    void reset() {
        currentRow = 0;
        currentColumn = 0;
    }

    bool hasNext() {
        if(currentRow < field->rowsAmount && currentColumn < field->columnsAmount)
            return true;
        else return false;
    }

    cellInterface* getNext()
    {
        cellInterface* cell = field->fieldModel[currentRow][currentColumn];
        currentRow++;
        if(currentRow == field->rowsAmount)
        {
            currentRow = 0;
            currentColumn++;
        }
        return cell;
    }
};
