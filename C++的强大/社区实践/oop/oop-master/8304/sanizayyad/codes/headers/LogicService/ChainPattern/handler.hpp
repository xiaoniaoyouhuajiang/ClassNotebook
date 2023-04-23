#ifndef handler_hpp
#define handler_hpp

#include <stdio.h>
#include "attackcommand.hpp"
#include "moveunitcommand.hpp"
#include "createunitcommand.hpp"


class Handler
{
public:
    virtual std::shared_ptr<Handler> SetNext(std::shared_ptr<Handler> handler) = 0;
    virtual std::shared_ptr<Unit> CreateUnit(std::shared_ptr<Base> homeBase,std::shared_ptr<Base> enemyBase,std::string type) = 0;
    virtual bool Attack(std::shared_ptr<BattleField> battleField,std::shared_ptr<Unit> unit, std::shared_ptr<Adapter> log) = 0;
    virtual bool MoveUnit(std::shared_ptr<Base> enemyBase,std::shared_ptr<Unit> unit) = 0;
    
};
#endif /* handler_hpp */
