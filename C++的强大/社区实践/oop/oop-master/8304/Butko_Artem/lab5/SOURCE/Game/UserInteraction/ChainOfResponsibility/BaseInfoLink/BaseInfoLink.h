//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_BASEINFOLINK_H
#define OOP_NEW_BASEINFOLINK_H


#include "../Chain.h"

/*
 * BaseInfoLink -- класс-звено цепи для получения информации для базы.
 */

class BaseInfoLink : public Chain
{
public:
    BaseInfoLink(Field* field) : Chain(field) {};
    void chain(std::string command) override;
};


#endif //OOP_NEW_BASEINFOLINK_H
