#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "cell.h"
#include "objects/object.h"
#include "objects/units/unit.h"

class BattleFieldIterator;

class Field
{
    friend BattleFieldIterator;
private:
    Cell** _cells; // двумерый массив ячеек поля

public:
    Field(int height, int width);   // конструктор
    ~Field();                       // деконструктор
    Field(const Field& field);
    Field(Field&& field);
    Field& operator=(const Field& field);
    Field& operator=(Field&& field);

    std::string renderField(); //рисование поля

    void print(); //рисование сетки

    int addObject(Object* object, int x, int y); // вставка объекта
    int addObject(Object* object, Cell& cell); // вставка объекта

    int deleteObject(int x, int y); // удаление объекта
    int deleteObject(Cell& cell); // удаление объекта
    int deleteObject(Object& unit); // удаление объекта

    Field copy(); // копирование поля с объектами

    int H, W; // должны быть произвольными
    int countObjects = 0; // кол-во эл. на поле

    Cell** getCells();
    Cell& cells(int x, int y);

    int moveObject(int x1, int y1, int x2, int y2);
};
