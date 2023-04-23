#pragma once
#include <list>
#include <string>
//#include "objects/object.h"

//class Object;
class IObserver   //интерфейс издателя
{
public:

    virtual ~IObserver();
    virtual void update(std::string message) = 0;

    //Object* observingObject;
};
