#pragma once

#include "landscape.h"
#include "swamp.h"

class SwampProxy : public Landscape //болото
{
private:
    Swamp* _landscape;

public:
    SwampProxy();
    ~SwampProxy();

    std::string symb();

    IStrategy* action();

    Swamp* getSwamp();
};
