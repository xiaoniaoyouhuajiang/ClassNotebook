#ifndef armorupdatelogic_hpp
#define armorupdatelogic_hpp

#include "strategy.hpp"
#include "lightarmorfactory.hpp"
#include "mediumarmorfactory.hpp"
#include "heavyarmorfactory.hpp"

#include <stdio.h>

class ArmorUpdateLogic : public StrategyPattern
{
public:
    explicit ArmorUpdateLogic() = default;
    virtual ~ArmorUpdateLogic() = default;

    ArmorUpdateLogic(const ArmorUpdateLogic& logic);
    ArmorUpdateLogic(ArmorUpdateLogic&& logic) = delete;
    ArmorUpdateLogic& operator=(const ArmorUpdateLogic& logic) = delete;
    ArmorUpdateLogic& operator=(ArmorUpdateLogic&& logic) = delete;

    virtual void updateUnit(std::shared_ptr<unit::Unit> unit) const override;

    
protected:
        std::unique_ptr<Armor> armor;
};
#endif /* armorupdatelogic_hpp */
