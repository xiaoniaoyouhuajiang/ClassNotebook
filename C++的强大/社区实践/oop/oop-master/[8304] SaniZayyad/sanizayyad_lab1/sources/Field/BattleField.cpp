#include "BattleField.hpp"
#include "battlefielditerator.hpp"

BattleField::BattleField(size_t height, size_t width) :
    height(height), width(width),
    battleFieldArray(std::make_unique<std::unique_ptr<FieldCell[]>[]>(height))

{
    this->numberOfUnits = 0;

    for (size_t i = 0; i < height; ++i) {
        battleFieldArray[i] = std::make_unique<FieldCell[]>(width);
    }
}


BattleField::BattleField(const BattleField& battleField)
{
    std::cout<<"\nconstructoeree\n";
    battleFieldArray = std::make_unique<std::unique_ptr<FieldCell[]>[]>(battleField.height);

    height = battleField.height;
    width = battleField.width;
    numberOfUnits = battleField.numberOfUnits;

    for (size_t i = 0; i < height; ++i) {
        battleFieldArray[i] = std::make_unique<FieldCell[]>(width);
    }

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            battleFieldArray[i][j] = battleField.battleFieldArray[i][j];
        }
    }
}


BattleField& BattleField::operator=(const BattleField& battleField)
{
    std::cout<<"\asiignmentttt\n";

    if (this == &battleField) {
        return *this;
    }

    for (size_t i = 0; i < height; ++i) {
        battleFieldArray[i].reset();
    }
    battleFieldArray.reset();

    battleFieldArray = std::make_unique<std::unique_ptr<FieldCell[]>[]>(battleField.height);

    height = battleField.height;
    width = battleField.width;
    numberOfUnits = battleField.numberOfUnits;

    for (size_t i = 0; i < height; ++i) {
        battleFieldArray[i] = std::make_unique<FieldCell[]>(width);
    }

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            battleFieldArray[i][j] = battleField.battleFieldArray[i][j];
        }
    }

    return *this;
}


BattleField::BattleField(BattleField&& battleField)
{
    std::cout<<"\tf 1\n";

    height = battleField.height;
    width = battleField.width;
    numberOfUnits = battleField.numberOfUnits;

    battleField.height = 0;
    battleField.width = 0;
    battleField.numberOfUnits = 0;

    battleFieldArray = std::move(battleField.battleFieldArray);
}


BattleField& BattleField::operator=(BattleField&& battleField)
{
    std::cout<<"\tf2222222\n";

    if (this == &battleField) {
        return* this;
    }

    for (size_t i = 0; i < height; ++i) {
        battleFieldArray[i].reset();
    }
    battleFieldArray.reset();

    height = battleField.height;
    width = battleField.width;
    numberOfUnits = battleField.numberOfUnits;

    battleField.height = 0;
    battleField.width = 0;
    battleField.numberOfUnits = 0;

    battleFieldArray = std::move(battleField.battleFieldArray);

    return *this;
}


size_t BattleField::getWidth() const
{
    return width;
}


size_t BattleField::getHeight() const
{
    return height;
}


size_t BattleField::getNumberOfUnits() const
{
    return numberOfUnits;
}


bool BattleField::addUnit(std::shared_ptr<Unit> unit)
{
    Position2D position = unit->getPosition();

    if (!battleFieldArray[position.y][position.x].isEmpty()) {
        return false;
    }

    battleFieldArray[position.y][position.x].addUnit(unit);
    numberOfUnits++;

    return true;
}


FieldCell& BattleField::getFieldCell(const Position2D &position)
{
    return battleFieldArray[position.y][position.x];
}

void BattleField::getFieldCellInfo(const Position2D &position)
{
   auto unit = getFieldCell(position).isEmpty();
   if(!unit)
        getFieldCell(position).getUnit()->getUnitInfo();
   else{
       std::cout<<"At position X=" << position.x << " Y="<< position.y<<" Cell is Empty :(\n";
    }


}

void BattleField::deleteUnit(std::shared_ptr<Unit> unit)
{
   ;
    
    auto it = std::unique_ptr<BattleFieldIterator>(new BattleFieldIterator(*this));

    for (it->first(); it->hasNext(); ++*it) {
        if ((**it).getUnit() == unit) {
            (**it).deleteUnit();
        }
    }
    numberOfUnits--;
    unit.reset();
}

void BattleField::deleteUnitCord(Position2D position)
{
    auto unit = getFieldCell(position).isEmpty();
    
    if(!unit){
           getFieldCell(position).getUnit().reset();
           getFieldCell(position).deleteUnit();
       }
      else{
          std::cout<<"Empty!";

       }
    numberOfUnits--;
}
