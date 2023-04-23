#ifndef armorobject_hpp
#define armorobject_hpp

#include "neutralobject.hpp"

#include <stdio.h>

class ArmorObject : public NeutralObject
{
public:
    ArmorObject() = default;
    ArmorObject(const ArmorObject& object);
    ArmorObject& operator=(const ArmorObject& object);
    
    virtual std::shared_ptr<NeutralObject> clone() const override;
    virtual char draw() const override;


protected:
    virtual void selectLogic(std::shared_ptr<unit::Unit> unit) override;
};

#endif /* armorobject_hpp */
