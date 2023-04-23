#ifndef Archer_hpp
#define Archer_hpp

#include "longrangeunit.hpp"

#include <stdio.h>

class Archer : public LongRangeUnit
{
public:
    explicit Archer(const Position2D& position,std::shared_ptr<Mediator> mediator);
    virtual ~Archer() = default;

    Archer(const Archer& unit);
    Archer(Archer&& unit) = delete;
    Archer& operator=(const Archer& unit);
    Archer& operator=(Archer&& unit) = delete;


    virtual std::shared_ptr<Unit> clone() override;
};
#endif /* Archer_hpp */
