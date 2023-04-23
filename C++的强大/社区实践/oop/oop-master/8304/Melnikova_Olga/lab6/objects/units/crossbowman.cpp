#include "crossbowman.h"

CrossBowMan::CrossBowMan(bool numbase)
{
    //health = LIGHT_HEALTH;
    attackRadius = HEAVY_RADIUS;
    movementRadius = LIGHT_RADIUS;
    damage = DAMAGE;
    if(numbase == 0){ symb = ":/pics/crossBow1.jpg";
    }else if(numbase == 1){ symb = "::/pics/crossBow2.jpg";}
}
