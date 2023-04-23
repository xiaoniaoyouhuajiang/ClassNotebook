//

//

#include "HolyUp.h"

void HolyUp::unitImpact(Unit *unit_)
{
    unit_->regeneration(100);
    unit_->armor.set(150, true);
}
