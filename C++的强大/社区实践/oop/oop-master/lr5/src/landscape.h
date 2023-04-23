#include "unit.h"
#ifndef LANDSCAPE_H
#define LANDSCAPE_H


/* ландшафт и паттерн "Прокси" */

class Proxy {
public:
    bool moving();
    bool notMoving();
};

class Landscape{
public:
    Proxy land;
    char sym;
    virtual bool interaction(Unit* unit) = 0;
  //  virtual ~Landscape();
};


class Forest: public Landscape{

public:
    Forest();
    bool interaction(Unit* unit);
};

class Plain: public Landscape{
public:
    Plain();
    bool interaction (Unit* unit);
};

class Swamp: public Landscape{
public:
    Swamp();
    bool interaction(Unit* unit);
};

#endif // LANDSCAPE_H
