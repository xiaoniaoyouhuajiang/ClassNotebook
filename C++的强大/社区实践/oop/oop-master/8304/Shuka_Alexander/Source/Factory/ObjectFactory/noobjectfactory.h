#ifndef NOOBJECTFACTORY_H
#define NOOBJECTFACTORY_H

#include "objectfactory.h"


class NoObjectFactory : public ObjectFactory
{
public:
    virtual std::shared_ptr<NeutralObject> createObject() const override;
};

#endif // NOOBJECTFACTORY_H
