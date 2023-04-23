#include "gamefield.h"

using namespace unit;


GameField::GameField(size_t height, size_t width) :
    height(height), width(width),
    array(height, std::vector<std::shared_ptr<CellOfField>>(width))


{
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            array[i][j] = std::make_shared<CellOfField>();
        }
    }
    RandomObjectFactory factory;
}


GameField::GameField(const GameField& gameField)
{
    doCopy(gameField);
}


GameField& GameField::operator=(const GameField& gameField)
{
    if (this == &gameField) {
        return *this;
    }

    doCopy(gameField);

    return *this;
}


GameField::GameField(GameField&& gameField)
{
    doMove(gameField);
}


GameField& GameField::operator=(GameField&& gameField)
{
    if (this == &gameField) {
        return* this;
    }

    doMove(gameField);

    return *this;
}


size_t GameField::getWidth() const
{
    return width;
}


size_t GameField::getHeight() const
{
    return height;
}


bool GameField::addUnit(std::shared_ptr<Unit> unit)
{
    if (unit) {
        Point2D point = unit->getPosition();

        if (!array[point.y][point.x]->isEmpty()) {
            return false;
        }

        array[point.y][point.x]->addUnit(unit);

        return true;
    }

    return false;
}


std::shared_ptr<CellOfField> GameField::getCell(const Point2D& point) const
{
    return array[point.y][point.x];
}


void GameField::deleteUnit(std::shared_ptr<Unit> unit)
{
    if (unit) {
        auto pos = unit->getPosition();
        array[pos.y][pos.x]->deleteUnit();
    }
}


std::shared_ptr<GameFieldIterator> GameField::getIterator() const
{
    return std::shared_ptr<GameFieldIterator>(new GameFieldIterator(*this));
}


void GameField::doCopy(const GameField& gameField)
{
    array.clear();
    array.resize(gameField.height);
    for (size_t i = 0; i < gameField.height; ++i) {
        array[i].resize(gameField.width);
    }

    height = gameField.height;
    width = gameField.width;

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            array[i][j] = std::make_shared<CellOfField>(*gameField.array[i][j]);
        }
    }
}


void GameField::doMove(GameField& gameField)
{
    height = gameField.height;
    width = gameField.width;

    gameField.height = 0;
    gameField.width = 0;

    array = std::move(gameField.array);
}
