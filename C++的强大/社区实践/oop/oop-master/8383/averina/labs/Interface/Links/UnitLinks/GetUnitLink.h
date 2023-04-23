//
// Created by olyaave on 01.06.2020.
//

#ifndef OOP_GETUNITLINK_H
#define OOP_GETUNITLINK_H

#include "../Chain.h"

/*
 * GetUnitLink -- класс-звено цепи для получения юнита на поле.
 */

class GetUnitLink : public Chain
{
public:
    GetUnitLink(Field* field) : Chain(field) {};
    void chain(std::string command, std::string player) override;
};



#endif //OOP_GETUNITLINK_H
