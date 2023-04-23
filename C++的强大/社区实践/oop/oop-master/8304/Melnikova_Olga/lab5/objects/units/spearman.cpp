#include "spearman.h"

SpearMan::SpearMan(bool numbase)
{
    //health = LIGHT_HEALTH;
    attackRadius = LIGHT_RADIUS;
    movementRadius = LIGHT_RADIUS;
    damage = DAMAGE;
    if(numbase == 0){ symb = ":/pics/SpearMan1.jpg";
    }else if(numbase == 1){ symb = ":/pics/SpearMan2.jpg";}
}
