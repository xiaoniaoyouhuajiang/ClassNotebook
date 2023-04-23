#ifndef OOP_BASEINFOLINK_H
#define OOP_BASEINFOLINK_H

#include "../Chain.h"

/*
 * BaseInfoLink -- класс-звено цепи для получения информации для базы.
 */

class BaseInfoLink : public Chain
{
public:
    BaseInfoLink(Field* field) : Chain(field) {};
    void chain(std::string command, std::string player) override;
};



#endif //OOP_BASEINFOLINK_H
