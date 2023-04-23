//

//

#include "Field.h"

void Field::getEffect(Object *object_)
{
    if (object_->id_ == 'A' || object_->id_ == 'C')
    {
        object_->armor.set(10, true);
        object_->health.actDamaged(15);
    }
    else if (object_->id_ == 'M' || object_->id_ == 'W')
    {
        object_->armor.set(0, false);
        object_->health.actDamaged(10);
    }
    else
    {
        object_->armor.set(50, true);
        object_->health.actHealed(20);
    }
}

char Field::getID() {
    return this->id_;
}
