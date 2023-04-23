//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_UNKNOWNLINK_H
#define OOP_NEW_UNKNOWNLINK_H

#include "../Chain.h"

/*
 * UnknownLink -- класс-звено цепи для неизвестной комманды.
 */

class UnknownLink : public Chain
{
public:
    UnknownLink(Field* field) : Chain(field) {};
    void chain(std::string command) override;
};


#endif //OOP_NEW_UNKNOWNLINK_H
