//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_GETUNITLINK_H
#define OOP_NEW_GETUNITLINK_H


#include "../Chain.h"

/*
 * GetUnitLink -- класс-звено цепи для получения юнита на поле.
 */

class GetUnitLink : public Chain
{
public:
    GetUnitLink(Field* field) : Chain(field) {};
    void chain(std::string command) override;
};


#endif //OOP_NEW_GETUNITLINK_H
