#pragma once
#include "melee_unit.h"
#include "range_unit.h"
#include "vehicle_unit.h"

enum Units_ID_list {knight, rogue, archer, mage, siege_tower, catapult};

std::shared_ptr<Unit> create_unit(size_t unit_ID);