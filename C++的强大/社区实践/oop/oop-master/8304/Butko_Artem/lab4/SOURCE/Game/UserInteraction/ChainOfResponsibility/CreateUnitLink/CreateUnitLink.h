//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_CREATEUNITLINK_H
#define OOP_NEW_CREATEUNITLINK_H


#include "../Chain.h"

/*
 * CreateUnitLink -- класс-звено цепи для создания юнита.
 */

class CreateUnitLink : public Chain
{
public:
    CreateUnitLink(Field* field) : Chain(field) {};
    virtual void chain(std::string command) override;
};


#endif //OOP_NEW_CREATEUNITLINK_H
