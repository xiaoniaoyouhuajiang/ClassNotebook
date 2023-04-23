#ifndef OOP_MOVEUNITLINK_H
#define OOP_MOVEUNITLINK_H

#include "../Chain.h"

/*
 * MoveUnitLink -- класс-звено цепи для передвижения юнита.
 */


class MoveUnitLink : public Chain
{
public:
    MoveUnitLink(Field* field) : Chain(field) {};
    void chain(std::string command, std::string player) override;
};


#endif //OOP_MOVEUNITLINK_H
