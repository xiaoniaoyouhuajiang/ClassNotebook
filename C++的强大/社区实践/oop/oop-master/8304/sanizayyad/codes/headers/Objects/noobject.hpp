#ifndef noobject_hpp
#define noobject_hpp

#include "neutralobject.hpp"

#include <stdio.h>

class NoObject : public NeutralObject
{
public:
    NoObject() = default;
    NoObject(const NoObject& object);
    NoObject& operator=(const NoObject& object);

    virtual std::shared_ptr<NeutralObject> clone() const override;
    virtual char draw() const override; 

protected:
    virtual void selectLogic(std::shared_ptr<unit::Unit> unit) override;
};
#endif /* noobject_hpp */
