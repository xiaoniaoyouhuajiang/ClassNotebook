#ifndef HANDLERREGISTRY_H
#define HANDLERREGISTRY_H

#include <map>
#include "ihandler.h"
#include "derivedhandlers.h"
class HandlerRegistry
{
private:
    std::map<std::string,Unit*> handlers;
    static HandlerRegistry *instance;
    HandlerRegistry();
public:
    static const std::size_t TYPE_SUM = 0;
    static const std::size_t TYPE_DISTRIBUTE = 1;
    static const std::size_t TYPE_SQUARED = 2;
    static const std::size_t TYPE_DIV_MOD = 3;
    static const std::size_t TYPE_ROUND2 = 4;
    static const std::size_t TYPE_DISTANCE = 5;
    static const std::size_t TYPE_COOR_MAKING = 6;
    static const std::size_t TYPE_COOR_BREAKUP = 7;
    static const std::size_t TYPE_ROUND1 = 8;
    static const std::size_t TYPE_DISTRIBUTE_D = 9;
    static HandlerRegistry& getInstance(){
        if(instance==nullptr) instance = new HandlerRegistry;
        return *instance;
    }
    Unit* getByTypeId(std::size_t type);
    std::string getTypeDescription(std::size_t type);
};

#endif // HANDLERREGISTRY_H
