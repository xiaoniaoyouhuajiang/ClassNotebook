#include "heavyrider.h"

HeavyRider::HeavyRider(bool numbase)
{
   // health = MEDIUM_HEALTH;
    attackRadius = MEDIUM_RADIUS;
    movementRadius = HEAVY_RADIUS;
    damage = DAMAGE;
    if(numbase == 0){ symb = ":/pics/rider1.jpg";
    }else if(numbase == 1){ symb = ":/pics/rider2.jpg";}
}
