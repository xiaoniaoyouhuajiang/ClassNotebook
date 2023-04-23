//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_CREATEBASELINK_H
#define OOP_NEW_CREATEBASELINK_H


#include "../Chain.h"

/*
 * CreateBaseLink -- класс-звено цепи для создания базы.
 */

class CreateBaseLink : public Chain
{
public:
    CreateBaseLink(Field* field) : Chain(field) {};
    void chain(std::string command, std::string player) override;
};


#endif //OOP_NEW_CREATEBASELINK_H
