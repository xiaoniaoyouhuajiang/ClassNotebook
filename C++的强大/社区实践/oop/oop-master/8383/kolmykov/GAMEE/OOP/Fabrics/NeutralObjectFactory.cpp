#include "NeutralObjectFactory.h"

NeutralObjectFactory::NeutralObjectFactory()
{

}


std::shared_ptr<NeutralObject> NeutralObjectFactory::create() {
    int num = rand()% 6;

    if (num == 0) {
        return std::shared_ptr<NeutralObject>(new LargeMedicine);
    }
    else if (num == 1) {
        return std::shared_ptr<NeutralObject>(new LargeArmorObject);
    }
    else if (num < 4) {
        return std::shared_ptr<NeutralObject>(new SmallMedicine);
    }
    else {
        return std::shared_ptr<NeutralObject>(new SmallArmorObject);
    }
}
