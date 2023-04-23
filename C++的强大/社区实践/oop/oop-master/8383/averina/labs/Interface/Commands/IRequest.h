#ifndef OOP_IREQUEST_H
#define OOP_IREQUEST_H

#include "../../Field/Field.h"


class IRequest
{
public:
    virtual void Command() = 0;

protected:
    IRequest(Field* Field) : field(Field) {};
    Field* field;
    std::string player;
};




#endif //OOP_IREQUEST_H
