#pragma once
#include "landscape.h"
#include "glade.h"

class GladeProxy : public Landscape
{
private:
    Glade* _landscape;

public:
    GladeProxy();
    ~GladeProxy();

    std::string symb();

    IStrategy* action();

    Glade* getGlade();
};
