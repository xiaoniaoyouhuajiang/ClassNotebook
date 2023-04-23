#pragma once

#include "iobserver.h"

class Observer : public IObserver   //издатель
{
public:
    //Observer();
    //Observer(Object* observingObject);
    ~Observer();
    //Object* observingObject;
    void update(std::string message) override;
};
