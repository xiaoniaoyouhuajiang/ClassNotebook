#ifndef movehandler_hpp
#define movehandler_hpp

#include <stdio.h>
#include "abstracthandler.hpp"

class MoveUnitHandler : public AbstractHandler
{
public:
    MoveUnitHandler();
                  
    bool MoveUnit(std::shared_ptr<Base> enemyBase,std::shared_ptr<Unit> unit) override {
     MoveUnitCommand* command = new MoveUnitCommand(enemyBase, unit);
     command->Execute();
    return true;
    }
};

#endif /* movehandler_hpp */
