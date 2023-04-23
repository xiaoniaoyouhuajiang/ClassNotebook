#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "NeutralObject/armorobject.h"
#include "NeutralObject/bombobject.h"
#include "NeutralObject/noobject.h"
#include "NeutralObject/healerobject.h"


class ObjectFactory
{
public:
    virtual ~ObjectFactory() = default;

    virtual std::shared_ptr<NeutralObject> createObject() const = 0;
};

#endif // OBJECTFACTORY_H
