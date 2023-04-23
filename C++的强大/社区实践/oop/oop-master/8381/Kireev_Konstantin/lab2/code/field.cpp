#include "field.h"

Field::~Field()
{
    for(unsigned int i = 0; i < NmRows; ++i)
    {
        for(unsigned int j = 0; j < NmColumns; ++j)
            delete fieldModel[i][j];
        delete[] fieldModel[i];
    }
    delete[] fieldModel;
}

Field::Field(unsigned int NmRows, unsigned int NmColumns, unsigned int MaxObjects)
    : NmRows(NmRows)
    , NmColumns(NmColumns)
    , MaxObjects(MaxObjects)
{
    fieldModel = new cellInterface** [NmRows];
    for(unsigned int i = 0; i < NmRows; ++i)
    {
        fieldModel[i] = new cellInterface* [NmColumns];
        for(unsigned int j = 0; j < NmColumns; ++j)
            fieldModel[i][j] = new cellInterface();
    }
    CurrObjects = 0;
}

Field::Field(const Field& field)
    : NmRows(field.NmRows)
    , NmColumns(field.NmColumns)
    , MaxObjects(field.MaxObjects)
    , CurrObjects(field.CurrObjects)
{
    fieldModel = new cellInterface** [NmRows];
    for(unsigned int i = 0; i < NmRows; i++)
    {
        fieldModel[i] = new cellInterface*[NmColumns];
        for(unsigned int j = 0; j < NmColumns; j++)
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
    : fieldModel(field.fieldModel)
    , NmRows(field.NmRows)
    , NmColumns(field.NmColumns)
    , MaxObjects(field.MaxObjects)
    , CurrObjects(field.CurrObjects)
{
    field.fieldModel = nullptr;
    field.NmRows = 0;
    field.NmColumns = 0;
}

unsigned int Field::getNmRows() const
{
    return NmRows;
}

unsigned int Field::getNmColumns() const
{
    return NmColumns;
}

void Field::setMaxObjects(unsigned int maxObjectsNewValue)
{
    MaxObjects = maxObjectsNewValue;
}

void Field::addObject(unsigned int Nrows, unsigned int Ncols, CreatureInterface *creature)
{
    if (CurrObjects == MaxObjects)
        throw std::length_error ("Error:\nThere are max objects on the field");

    if (Nrows >= NmRows || Ncols >= NmColumns)
        throw std::out_of_range ("Error:\nOut of a field size");

    cellInterface* targetCell = fieldModel[Nrows][Ncols];

    if (targetCell->hasCreature())
        throw std::invalid_argument ("Error:\nThis cell is reserved");

    if(targetCell->canHoldCreature() == false)
        throw std::invalid_argument("Error:\nLandscape is not appropriate");

    targetCell->setCreature(creature);

    if(creature->getCreatureType() != BASE)
        CurrObjects++;
}

void Field::commitFight(unsigned int NrowFrom, unsigned int NcolFrom, unsigned int NrowTo, unsigned int NcolTo)
{
    if(NrowFrom >= NmRows || NcolFrom >= NmColumns || NrowTo >= NmRows || NcolTo >= NmColumns)
        throw std::out_of_range ("Error:\nOut of a field size");

    cellInterface* cellFrom = fieldModel[NrowFrom][NcolFrom];
    cellInterface* cellTo = fieldModel[NrowTo][NcolTo];

    if(cellFrom->hasCreature() == false || cellTo->hasCreature() == false)
        throw std::invalid_argument("Impossible attack");

    if(cellFrom->getCreature()->getCreatureType() == BASE)
        throw std::invalid_argument("Base can't attack");

    UnitInterface* attackUnit = dynamic_cast<UnitInterface*>(cellFrom->getCreature());
    CreatureInterface* defendCreature = cellTo->getCreature();

    attackUnit->commitAttack(defendCreature);
}


void Field::removeObject(unsigned int Nrows, unsigned int Ncols)
{
    if (Nrows >= NmRows || Ncols >= NmColumns)
        throw std::out_of_range ("Error:\nOut of a field size");

    if (fieldModel[Nrows][Ncols] == nullptr)
        throw std::invalid_argument ("Error:\nThis cell is empty");

    delete fieldModel[Nrows][Ncols];
    fieldModel[Nrows][Ncols] = nullptr;
    CurrObjects--;
}

void Field::moveObject(unsigned int NrowFrom, unsigned int NcolFrom, unsigned int NrowTo, unsigned int NcolTo)
{
    if (NrowFrom >= NmRows || NcolFrom >= NmColumns || NrowTo >= NmRows || NcolTo >= NmColumns)
        throw std::out_of_range ("Error:\nOut of a field size");

    cellInterface* object = fieldModel[NrowFrom][NcolFrom];
    if (object == nullptr)
        throw std::invalid_argument ("Error:\nThis cell is empty");

    if (object->getCreature()->isMove() == true)
    {
        if(object->canHoldCreature() == false)
            throw std::invalid_argument("Error:\nThis landscape type can'h hold creature");

        cellInterface* newCell = fieldModel[NrowTo][NcolTo];
        if (newCell->hasCreature())
            throw std::invalid_argument ("Error:\nNew cell is not empty");
        else
        {
            newCell->setCreature(object->getCreature());
            object->setCreature(nullptr);
        }
    }
    else
        throw std::invalid_argument ("Error:\nObject is not mobile");
}

cellInterface* Field::getCell(unsigned int Nrow, unsigned int Ncol)
{
    if(Nrow >= NmRows || Ncol >= NmColumns)
        throw std::out_of_range("Error:\nOut of a field size");
    else
        return fieldModel[Nrow][Ncol];
}

QString Field::getStringInfo(int cols)
{
    QString returnable = nullptr;
    for (int k=0;k<cols;k++)
        returnable.append(" ----------------");
    returnable.append("\n");
    for(unsigned int i = 0; i < NmRows; i++)
    {
        for(int objectCnt = 0; objectCnt < 3; objectCnt++)
        {
            QString temp_str = nullptr;
            for(unsigned int j = 0; j < NmColumns; j++)
            {
                cellInterface* cell = getCell(i,j);
                QString temporary = nullptr;
                switch (objectCnt) {
                    case 0:
                        temporary.append("|   ");
                        temporary.append(cell->getCreatureInfo());
                        while(temporary.size() <= 11) temporary.append(" ");
                        while(temporary.size() <= 16) temporary.append(" ");
                        break;
                    case 1:
                        temporary.append("|   ");
                        temporary.append(cell->getObjectInfo());
                        while(temporary.size() <= 11) temporary.append(" ");
                        while(temporary.size() <= 16) temporary.append(" ");
                        break;
                    case 2:
                        temporary.append("|   ");
                        temporary.append(cell->getLandscapeInfo());
                        while(temporary.size() <= 11) temporary.append(" ");
                        while(temporary.size() <= 16) temporary.append(" ");
                        break;
                }
                temp_str += temporary;
            }
            returnable.append(temp_str);
            returnable.append("|\n");
        }
        for (int k=0;k<cols;k++)
            returnable.append(" ----------------");
        returnable.append("\n");
    }

    return returnable;
}
