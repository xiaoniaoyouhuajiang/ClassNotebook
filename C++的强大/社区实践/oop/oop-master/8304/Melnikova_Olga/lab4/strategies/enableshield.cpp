#include "enableshield.h"


EnableShield::~EnableShield()
{

}

void EnableShield::interact(Unit *unit) {
    unit->shieldEnabled = true;
}
