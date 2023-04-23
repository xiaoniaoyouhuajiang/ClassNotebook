#ifndef ballistic_hpp
#define ballistic_hpp

#include "longrangeunit.hpp"

#include <stdio.h>

class Ballistic : public LongRangeUnit
{
public:
    explicit Ballistic(const Position2D& position,std::shared_ptr<Mediator> mediator);
    virtual ~Ballistic() = default;

    Ballistic(const Ballistic& unit);
    Ballistic(Ballistic&& unit) = delete;
    Ballistic& operator=(const Ballistic& unit);
    Ballistic& operator=(Ballistic&& unit) = delete;


    virtual std::shared_ptr<Unit> clone() override;
};

#endif /* ballistic_hpp */
