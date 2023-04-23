#ifndef range_hpp
#define range_hpp

#include "unit.hpp"

#include <stdio.h>

class LongRangeUnit : public Unit
{
public:
    explicit LongRangeUnit(const Position2D& Position2D,std::shared_ptr<Mediator> mediator);
    virtual ~LongRangeUnit() = default;

    LongRangeUnit(const LongRangeUnit& unit);

    virtual bool moveLeft() override;
    virtual bool moveRight() override;
    virtual bool moveTop() override;
    virtual bool moveBottom() override;
};

#endif /* range_hpp */
