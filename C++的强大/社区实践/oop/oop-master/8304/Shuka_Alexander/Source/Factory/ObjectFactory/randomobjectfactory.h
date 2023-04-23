#ifndef RANDOMOBJECTFACTORY_H
#define RANDOMOBJECTFACTORY_H

#include <random>
#include <time.h>

#include "objectfactory.h"


class RandomObjectFactory : public ObjectFactory
{
public:
    virtual std::shared_ptr<NeutralObject> createObject() const override;
};

#endif // RANDOMOBJECTFACTORY_H
