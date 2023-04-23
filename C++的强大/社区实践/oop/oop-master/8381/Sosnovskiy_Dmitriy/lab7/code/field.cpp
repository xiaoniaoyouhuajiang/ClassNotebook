#include "field.h"

Field::~Field()
{
    for(unsigned int i = 0; i < rowsAmount; i++)
    {
        for(unsigned int j = 0; j < columnsAmount; j++)
        {
            delete fieldModel[i][j];
        }
        delete [] fieldModel[i];
    }
    delete [] fieldModel;
}

Field::Field(unsigned int rowsAmount, unsigned int columnsAmount, unsigned int maximumEntitiesAmount):
    rowsAmount(rowsAmount),
    columnsAmount(columnsAmount),
    maximumEntitiesAmount(maximumEntitiesAmount)
{
    fieldModel = new FieldComponent**[rowsAmount];
    for(unsigned int i = 0; i < rowsAmount; i++)
    {
        fieldModel[i] = new FieldComponent*[columnsAmount];
        for(unsigned int j = 0; j < columnsAmount; j++)
        {
            fieldModel[i][j] = new FieldComponent();
        }
    }

    currentEntitiesAmount = 0;
}

Field::Field(const Field& field)
    :rowsAmount(field.rowsAmount),
     columnsAmount(field.columnsAmount),
     maximumEntitiesAmount(field.maximumEntitiesAmount),
     currentEntitiesAmount(field.currentEntitiesAmount)
{
    fieldModel = new FieldComponent**[rowsAmount];
    for(unsigned int i = 0; i < rowsAmount; i++)
    {
        fieldModel[i] = new FieldComponent*[columnsAmount];
        for(unsigned int j = 0; j < columnsAmount; j++)
        {
            fieldModel[i][j] = nullptr;
            if(field.fieldModel[i][j] != nullptr)
            {
                fieldModel[i][j] = field.fieldModel[i][j]->copy();
            }
        }
    }
}

Field::Field(Field&& field)
    :fieldModel(field.fieldModel),
     rowsAmount(field.rowsAmount),
     columnsAmount(field.columnsAmount),
     maximumEntitiesAmount(field.maximumEntitiesAmount),
     currentEntitiesAmount(field.currentEntitiesAmount)
{
    field.fieldModel = nullptr;
    field.rowsAmount = 0;
    field.columnsAmount = 0;

}

unsigned int Field::getRowsAmount() const { return rowsAmount; }

unsigned int Field::getColumnsAmount() const { return columnsAmount; }

void Field::setMaximumEntitiesAmount(unsigned int newMaximumEntitiesAmount)
{
    maximumEntitiesAmount = newMaximumEntitiesAmount;
}

void Field::placeCreature(unsigned int rowNumber, unsigned int columnNumber, ICreature *creature)
{
    if(currentEntitiesAmount == maximumEntitiesAmount && creature->getCreatureType() != BASE)
        throw  new Exception(80, "Error in the placing creature", "Limit of entities has been reached.");

    if(rowNumber >= rowsAmount ||
       columnNumber >= columnsAmount)
        throw new Exception(84, "Error in the placing creature", "Coordinate is out-of-range to field size.");

    FieldComponent* targetCell = fieldModel[rowNumber][columnNumber];

    if(creature->getCreatureType() == BASE) targetCell->setLandscape(new Ground());

    if(targetCell->hasCreature()) throw new Exception(90, "Error in the placing creature", "There is a creature on " + QString::number(rowNumber) + " " + QString::number(columnNumber));

    if(targetCell->canHoldCreature() == false) throw new Exception(80, "Error in the placing creature", "Water is places on " + QString::number(rowNumber) + " " + QString::number(columnNumber) + " so unit can't be here");

    targetCell->setCreature(creature);

    if(creature->getCreatureType() != BASE)
        currentEntitiesAmount++;

    creature->setCoordinates(rowNumber, columnNumber);
}

