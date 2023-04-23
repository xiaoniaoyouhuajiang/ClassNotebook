#pragma once
#include "landscapes/landscape.h"
#include "landscapes/cliff.h"
#include "landscapes/swamp.h"
#include "landscapes/glade.h"
#include "typeinfo"

constexpr int NO_DAMAGE = 1;
constexpr int MEDIUM_DAMAGE = 2;
constexpr int HEAVY_DAMAGE = 3;

class Damage
{
public:
    int _damage;
    Damage(Landscape* obj);

};
