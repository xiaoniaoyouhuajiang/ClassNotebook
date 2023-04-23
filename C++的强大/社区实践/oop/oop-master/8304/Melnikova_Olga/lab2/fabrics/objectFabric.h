#pragma once
#include "health.h"
#include "objects/object.h"
//#include "objects/base.h"
#include "objects/units/archer.h"
#include "objects/units/crossbowman.h"
#include "objects/units/heavyrider.h"
#include "objects/units/lightrider.h"
#include "objects/units/knight.h"
#include "objects/units/spearman.h"


//#include "neutralobject.h"
#include "objects/neutral_objects/powerup.h"
#include "objects/neutral_objects/shield.h"
#include "objects/neutral_objects/medicinechest.h"
#include "objects/neutral_objects/horse.h"
//#include "glade.h"

class Base;
class objectFabric {
public:
    Archer* createArcher();
    CrossBowMan* createCrossbowman();
    HeavyRider* createHeavyRider();
    LightRider* createLightRider();
    Knight* createKnight();
    SpearMan* createSpearman();
    Base* createBase(int x, int y, bool numbase);
    PowerUp* createTree();
    Shield* createChield();
    MedicineChest* createMedicineChest();
    Horse* createHorse();
};
