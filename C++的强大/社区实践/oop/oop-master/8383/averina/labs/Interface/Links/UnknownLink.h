#ifndef OOP_UNKNOWNLINK_H
#define OOP_UNKNOWNLINK_H

#include "Chain.h"

/*
 * UnknownLink -- класс-звено цепи для неизвестной комманды.
 */

class UnknownLink : public Chain
{
public:
    UnknownLink(Field* field) : Chain(field) {};
    void chain(std::string command, std::string player) override;
};


#endif //OOP_UNKNOWNLINK_H
