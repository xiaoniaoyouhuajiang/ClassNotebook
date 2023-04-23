#include "iterator.h"

Iterator::Iterator(GameField* field) : field(field), cur(field->pointsMap[0][0]->unit), x(0), y(0), isFirstIter(true)
{

}

bool Iterator::hasNext()
{
    int x = this->x;
    int y = this->y;
    while (true){
        if (x == field->x){
            x = 0;
            y++;
        }
        if (y >= field->y)
            return false;

        if (field->pointsMap[y][x]->unit != nullptr) {
            if (isFirstIter){
                this->y = y;
                this->x = x;
                cur = field->pointsMap[y][x]->unit;
                isFirstIter = false;
            }
            return true;
        }
        x++;
    }
}

Unit*& Iterator::operator++(int)
{
    while (true){
        x++;
        if (x == field->x){
            x = 0;
            y++;
        }
        if (y >= field->y){
            Unit* unit = nullptr;
            return unit;
        }

        if (field->pointsMap[y][x]->unit != nullptr) {
            cur = field->pointsMap[y][x]->unit;
            return cur;
        }
    }
}

bool Iterator::operator!= (const Iterator& iter)
{
    return cur != iter.cur;
}

Unit*& Iterator::operator*()
{
    return cur;
}

