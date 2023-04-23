#include "Field.h"


Field::Iterator::Iterator(Field* field, Cell* cell) {
    this->field = field;
    this->cell = cell;
}


Cell& Field::Iterator::operator*() {
    return *cell;
}

Cell* Field::Iterator::operator->() {
    return cell;
}


bool operator== (const Field::Iterator& iter1, const Field::Iterator& iter2) {
    return (iter1.cell == iter2.cell);
}

bool operator!= (const Field::Iterator& iter1, const Field::Iterator& iter2) {
    return (iter1.cell != iter2.cell);
}


Cell& Field::Iterator::operator++() {
    if (cell == field->end().cell)
        return *cell;

    if (cell->getX() + 1 < field->getWidth() || cell->getY() + 1 == field->getHeight()) {
        cell += 1;
    }
    else {
        cell = field->getCell(Point(0, cell->getY() + 1));
    }
    return *cell;
}

Cell& Field::Iterator::operator++(int) {
    if (cell == field->end().cell)
        return *cell;

    Cell* tempCell = cell;
    if (cell->getX() + 1 < field->getWidth() || cell->getY() + 1 == field->getHeight()) {
        cell += 1;
    }
    else {
        cell = field->getCell(Point(0, cell->getY() + 1));
    }
    return *tempCell;
}

Cell& Field::Iterator::operator--() {
    if (cell == field->begin().cell - 1)
        return *cell;

    if (cell->getX() > 0 || cell->getY() == 0) {
        cell -= 1;
    }
    else {
        cell = field->getCell(Point(field->getWidth() - 1, cell->getY() - 1));
    }
    return *cell;
}

Cell& Field::Iterator::operator--(int) {
    if (cell == field->begin().cell - 1)
        return *cell;

    Cell* tempCell = cell;
    if (cell->getX() > 0 || cell->getY() == 0) {
        cell -= 1;
    }
    else {
        cell = field->getCell(Point(field->getWidth() - 1, cell->getY() - 1));
    }
    return *tempCell;
}


Cell& Field::Iterator::operator+=(int n) {
    for (int i = 0; i < n && cell != field->end().cell; i++)
        ++(*this);
    return *cell;
}
Cell& Field::Iterator::operator-=(int n) {
    for (int i = 0; i < n && cell != field->begin().cell - 1; i++)
        --(*this);
    return *cell;
}


Cell& Field::Iterator::operator+(int n) {
    Field::Iterator tempIter = *this;
    tempIter += n;
    return *tempIter;
}

Cell& Field::Iterator::operator-(int n) {
    Field::Iterator tempIter = *this;
    tempIter -= n;
    return *tempIter;
}
