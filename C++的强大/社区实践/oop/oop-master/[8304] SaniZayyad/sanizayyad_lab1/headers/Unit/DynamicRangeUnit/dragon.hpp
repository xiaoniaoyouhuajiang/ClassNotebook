
#ifndef dragon_hpp
#define dragon_hpp

#include "dynamicrangeunit.hpp"

#include <stdio.h>

class Dragon : public DynamicRangeUnit
{
public:
    explicit Dragon(const Position2D& position,std::shared_ptr<Mediator> mediator);
    virtual ~Dragon() = default;

    Dragon(const Dragon& unit);
    Dragon(Dragon&& unit) = delete;
    Dragon& operator=(const Dragon& unit);
    Dragon& operator=(Dragon&& unit) = delete;


    virtual std::shared_ptr<Unit> clone() override;
};

#endif /* dragon_hpp */
