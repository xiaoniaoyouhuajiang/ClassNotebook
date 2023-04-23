#include "Object.h"

Point Object::getCoords() const {
    return this->coords;
}

ObjectType Object::type() const{
    return OBJECT;
}