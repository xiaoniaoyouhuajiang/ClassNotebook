#include "BattleField.hpp"
#include "battlefielditerator.hpp"

using namespace unit;

BattleField::BattleField(int height, int width) :
    height(height), width(width),
    battleFieldArray(height, std::vector<std::shared_ptr<FieldCell>>(width))

{
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            battleFieldArray[i][j] = std::make_shared<FieldCell>();
        }
    }
}


BattleField::BattleField(const BattleField& battleField)
{
    copy(battleField);
}


BattleField& BattleField::operator=(const BattleField& battleField)
{
   if (this == &battleField) {
        return *this;
    }

    copy(battleField);

    return *this;
}


BattleField::BattleField(BattleField&& battleField)
{
    move(battleField);
}


BattleField& BattleField::operator=(BattleField&& battleField)
{
    if (this == &battleField) {
        return* this;
    }

    move(battleField);

    return *this;
}


int BattleField::getWidth() const
{
    return width;
}


int BattleField::getHeight() const
{
    return height;
}



bool BattleField::addUnit(std::shared_ptr<unit::Unit> unit)
{
    if (unit) {
        Position2D position = unit->getPosition();

        if (!battleFieldArray[position.y][position.x]->isEmpty()) {
            return false;
        }

        battleFieldArray[position.y][position.x]->addUnit(unit);

        return true;
    }

    return false;
    
}


std::shared_ptr<FieldCell> BattleField::getFieldCell(const Position2D &position)
{
    return battleFieldArray[position.y][position.x];
}

void BattleField::getFieldCellInfo(const Position2D &position)
{
   auto unit = getFieldCell(position)->isEmpty();
   if(!unit)
        getFieldCell(position)->getUnit()->getUnitInfo();
   else{
       std::cout<<"At position X=" << position.x << " Y="<< position.y<<" Cell is Empty :(\n";
    }


}

void BattleField::deleteUnit(std::shared_ptr<unit::Unit> unit)
{
    if (unit) {
        auto pos = unit->getPosition();
        battleFieldArray[pos.y][pos.x]->deleteUnit();
    }}

void BattleField::deleteUnitCord(Position2D pos)
{
    auto unit = getFieldCell(pos)->isEmpty();
    
    if(!unit){
        battleFieldArray[pos.y][pos.x]->deleteUnit();
     }
      else{
          std::cout<<"Empty!";
       }
}

std::shared_ptr<BattleFieldIterator> BattleField::getIterator() const
{
    return std::shared_ptr<BattleFieldIterator>(new BattleFieldIterator(*this));
}

void BattleField::copy(const BattleField& battleField)
{
    battleFieldArray.clear();
    battleFieldArray.resize(battleField.height);
    for (int i = 0; i < battleField.height; ++i) {
        battleFieldArray[i].resize(battleField.width);
    }

    height = battleField.height;
    width = battleField.width;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            battleFieldArray[i][j] = std::make_shared<FieldCell>(*battleField.battleFieldArray[i][j]);
        }
    }
}


void BattleField::move(BattleField& battleField)
{
    height = battleField.height;
    width = battleField.width;

    battleField.height = 0;
    battleField.width = 0;

    battleFieldArray = std::move(battleField.battleFieldArray);
}
