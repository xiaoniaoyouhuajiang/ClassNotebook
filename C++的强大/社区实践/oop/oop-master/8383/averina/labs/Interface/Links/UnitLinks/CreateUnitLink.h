#ifndef OOP_CREATEUNITLINK_H
#define OOP_CREATEUNITLINK_H


#include "../Chain.h"

/*
 * CreateUnitLink -- класс-звено цепи для создания юнита.
 */

class CreateUnitLink : public Chain
{
public:
    CreateUnitLink(Field* field) : Chain(field) {};
    virtual void chain(std::string command, std::string player) override;
};



#endif //OOP_CREATEUNITLINK_H
