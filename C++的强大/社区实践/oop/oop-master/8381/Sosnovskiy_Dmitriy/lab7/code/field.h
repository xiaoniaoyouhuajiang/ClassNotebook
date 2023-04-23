#pragma once
#include "units_interfaces.h"
#include "fieldcomponent.h"
#include "fightmediator.h"
#include "exception.h"

#include <snapshot.h>

class Field
{
private:

    FieldComponent*** fieldModel;

    friend class FieldIteator;

    unsigned int rowsAmount;
    unsigned int columnsAmount;
    unsigned int maximumEntitiesAmount;
    unsigned int currentEntitiesAmount;

public:
    Field(unsigned int rowsAmount, unsigned int columnsAmount, unsigned int maximumEntitiesAmount);
    Field(const Field& field);
    Field(Field&& field);

    Field(FieldSnapshot* snapshot)
    {
        this->rowsAmount = snapshot->rowsAmount;
        this->columnsAmount = snapshot->columnsAmount;
        this->maximumEntitiesAmount = snapshot->maximumEntitiesAmount;
        currentEntitiesAmount = 0;

        fieldModel = new FieldComponent**[rowsAmount];
        for(unsigned int i = 0; i < rowsAmount; i++)
        {
            fieldModel[i] = new FieldComponent*[columnsAmount];
            for(unsigned int j = 0; j < columnsAmount; j++)
            {
                fieldModel[i][j] = new FieldComponent();
            }
        }

        setLandscapes(snapshot->landscapes);


        for(unsigned int i = 0; i < snapshot->neutralObjects.size(); i++)
        {

            INeutralObject* neutralObj;

            switch (snapshot->neutralObjects[i]->type) {
                case BANNER:
                    neutralObj = new Banner();
                    break;
                case TOWER:
                    neutralObj = new Tower;
                    break;
                case TEMPLE:
                    neutralObj = new Temple();
                    break;
                case FORGE:
                    neutralObj = new Forge();
                    break;
            }

            if(fieldModel[snapshot->neutralObjects[i]->coordinate->row][snapshot->neutralObjects[i]->coordinate->column]->hasNeutralObject())
            {
                throw new Exception(69, "Irregular positioning", "Can't place neutral objects on the " + QString::number(snapshot->neutralObjects[i]->coordinate->row)
                                    +" " + QString::number(snapshot->neutralObjects[i]->coordinate->column) + " because there is neutral object alredy");
            }
            else fieldModel[snapshot->neutralObjects[i]->coordinate->row][snapshot->neutralObjects[i]->coordinate->column]->setNeutralObject(neutralObj);
        }
    }


    ~Field();

    void setLandscapes(std::vector<LandscapeType> landscapes){
        for(unsigned int i = 0; i < rowsAmount; i++)
        {
            for(unsigned int j = 0; j < columnsAmount; j++)
            {
                ILandscape* landscape;
                switch (landscapes[i * columnsAmount + j]) {
                    case MOUNTAINS:
                        landscape = new Mountains();
                        break;
                    case WATER:
                        landscape = new Water();
                        break;
                    case GROUND:
                        landscape = new Ground();
                        break;
                }
                fieldModel[i][j]->setLandscape(landscape);
            }
        }
    }

    void setNeutralObjects(std::vector<NeutralObjectInfo*> neutralObjects)
    {
        for(auto i : neutralObjects)
        {
            FieldComponent* cell = fieldModel[i->coordinate->row][i->coordinate->column];

            switch (i->type) {
                case BANNER:
                    cell->setNeutralObject(new Banner());
                    break;
                case TOWER:
                  cell->setNeutralObject(new Tower());
                    break;
                case TEMPLE:
                   cell->setNeutralObject(new Temple());
                    break;
                case FORGE:
                   cell->setNeutralObject(new Forge());
                    break;
            }
        }
    }

    unsigned int getRowsAmount() const;
    unsigned int getColumnsAmount() const;
    unsigned int getMaximumEntitiesAmount() const;

    void setMaximumEntitiesAmount(unsigned int newMaximumEntitiesAmount);

    void placeCreature(unsigned int row, unsigned int columnn, ICreature* creature);

    void moveUnit(unsigned int rowNumberFrom, unsigned int columnNumberFrom,
                  unsigned int rowNumberTo, unsigned int columnNumberTo,
                  unsigned int actorId);

    FieldComponent* getCell(unsigned int rowNumber, unsigned int columnNumber);

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
                    fieldModel[i][j]->setNeutralObject(new Temple());
                else if(temp == 1)
                    fieldModel[i][j]->setNeutralObject(new Forge());
                else if(temp == 2)
                    fieldModel[i][j]->setNeutralObject(new Banner());
                else if(temp == 3)
                    fieldModel[i][j]->setNeutralObject(new Tower());

            }
        }
    }



    FieldSnapshot* createSnapshot(){

        std::vector<UnitSnapshot*> unitSnapshots;
        std::vector<LandscapeType> landscapes;
        std::vector<NeutralObjectInfo*> neutralObjectsInfo;

        for(unsigned int i = 0; i < rowsAmount; i++)
        {
            for(unsigned int j = 0; j < columnsAmount; j++)
            {
                FieldComponent* cell = fieldModel[i][j];

                landscapes.push_back(cell->getLandscape()->getType());

                if(cell->hasCreature())
                {
                    ICreature* creature = cell->getCreature();
                    if(creature->getCreatureType() == UNIT) {
                        IUnit* unit = dynamic_cast<IUnit*>(creature);
                        unitSnapshots.push_back(unit->createSnapshot());
                    }
                }

                if(cell->hasNeutralObject())
                {
                    INeutralObject* obj = cell->getNeutralObject();
                    NeutralObjectInfo* objInfo = new NeutralObjectInfo(obj->getType(), new CoordsInfo(i, j));
                    neutralObjectsInfo.push_back(objInfo);
                }
            }
        }


        FieldSnapshot* snapshot = new FieldSnapshot(rowsAmount, columnsAmount, maximumEntitiesAmount, currentEntitiesAmount,
                                                    unitSnapshots, landscapes, neutralObjectsInfo);
        return snapshot;
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

    FieldComponent* getNext()
    {
        FieldComponent* cell = field->fieldModel[currentRow][currentColumn];
        currentRow++;
        if(currentRow == field->rowsAmount)
        {
            currentRow = 0;
            currentColumn++;
        }
        return cell;
    }
};
