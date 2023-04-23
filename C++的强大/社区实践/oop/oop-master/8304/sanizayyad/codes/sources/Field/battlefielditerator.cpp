#include "battlefielditerator.hpp"


BattleFieldIterator::BattleFieldIterator(const BattleField& battleField) : battleField(battleField)
{
    this->i = 0;
    this->j = 0;
    this->width = battleField.width;
    this->height = battleField.height;
}


bool BattleFieldIterator::hasNext() const
{
    if (i < battleField.height && j < battleField.width) {
        return true;
    }

    return false;
}


void BattleFieldIterator::first()
{
    j = 0;
    i = 0;
}


const BattleFieldIterator& operator++(BattleFieldIterator& it)
{
    if (it.j + 1 < it.width) {
        ++it.j;
    }
    else {
        ++it.i;
        it.j = 0;
    }
    return it;
}


const BattleFieldIterator operator++(BattleFieldIterator& it, int)
{
    BattleFieldIterator tmp(it);
    ++it;
    return tmp;
}


std::shared_ptr<FieldCell> BattleFieldIterator::operator*() const
{

    return battleField.battleFieldArray[i][j];
}
