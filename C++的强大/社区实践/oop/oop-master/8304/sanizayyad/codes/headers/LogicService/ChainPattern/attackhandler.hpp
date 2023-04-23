#ifndef attackhandler_hpp
#define attackhandler_hpp

#include "abstracthandler.hpp"
#include "attackcommand.hpp"

class AttackHandler : public AbstractHandler
{
public:
    AttackHandler(){
    };

    bool Attack(std::shared_ptr<BattleField> battleField,std::shared_ptr<Unit> unit, std::shared_ptr<Adapter> log) override {
        
            AttackCommand* command = new AttackCommand(battleField, unit,log);
            command->Execute();
        if( command->getExecution())
            return true;
        return false;
    }
    
};
#endif /* attackhandler_hpp */
