#ifndef poisonobject_hpp
#define poisonobject_hpp

#include "neutralobject.hpp"

#include <stdio.h>

class PoisonObject : public NeutralObject
{
public:
    PoisonObject() = default;
    PoisonObject(const PoisonObject& object);
    PoisonObject& operator=(const PoisonObject& object);

    virtual std::shared_ptr<NeutralObject> clone() const  override;
    virtual char draw() const override;

protected:
    virtual void selectLogic(std::shared_ptr<unit::Unit> unit) override;
};
#endif /* poisonobject_hpp */
