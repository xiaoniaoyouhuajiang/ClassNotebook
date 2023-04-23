//
// Created by Artem Butko on 21.05.2020.
//

#ifndef OOP_NEW_ADAPTER_H
#define OOP_NEW_ADAPTER_H

#include <string>
#include <sstream>
#include "../../../Objects/Object.h"
#include "../../../Objects/Base/Base.h"

/*
 * Adapter -- класс, который реализует паттерн "Адаптер".
 */

class Adapter
{
public:
    static std::string createBase(Base* base);
    static std::string createUnit(char id);
    static std::string getUnit(Object* unit, int x, int y);
    static std::string moveUnit(Object* unit, int x, int y, int i, int j);
    static std::string attackUnit(Object* unit, int x, int y, int i, int j);
};


#endif //OOP_NEW_ADAPTER_H
