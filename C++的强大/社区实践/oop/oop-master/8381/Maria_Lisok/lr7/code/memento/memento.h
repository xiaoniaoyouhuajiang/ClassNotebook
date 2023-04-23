#ifndef MEMENTO_H
#define MEMENTO_H

#include "gameparam.h"

class Memento{
public:
    virtual ~Memento()=default;
    virtual GameParam* loadFromFile()=0;
};
#endif // MEMENTO_H
