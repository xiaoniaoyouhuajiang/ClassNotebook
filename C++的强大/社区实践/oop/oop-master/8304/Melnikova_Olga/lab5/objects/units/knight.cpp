#include "knight.h"

Knight::Knight(bool numbase)
{
   // health = LIGHT_HEALTH;
    attackRadius = LIGHT_RADIUS;
    movementRadius = LIGHT_RADIUS;
    damage = DAMAGE;
    if(numbase == 0){ symb = ":/pics/knight1.jpg";
    }else if(numbase == 1){ symb = ":/pics/knight2.jpg";}
}
