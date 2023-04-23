#ifndef ROADLANDSCAPE_H
#define ROADLANDSCAPE_H

#include "landscape.h"


class RoadLandscape : public Landscape
{
public:
    virtual void hurtUnit(std::shared_ptr<unit::Unit> unit) const override;
    virtual bool canMove(std::shared_ptr<unit::Unit> unit) const override;
    virtual std::shared_ptr<Landscape> clone() const override;

    virtual char draw() const override;
};

#endif // ROADLANDSCAPE_H
