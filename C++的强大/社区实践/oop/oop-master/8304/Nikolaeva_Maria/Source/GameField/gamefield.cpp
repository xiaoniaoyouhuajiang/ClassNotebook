#include "gamefield.h"


GameField::GameField(size_t height, size_t width)
{
    this->height = height;
    this->width = width;
    this->numberOfUnits = 0;

    this->field = new CellOfGameField* [height];
    for (size_t i = 0; i < height; ++i) {
        field[i] = new CellOfGameField [width];
    }

}


GameField::~GameField()
{
    for (size_t i = 0; i < height; ++i) {
        delete [] field[i];
    }
    delete [] field;
}


bool GameField::addUnit(Unit* unit)
{
    Point2D coordinate = unit->getCoordiante();
    if (coordinate.y <= static_cast<int>(this->height) &&
            coordinate.x <= static_cast<int>(this->width)) {
        field[coordinate.y][coordinate.x].addUnit(unit);
        numberOfUnits++;

        return true;
    }

    return false;
}


void GameField::deleteUnit(Unit* unit)
{
    Point2D coordinate = unit->getCoordiante();
    field[coordinate.y][coordinate.x].deleteUnit();
    numberOfUnits--;
}


CellOfGameField* GameField::getCell(int x, int y)
{
    if (y <= static_cast<int>(this->height) &&
            x <= static_cast<int>(this->width)) {
        return &this->field[y][x];
    }

    return nullptr;
}

int GameField::getWidth()
{
    return this->width;
}

int GameField::getHeight()
{
    return this->height;
}

size_t GameField::getNumberOfUnits()
{
    return this->numberOfUnits;
}


GameField* GameField::clone()
{
    GameField* field = new GameField(this->height, this->width);

    for (size_t i = 0; i < this->height; ++i) {
        for (size_t j = 0; j < this->width; ++j) {
            field->field[i][j] = this->field[i][j];
        }
    }

    return field;
}

GameFieldIterator GameField::getIterator() const
{
    return GameFieldIterator(*this);
}
