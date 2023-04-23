#ifndef LAB2_COMMAND_H
#define LAB2_COMMAND_H

#include "Boardfield.h"

class Command {
public:
    virtual void execute() const = 0;
};


#endif
