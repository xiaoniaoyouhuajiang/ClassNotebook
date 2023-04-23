#ifndef neutralobject_hpp
#define neutralobject_hpp

#include "swordman.hpp"
#include "spearman.hpp"
#include "archer.hpp"
#include "dragon.hpp"

#include "swordManArmorUpdateLogic.hpp"
#include "spearManArmorUpdateLogic.hpp"
#include "archerArmorUpdateLogic.hpp"
#include "dragonArmorUpdateLogic.hpp"
#include "drawingInterface.hpp"


#include "healthupdatelogic.hpp"
#include "poisonlogic.hpp"
#include "nologic.hpp"

#include <stdio.h>


class NeutralObject: public DrawingInterface
{
public:
    explicit NeutralObject() = default;
    virtual ~NeutralObject() = default;

    virtual void operator[](std::shared_ptr<unit::Unit> unit);
    
    virtual std::shared_ptr<NeutralObject> clone() const = 0;

protected:
    virtual void selectLogic(std::shared_ptr<unit::Unit> unit) = 0;

protected:
    std::shared_ptr<StrategyPattern> strategyPattern;
};


#endif /* neutralobject_hpp */
