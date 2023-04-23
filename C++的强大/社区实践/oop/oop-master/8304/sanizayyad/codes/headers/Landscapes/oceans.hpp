#ifndef oceans_hpp
#define oceans_hpp

#include "landscape.hpp"

#include <stdio.h>


class OceansLandscape : public Landscape
{
public:
    virtual void hurtUnit(std::shared_ptr<unit::Unit> unit) const override;
    virtual bool canMove(std::shared_ptr<unit::Unit> unit) const override;
    virtual std::shared_ptr<Landscape> clone() const override;

    virtual char draw() const override;
};
#endif /* oceans_hpp */
