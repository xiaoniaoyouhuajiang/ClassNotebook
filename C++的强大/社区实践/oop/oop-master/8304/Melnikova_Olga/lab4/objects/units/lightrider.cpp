#include "lightrider.h"

LightRider::LightRider(bool numbase)
{
    //health = MEDIUM_HEALTH;
    attackRadius = MEDIUM_RADIUS;
    movementRadius = HEAVY_RADIUS;
    damage = DAMAGE;
    if(numbase == 0){ symb = ":/pics/lidht_rider1.jpg";
    }else if(numbase == 1){ symb = ":/pics/light_rider2.jpg";}
}
