
#ifndef shortRangeUnit_hpp
#define shortRangeUnit_hpp

#include "unit.hpp"

#include <stdio.h>

class ShortRangeUnit : public Unit
{
public:
    explicit ShortRangeUnit(const Position2D& position,std::shared_ptr<Mediator> mediator);
    virtual ~ShortRangeUnit() = default;

    ShortRangeUnit(const ShortRangeUnit& unit);

    virtual bool moveLeft() override;
    virtual bool moveRight() override;
    virtual bool moveTop() override;
    virtual bool moveBottom() override;
};
#endif /* ShortRangeUnit_hpp */
