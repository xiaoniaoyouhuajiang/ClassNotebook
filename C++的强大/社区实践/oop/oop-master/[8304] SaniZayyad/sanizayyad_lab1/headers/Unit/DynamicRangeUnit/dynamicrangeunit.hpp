#ifndef rare_hpp
#define rare_hpp

#include "unit.hpp"

#include <stdio.h>

class DynamicRangeUnit : public Unit
{
public:
    explicit DynamicRangeUnit(const Position2D& position,std::shared_ptr<Mediator> mediator);
    virtual ~DynamicRangeUnit() = default;

    DynamicRangeUnit(const DynamicRangeUnit& unit);

    virtual bool moveLeft() override;
    virtual bool moveRight() override;
    virtual bool moveTop() override;
    virtual bool moveBottom() override;
};

#endif /* rare_hpp */
