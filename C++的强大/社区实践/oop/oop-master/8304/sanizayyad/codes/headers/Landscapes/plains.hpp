#ifndef plains_hpp
#define plains_hpp

#include "landscape.hpp"

#include <stdio.h>


class PlainsLandscape : public Landscape
{
public:
    virtual void hurtUnit(std::shared_ptr<unit::Unit> unit) const override;
    virtual bool canMove(std::shared_ptr<unit::Unit> unit) const override;
    virtual std::shared_ptr<Landscape> clone() const override;

    virtual char draw() const override;
};

#endif /* plains_hpp */
