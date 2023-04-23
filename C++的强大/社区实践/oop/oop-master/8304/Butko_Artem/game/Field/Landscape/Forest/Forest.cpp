//

//

#include "Forest.h"

void Forest::getEffect(Object *object_) {
    if (object_->id_ == 'A' || object_->id_ == 'C')
    {
        object_->armor.set(0, false);
        object_->health.actDamaged(15);
    }
    else if (object_->id_ == 'M' || object_->id_ == 'W')
    {
        object_->health.actHealed(20);
    }
    else
    {
        object_->armor.set(300, true);
    }
}

char Forest::getID()
{
    return this->id_;
}
