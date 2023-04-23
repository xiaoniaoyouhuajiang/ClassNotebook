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
    virtual bool canMove(int x, int y);
};
