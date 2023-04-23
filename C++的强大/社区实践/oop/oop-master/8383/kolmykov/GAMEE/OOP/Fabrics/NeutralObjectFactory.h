#ifndef NEUTRALOBJECTFACTORY_H
#define NEUTRALOBJECTFACTORY_H


#include "NeutralObject.h"
#include "LargeArmorObject.h"
#include "SmallArmorObject.h"
#include "LargeMedicine.h"
#include "SmallMedicine.h"


class NeutralObjectFactory
{
public:
    NeutralObjectFactory();
    std::shared_ptr<NeutralObject> create();
};

#endif // NEUTRALOBJECTFACTORY_H
