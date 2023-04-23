#include "object.h"

Object::Object()
{
    symb = "";
    health = 0;
    x = 0;
    y = 0;
}

bool Object::canMove(int x, int y) {
    return true;
}

Object::~Object() {}
