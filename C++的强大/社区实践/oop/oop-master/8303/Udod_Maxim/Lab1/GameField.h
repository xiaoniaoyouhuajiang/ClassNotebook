//
// Created by shenk on 14.02.2020.
//

#ifndef UNTITLED13_GAMEFIELD_H
#define UNTITLED13_GAMEFIELD_H

#include "Point.h"
#include "Units/Unit.h"
#include "GameFieldIterator.h"

class Unit;

class GameField {

private:

    Unit ***field;

    const int fieldHeight;
    const int fieldWidth;

    const int maxObjectsCount = 3;
    int objectsCount;

public:

    explicit GameField(int fieldSize);
    GameField(int fieldHeight, int fieldWidth);
    GameField(const GameField &other);
    GameField(GameField &&other);

    ~GameField();

    void deleteObject(int x, int y);
    void deleteObject(const Point &point);
    void deleteObject(Unit *object);

    void addObject(Unit *object, int x, int y);

    void moveObject(const Point &p1, const Point &p2);
    void moveObject(Unit *object, const Point &p2);

    int getHeight() const;
    int getWidth() const;
    Unit *getObject(const Point &p) const;

    GameFieldIterator begin(){ return GameFieldIterator(Point(0, 0), field, fieldHeight, fieldWidth); }
    GameFieldIterator end(){ return GameFieldIterator(Point(0, fieldHeight), field, fieldHeight, fieldWidth); }

};

#endif //UNTITLED13_GAMEFIELD_H
