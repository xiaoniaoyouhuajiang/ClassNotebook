#include "noobjectfactory.h"


std::shared_ptr<NeutralObject> NoObjectFactory::createObject() const
{
    return std::make_shared<NoObject>();
}
