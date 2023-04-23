#ifndef UNITDIRECTOR_H
#define UNITDIRECTOR_H

#include <climits>

#include "unitbuilder.h"

#include "Factory/ArmorFactory/heavyarmorfactory.h"
#include "Factory/ArmorFactory/lightarmorfactory.h"
#include "Factory/ArmorFactory/noarmorfactory.h"
#include "Factory/ArmorFactory/mediumarmorfactory.h"

#include "Factory/UnitFactory/dragonfactory.h"
#include "Factory/UnitFactory/kamikadzefactory.h"
#include "Factory/UnitFactory/warriorfactory.h"
#include "Factory/UnitFactory/towerfactory.h"
#include "Factory/UnitFactory/goldminerfactory.h"
#include "Factory/UnitFactory/thieffactory.h"

#include "Factory/WeaponFactory/bowweaponfactory.h"
#include "Factory/WeaponFactory/magicweaponfactory.h"
#include "Factory/WeaponFactory/noweaponfactory.h"
#include "Factory/WeaponFactory/swordweaponfactory.h"


namespace unit {
class UnitDirector
{
public:
    std::shared_ptr<Unit> createDragon(const Point2D& point,
                                       std::shared_ptr<Mediator> mediator,
                                       double healthPoints = __DBL_MIN__);
    std::shared_ptr<Unit> createThief(const Point2D& point,
                                      std::shared_ptr<Mediator> mediator,
                                      double healthPoints = __DBL_MIN__);
    std::shared_ptr<Unit> createWarrior(const Point2D& point,
                                        std::shared_ptr<Mediator> mediator,
                                        double healthPoints = __DBL_MIN__);
    std::shared_ptr<Unit> createTower(const Point2D& point,
                                      std::shared_ptr<Mediator> mediator,
                                      double healthPoints = __DBL_MIN__);
    std::shared_ptr<Unit> createKamikadze(const Point2D& point,
                                          std::shared_ptr<Mediator> mediator,
                                          double healthPoints = __DBL_MIN__);
    std::shared_ptr<Unit> createGoldMiner(const Point2D& point,
                                          std::shared_ptr<Mediator> mediator,
                                          double healthPoints = __DBL_MIN__);

};
}

#endif // UNITDIRECTOR_H
