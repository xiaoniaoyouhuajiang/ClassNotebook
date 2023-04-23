#ifndef swordman_hpp
#define swordman_hpp

#include "shortrangeunit.hpp"

#include <stdio.h>

class SwordMan : public ShortRangeUnit
{
public:
    explicit SwordMan(const Position2D& position,std::shared_ptr<Mediator> mediator);
    virtual ~SwordMan() = default;

    SwordMan(const SwordMan& unit);
    SwordMan(SwordMan&& unit) = delete;
    SwordMan& operator=(const SwordMan& unit);
    SwordMan& operator=(SwordMan&& unit) = delete;
        

    virtual std::shared_ptr<Unit> clone() override;
};

#endif /* swordman_hpp */
