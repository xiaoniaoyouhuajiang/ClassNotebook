#ifndef BOMBOBJECT_H
#define BOMBOBJECT_H

#include "neutralobject.h"


class BombObject : public NeutralObject
{
public:
    BombObject() = default;
    BombObject(const BombObject& object);
    BombObject& operator=(const BombObject& object);

    virtual std::shared_ptr<NeutralObject> clone() const override;

    virtual char draw() const override;

protected:
    virtual void selectStrategy(std::shared_ptr<unit::Unit> unit) override;
};

#endif // BOMBOBJECT_H