void Field::moveUnit(unsigned int rowNumberFrom, unsigned int columnNumberFrom,
                     unsigned int rowNumberTo, unsigned int columnNumberTo,
                     unsigned int actorId)
{
    if(rowNumberFrom >= rowsAmount ||
       columnNumberFrom >= columnsAmount ||
       rowNumberTo >= rowsAmount ||
       columnNumberTo >= columnsAmount) throw new Exception(109, "Error in moving the creature", "The range of moving is out-of a field size.");


    FieldComponent* cell = fieldModel[rowNumberFrom][columnNumberFrom];

    FieldComponent* targetCell = fieldModel[rowNumberTo][columnNumberTo];

    if(cell->hasCreature() == false)
        throw new Exception(116, "Error in the moving creature", "The cell " + QString::number(rowNumberFrom) + " " + QString::number(columnNumberFrom) + " is empty. Nothing to move");

    if(cell->getCreature()->getPossessorId() != actorId)
        throw new Exception(120, "Error in the moving creature", "Player " + QString::number(actorId) + " is not a possessor of this unit.");


    if(cell->getCreature()->isMoveable() == true)
    {
        if(targetCell->canHoldCreature() == false)
            throw new Exception(125, "Error in the moving creature", "The cell " + QString::number(rowNumberTo) + " " + QString::number(columnNumberTo) + " can't hold any creatures.");


        FieldComponent* cellMoveInto = fieldModel[rowNumberTo][columnNumberTo];
        if(cellMoveInto->hasCreature())
            throw new Exception(131, "Error in the moving creature", "The cell " + QString::number(rowNumberTo) + " " + QString::number(columnNumberTo) + " is not empty. Moving is impossible.");
        else {
            cellMoveInto->setCreature(cell->getCreature());
            cell->setCreature(nullptr);

            cellMoveInto->getCreature()->setCoordinates(rowNumberTo, columnNumberTo);
        }
    }
    else
        throw new Exception(140, "Error in the moving creature", "The cell " + QString::number(rowNumberFrom) + " " + QString::number(columnNumberFrom) + " is not moveable. You can't move it anyway.");
}

void Field::commitFight(unsigned int rowNumberFrom, unsigned int columnNumberFrom,
                        unsigned int rowNumberTo, unsigned int columnNumberTo,
                        unsigned int actorId)
{
    if(rowNumberFrom >= rowsAmount ||
       columnNumberFrom >= columnsAmount ||
       rowNumberTo >= rowsAmount ||
       columnNumberTo >= columnsAmount)
        throw new Exception(151, "Error in the commiting fight", "The coordinates are not appropriate to the field size. Check them out and repeat.");


    FieldComponent* cellFrom = fieldModel[rowNumberFrom][columnNumberFrom];
    FieldComponent* cellTo = fieldModel[rowNumberTo][columnNumberTo];

    if(cellFrom->hasCreature() == false)
        throw new Exception(158, "Error in the commiting fight", "The cell " + QString::number(rowNumberFrom) + " " + QString::number(columnNumberFrom) + " is empty. Can't commit attack");

    if(cellTo->hasCreature() == false)
        throw new Exception(161, "Error in the commiting fight", "The cell " + QString::number(rowNumberTo) + " " + QString::number(columnNumberTo) + " is empty. Can't commit attack");


    if(cellFrom->getCreature()->getPossessorId() != actorId)
        throw new Exception(162, "Error in the commiting fight", "Player " + QString::number(actorId) + " is not a possessor of this unit.");

    if(cellFrom->getCreature()->getCreatureType() == BASE)
        throw new Exception(165, "Error in the commiting fight", "Base is placed here. It can't commit attack.");


    IUnit* attackUnit = dynamic_cast<IUnit*>(cellFrom->getCreature());
    ICreature* defendCreature = cellTo->getCreature();



    //Mediator implementation
    FightMediator* fightMediator = new FightMediator;

    fightMediator->commitFight(attackUnit, defendCreature);
}

FieldComponent* Field::getCell(unsigned int rowNumber, unsigned int columnNumber)
{
    if(rowNumber >= rowsAmount ||
       columnNumber >= columnsAmount)
        throw new Exception(183, "Error in the getting cell", "Arguments are out-of-field-size");


    else return fieldModel[rowNumber][columnNumber];
}

QString Field::getAsString()
{
    QString returnable = nullptr;
    for(unsigned int i = 0; i < rowsAmount; i++)
    {
        for(int objectCnt = 0; objectCnt < 3; objectCnt++)
        {
            QString temp_str = nullptr;
            for(unsigned int j = 0; j < columnsAmount; j++)
            {
                FieldComponent* cell = getCell(i,j);
                QString temporary = nullptr;
                switch (objectCnt) {
                    case 0:
                        temporary.append(cell->getCreatureInfo());
                        while(temporary.size() <= 15) temporary.append(" ");
                        break;
                    case 1:
                        temporary.append(cell->getObjectInfo());
                        while(temporary.size() <= 15) temporary.append(" ");
                        break;
                    case 2:
                        temporary.append(cell->getLandscapeInfo());
                        while(temporary.size() <= 15) temporary.append(" ");
                        break;
                }
                temp_str += temporary;
            }
            returnable.append(temp_str);
            returnable.append("\n");
        }
        returnable.append("\n");
    }

    return returnable;
}


