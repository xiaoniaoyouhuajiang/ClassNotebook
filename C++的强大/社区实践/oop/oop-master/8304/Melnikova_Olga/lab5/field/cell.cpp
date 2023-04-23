#include <iostream>
#include "cell.h"


Cell::Cell() {
    this->x = 0;
    this->y = 0;
    this->innerObject = nullptr;
}

Cell::Cell(int x, int y) : x(x), y(y), innerObject(nullptr) {}

Cell::Cell(const Cell &cell) : x(cell.x), y(cell.y) {
    if (cell.innerObject) {
        this->innerObject = cell.innerObject;
    } else {
        this->innerObject = nullptr;
    }
}
Cell::~Cell() {
//    if (this->innerObject)
//        delete &this->innerObject;
}

Cell::Cell(Cell &&cell) : x(cell.x), y(cell.y), innerObject(cell.innerObject) {
    cell.x = 0;
    cell.y = 0;
}

Cell& Cell::operator=(const Cell &cell) {
    if (&cell == this)
        return *this;
    delete this->innerObject;
    this->x = cell.x;
    this->y = cell.y;
    if (cell.innerObject) {
        this->innerObject = cell.innerObject;
    } else {
        this->innerObject = nullptr;
    }
    return *this;
}

Cell& Cell::operator=(const Cell &&cell) {
    if (&cell == this)
        return *this;
    delete this->innerObject;
    this->x = cell.x;
    this->y = cell.y;
    this->innerObject = cell.innerObject;
    return *this;
}
