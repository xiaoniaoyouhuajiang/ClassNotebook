#ifndef healthobject_hpp
#define healthobject_hpp

#include "neutralobject.hpp"

#include <stdio.h>

class HealthObject : public NeutralObject
{
public:
    HealthObject() = default;
    HealthObject(const HealthObject& object);
    HealthObject& operator=(const HealthObject& object);

    virtual std::shared_ptr<NeutralObject> clone() const override;
    virtual char draw() const override;

protected:
    virtual void selectLogic(std::shared_ptr<unit::Unit> unit) override;
};
#endif /* healthobject_hpp */
