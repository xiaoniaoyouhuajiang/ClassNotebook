#ifndef GAMEFIELDITERATOR_H
#define GAMEFIELDITERATOR_H

#include "cellofgamefield.h"


class GameField;


class GameFieldIterator
{
public:
    GameFieldIterator(const GameField& gameField);

    bool hasNext() const;
    void first();
    friend const GameFieldIterator& operator++(GameFieldIterator& it);
    friend const GameFieldIterator operator++(GameFieldIterator& it, int);
    CellOfGameField& operator*() const;

private:
    size_t i;
    size_t j;
    size_t width;
    size_t height;
    const GameField& gameField;
};

#endif // GAMEFIELDITERATOR_H
