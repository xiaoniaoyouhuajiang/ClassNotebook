
#ifndef OOP_CHAIN_H
#define OOP_CHAIN_H

#include <string>
#include "../../Field/Field.h"
#include "../../Exceptions/TypeError.h"
#include "../../Exceptions/OutofRangeError.h"
#include "../../Exceptions/LogicalError.h"

/*
 * Links -- класс для реализации паттерна "Цепочка обязанностей".
 */

class Chain
{
private:
    Chain* next;
protected:
    Chain(Field* field);
    Field* field;
public:
    Chain();
    void setNext(Chain* link);
    void addNext(Chain* link);
    virtual void chain(std::string command, std::string player);
};



#endif //OOP_CHAIN_H
