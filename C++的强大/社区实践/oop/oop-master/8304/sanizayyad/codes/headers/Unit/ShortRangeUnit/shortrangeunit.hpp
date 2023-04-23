
#ifndef shortRangeUnit_hpp
#define shortRangeUnit_hpp

#include "unit.hpp"

#include <stdio.h>

namespace unit {
class ShortRangeUnit : public Unit,public std::enable_shared_from_this<Unit>
{
public:
    explicit ShortRangeUnit(const Position2D& position,std::shared_ptr<Mediator> mediator);
    virtual ~ShortRangeUnit() = default;

    ShortRangeUnit(const ShortRangeUnit& unit);

    virtual bool moveLeft() override;
    virtual bool moveRight() override;
    virtual bool moveTop() override;
    virtual bool moveBottom() override;
};}

#endif /* ShortRangeUnit_hpp */
