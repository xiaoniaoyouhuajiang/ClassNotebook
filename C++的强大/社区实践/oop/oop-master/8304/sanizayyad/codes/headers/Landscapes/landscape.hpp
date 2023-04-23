#ifndef landscape_hpp
#define landscape_hpp

#include "unit.hpp"
#include "drawingInterface.hpp"

#include <stdio.h>

class Landscape: public DrawingInterface
{
public:
    virtual ~Landscape() = default;

    virtual void hurtUnit(std::shared_ptr<unit::Unit> unit) const = 0;
    virtual bool canMove(std::shared_ptr<unit::Unit> unit) const = 0;
    virtual std::shared_ptr<Landscape> clone() const = 0;
};

#endif /* landscape_hpp */
