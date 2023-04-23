#pragma once

#include "objects/base.h"
#include "objects/units/unit.h"

#include <typeinfo>
#include "objects/object.h"
#include "objects/units/archer.h"
#include "objects/units/crossbowman.h"
#include "objects/units/heavyrider.h"
#include "objects/units/lightrider.h"
#include "objects/units/knight.h"
#include "objects/units/spearman.h"

constexpr int LIGHT_HEALTH = 1;
constexpr int MEDIUM_HEALTH = 2;
constexpr int HEAVY_HEALTH = 3;

class Health
{
public:
    int _health;
    Health(Object* obj);
};

