#ifndef NEW_LR1_GAMEFIELD_H
#define NEW_LR1_GAMEFIELD_H


#include <cstdio>
#include "Tale.h"
#include "Object/Object.h"
#include "FieldIterator.h"
#include "Landscape/LandscapeFactory.h"

class FieldIterator;

class GameField
{
    friend FieldIterator;
public:
    GameField(size_t height, size_t width);
    ~GameField();

    int addObject(Object* object, size_t x, size_t y);
    void deleteObject(size_t x, size_t y);
    void moveObject(size_t x1, size_t y1, size_t x2, size_t y2);
    void printField();
    void swap(GameField& other);
    GameField(const GameField& other);
    GameField& operator=(GameField const& other);
    GameField& operator=(GameField&& other);
    size_t height_;
    size_t width_;
private:
    LandscapeFactory landscapeFactory_;
    size_t maxOfObjects_;
    size_t objectCounter_;
    Tale** field_;
};


#endif //NEW_LR1_GAMEFIELD_H
