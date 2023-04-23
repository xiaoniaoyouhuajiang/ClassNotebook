#pragma once
#include <string>

//#include <list>
#include "observer/ipublisher.h"
//#include "field/cell.h"
//#include "observer/iobserver.h"

//class Cell;
//class IPublisher;

class Object
{
public:
    Object();
    virtual ~Object();

    std::string symb; //путь до картинки
    int health;
    int x, y;
    int numBase = 0;

    bool isUnit = false;
    bool isBase = false;
    bool isNeutral = false;

    virtual bool canMove(int x, int y);
};
