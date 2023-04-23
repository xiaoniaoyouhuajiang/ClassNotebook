#ifndef vampire_hpp
#define vampire_hpp

#include "dynamicrangeunit.hpp"

#include <stdio.h>

class Vampire : public DynamicRangeUnit
{
public:
    explicit Vampire(const Position2D& position,std::shared_ptr<Mediator> mediator);
    virtual ~Vampire() = default;

    Vampire(const Vampire& unit);
    Vampire(Vampire&& unit) = delete;
    Vampire& operator=(const Vampire& unit);
    Vampire& operator=(Vampire&& unit) = delete;


    virtual std::shared_ptr<Unit> clone() override;
};

#endif /* vampire_hpp */
