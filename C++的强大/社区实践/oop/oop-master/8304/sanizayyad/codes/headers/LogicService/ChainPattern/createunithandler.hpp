#ifndef createunithandler_hpp
#define createunithandler_hpp

#include <stdio.h>
#include "abstracthandler.hpp"

class CreateUnitHandler : public AbstractHandler
{
public:
    CreateUnitHandler();
                  
    std::shared_ptr<Unit> CreateUnit(std::shared_ptr<Base> homeBase,std::shared_ptr<Base> enemyBase,std::string type) override {
     CreateUnitCommand* command = new CreateUnitCommand(homeBase, enemyBase,type);
     command->Execute();
    return command->getUnit();
    }
};

#endif /* createunithandler_hpp */
