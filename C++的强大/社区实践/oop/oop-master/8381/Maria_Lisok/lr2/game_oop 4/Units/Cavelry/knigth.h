#ifndef KNIGTH_H
#define KNIGTH_H
#include "cavelry.h"
class Knigth: public Cavelry{
public:
    Knigth();
    string getName();
    Unit* copyItem();
};

#endif // KNIGTH_H
