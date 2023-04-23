#include "object.h"
#include "cell.h"

Object::Object()
{
    symb = ' ';
    health = 0;
    x = 0;
    y = 0;
    //cell = nullptr;
}


bool Object::canMove(int x, int y) {
    return true;
}

