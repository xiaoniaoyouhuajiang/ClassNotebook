//
// Created by therealyou on 11.02.2020.
//
/**
 * Игровое поле является контейнером для объектов представляющим прямоугольную сетку.
 * Основные требования к классу игрового поля:
 * Создание поля произвольного размера
 * Контроль максимального количества объектов на поле
 * Возможность добавления и удаления объектов на поле
 * Возможность копирования поля (включая объекты на нем)
 * Для хранения запрещается использовать контейнеры из stl
 * */

#ifndef LAB1_GAMEFIELD_H
#define LAB1_GAMEFIELD_H

#define DEFAULT_X 4
#define DEFAULT_Y 5
#define DEFAULT_VALUE '-'

#include <iostream>
#include "Unit.h"

struct Cell{
    void *unit;
    char valueAsChar = DEFAULT_VALUE;
};

typedef Cell baseType;

class Unit;

class GameField {
private:
    baseType** matrix;
    int width;
    int height;
    int countUnits = 0;
    int maxCountUnits;

public:

    GameField();

    GameField(int x, int y);

    GameField(const GameField* gameField);

    void setCountUnits();

    void printField();

    void setMatrix();

    void setMatrix(baseType** matrix);

    void setWidth(int width);

    void setHeight(int height);

    int addUnit(Unit* unit, int x, int y);

    void deleteUnit(int x, int y);

    void move(Unit* unit, int dx, int dy);
};


#endif //LAB1_GAMEFIELD_H
