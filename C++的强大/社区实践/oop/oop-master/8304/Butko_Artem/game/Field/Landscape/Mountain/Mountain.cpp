//

//

#include "Mountain.h"


void Mountain::getEffect(Object *object_)
{
    if (object_->id_ == 'A' || object_->id_ == 'C')
    {
        object_->armor.set(40, true);
        object_->health.actHealed(20);
    }
    else if (object_->id_ == 'M' || object_->id_ == 'W')
    {
        object_->armor.set(20, true);
    }
    else
    {
        object_->armor.set(0, false);
        object_->health.actDamaged(15);
    }
}

char Mountain::getID()
{
    return this->id_;
}
