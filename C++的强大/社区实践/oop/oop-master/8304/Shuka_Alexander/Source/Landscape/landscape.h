#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "Unit/unit.h"
#include "idrawable.h"


class Landscape : public IDrawable
{
public:
    virtual ~Landscape() = default;

    virtual void hurtUnit(std::shared_ptr<unit::Unit> unit) const = 0;
    virtual bool canMove(std::shared_ptr<unit::Unit> unit) const = 0;
    virtual std::shared_ptr<Landscape> clone() const = 0;
};

#endif // LANDSCAPE_H
