//
// Created by Artem Butko on 21.05.2020.
//

#ifndef OOP_NEW_LOGGINGLINK_H
#define OOP_NEW_LOGGINGLINK_H


#include "../Chain.h"

class LoggingLink : public Chain
{
public:
    LoggingLink(Field* field) : Chain(field) {};
    void chain(std::string command) override;
};


#endif //OOP_NEW_LOGGINGLINK_H
