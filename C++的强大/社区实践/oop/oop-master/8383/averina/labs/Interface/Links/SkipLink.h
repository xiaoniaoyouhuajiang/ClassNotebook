//
// Created by olyaave on 20.05.2020.
//

#ifndef OOP_SKIPLINK_H
#define OOP_SKIPLINK_H

#include "Chain.h"

class SkipLink : public Chain
{
public:
    SkipLink(Field* field) : Chain(field) {};
    void chain(std::string command, std::string player) override;
};



#endif //OOP_SKIPLINK_H
