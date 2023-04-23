#include "randomobjectfactory.h"


std::shared_ptr<NeutralObject> RandomObjectFactory::createObject() const
{
    srand(time(0));
    int randomNumber = rand() % 3;
    std::shared_ptr<NeutralObject> object;

    switch (randomNumber) {
    case 0:
        object = std::make_shared<BombObject>();
        break;
    case 1:
        object = std::make_shared<HealerObject>();
        break;
    case 2:
        object = std::make_shared<ArmorObject>();
        break;
    default:
        object = std::make_shared<NoObject>();
        break;
    }

    return object;
}
