#include "swamp.h"


Swamp::Swamp()
{
    symb = ":/pics/swamp.jpg";
    isSwamp = true;
    action = new HealthDecrease();
}
