#ifndef spearman_hpp
#define spearman_hpp

#include "shortrangeunit.hpp"

#include <stdio.h>

class SpearMan : public ShortRangeUnit
{
public:
    explicit SpearMan(const Position2D& position,std::shared_ptr<Mediator> mediator);
    virtual ~SpearMan() = default;

    SpearMan(const SpearMan& unit);
    SpearMan(SpearMan&& unit) = delete;
    SpearMan& operator=(const SpearMan& unit);
    SpearMan& operator=(SpearMan&& unit) = delete;
//
    virtual std::shared_ptr<Unit> clone() override;
};

#endif /* spearman_hpp */
