#ifndef SPIKESLANDSCAPES_H
#define SPIKESLANDSCAPES_H

#include "landscape.h"


class SpikesLandscape : public Landscape
{
public:
    virtual void hurtUnit(std::shared_ptr<unit::Unit> unit) const override;
    virtual bool canMove(std::shared_ptr<unit::Unit> unit) const override;
    virtual std::shared_ptr<Landscape> clone() const override;

    virtual char draw() const override;
};

#endif // SPIKESLANDSCAPES_H
