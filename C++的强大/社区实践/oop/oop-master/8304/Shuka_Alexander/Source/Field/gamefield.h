#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <memory>
#include <vector>

#include "Field/celloffield.h"
#include "Field/point2d.h"
#include "Field/iterator.h"

#include "Factory/ObjectFactory/randomobjectfactory.h"
#include "Factory/ObjectFactory/noobjectfactory.h"


class GameFieldIterator;


class GameField
{
    friend class GameFieldIterator;

public:
    explicit GameField(size_t height, size_t width);

    GameField(const GameField& gameField);
    GameField& operator=(const GameField& gameField);
    GameField(GameField&& gameField);
    GameField& operator=(GameField&& gameField);

    size_t getWidth() const;
    size_t getHeight() const;

    bool addUnit(std::shared_ptr<unit::Unit> unit);
    void deleteUnit(std::shared_ptr<unit::Unit> unit);

    std::shared_ptr<CellOfField> getCell(const Point2D& point) const;

    std::shared_ptr<GameFieldIterator> getIterator() const;

private:
    void doCopy(const GameField& gameField);
    void doMove(GameField& gameField);

private:
    size_t height;
    size_t width;
    std::vector<std::vector<std::shared_ptr<CellOfField>>> array;
};

#endif // GAMEFIELD_H
