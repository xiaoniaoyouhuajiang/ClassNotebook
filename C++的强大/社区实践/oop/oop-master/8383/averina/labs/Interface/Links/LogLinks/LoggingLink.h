
#ifndef OOP_LOGGINGLINK_H
#define OOP_LOGGINGLINK_H

#include "../Chain.h"

class LoggingLink : public Chain
{
public:
    LoggingLink(Field* field) : Chain(field) {};
    void chain(std::string command, std::string player) override;
};



#endif //OOP_LOGGINGLINK_H
