#ifndef unitcreator_hpp
#define unitcreator_hpp

#include "unitfactory.hpp"
#include "unitbuilder.hpp"

#include "swordmanfactory.hpp"
#include "spearmanfactory.hpp"
#include "archerfactory.hpp"
#include "ballisticfactory.hpp"
#include "vampirefactory.hpp"
#include "dragonfactory.hpp"

#include "noarmorfactory.hpp"
#include "lightarmorfactory.hpp"
#include "mediumarmorfactory.hpp"
#include "heavyarmorfactory.hpp"

#include "swordweaponfactory.hpp"
#include "spearweaponfactory.hpp"
#include "arrowweaponfactory.hpp"
#include "ballisticweaponfactory.hpp"
#include "vampireteethweaponfactory.hpp"
#include "dragonfireweaponfactory.hpp"


#include <stdio.h>
#include <memory>


class UnitCreator
{
public:
    std::shared_ptr<Unit> createSwordMan(const Position2D& Position,std::shared_ptr<Mediator> mediator);
    std::shared_ptr<Unit> createSpearMan(const Position2D& Position,std::shared_ptr<Mediator> mediator);
    std::shared_ptr<Unit> createArcher(const Position2D& Position,std::shared_ptr<Mediator> mediator);
    std::shared_ptr<Unit> createBallistic(const Position2D& Position,std::shared_ptr<Mediator> mediator);
    std::shared_ptr<Unit> createVampire(const Position2D& Position,std::shared_ptr<Mediator> mediator);
    std::shared_ptr<Unit> createDragon(const Position2D& Position,std::shared_ptr<Mediator> mediator);

};

#endif /* unitcreator_hpp */
