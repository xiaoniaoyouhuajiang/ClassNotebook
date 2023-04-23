#include "archer.h"

Archer::Archer(bool numbase)
{
    //health = LIGHT_HEALTH;
    attackRadius = HEAVY_RADIUS;
    movementRadius = LIGHT_RADIUS;
    if(numbase == 0){ symb = ":/pics/lychnik1.jpg";
    }else if(numbase == 1){ symb = ":/pics/lychnik2.jpg";}
    this->notify("Base created");
}
