#ifndef TOWERSETTINGSTATE_H
#define TOWERSETTINGSTATE_H


#include "state.h"
#include "Kind.h"
#include "BitingZombyFactory.h"
#include "StinkyZombyFactory.h"
#include "StrongZombyFactory.h"
#include "KamikadzeZombyFactory.h"
#include "SpitToEnemyZombyFactory.h"
#include "SpitToAreaZombyFactory.h"
#include "HumanWithBatFactory.h"
#include "HumanOnBikeFactory.h"
#include "HumanOnCarFactory.h"
#include "HumanWithGrenadeFactory.h"
#include "HumanWithGunFactory.h"
#include "HumanWithSwordFactory.h"


class TowerSettingState : public State
{
public:
    TowerSettingState(Kind kind, int num, std::shared_ptr<Field> field, std::shared_ptr<Facade> facade);
    ~TowerSettingState();
    void create(int xT, int xU, UnitType type);
    void endStep();
};

#endif // TOWERSETTINGSTATE_H
