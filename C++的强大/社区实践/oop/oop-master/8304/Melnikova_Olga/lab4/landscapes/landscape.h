#pragma once

#include <string>
#include "strategies/istrategy.h"

class Landscape
{
public:
    Landscape();
    ~Landscape();

    std::string symb;
    int damage;

    IStrategy* action;

};

