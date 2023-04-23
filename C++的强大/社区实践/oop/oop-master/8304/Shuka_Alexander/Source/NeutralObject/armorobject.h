#ifndef ARMOROBJECT_H
#define ARMOROBJECT_H

#include "neutralobject.h"


class ArmorObject : public NeutralObject
{
public:
    ArmorObject() = default;
    ArmorObject(const ArmorObject& object);
    ArmorObject& operator=(const ArmorObject& object);

    virtual std::shared_ptr<NeutralObject> clone() const override;

    virtual char draw() const override;

protected:
    virtual void selectStrategy(std::shared_ptr<unit::Unit> unit) override;
};

#endif // ARMOROBJECT_H
