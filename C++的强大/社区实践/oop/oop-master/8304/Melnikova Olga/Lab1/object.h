#pragma once
#include <string>

constexpr double LIGHT_HEALTH = 1;
constexpr double MEDIUM_HEALTH = 2;

class Cell;
class Object
{
public:
    Object();
//    Object(const Object& object);
//    Object(const Object&& object);
//    Object& operator=(const Object& object);
//    Object& operator=(const Object&& object);
    //std::string name;
    char symb;
    int health;
    //Object& copy;
    //Cell* cell;
    int x, y;

    bool canMove(int x, int y);
    //int moveToCell(Cell& newCell);

    //Object* copy();

};
