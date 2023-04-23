#ifndef desert_hpp
#define desert_hpp

#include "landscape.hpp"

#include <stdio.h>


class DesertLandscape : public Landscape
{
public:
    virtual void hurtUnit(std::shared_ptr<unit::Unit> unit) const override;
    virtual bool canMove(std::shared_ptr<unit::Unit> unit) const override;
    virtual std::shared_ptr<Landscape> clone() const override;

    virtual char draw() const override;
};
#endif /* desert_hpp */
