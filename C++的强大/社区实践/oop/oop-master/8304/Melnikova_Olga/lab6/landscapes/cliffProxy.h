#pragma once

#include "landscape.h"
#include "cliff.h"
#include "strategies/istrategy.h"

class CliffProxy : public Landscape //обрыв   //создает экземпляр, имеет тот же интерфейс
{
private:
    Cliff* _landscape;

public:
    CliffProxy();
    ~CliffProxy();

    std::string symb();

    IStrategy* action();

    Cliff* getCliff();
};
