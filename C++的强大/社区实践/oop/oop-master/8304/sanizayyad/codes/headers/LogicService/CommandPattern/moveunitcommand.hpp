
#ifndef moveunitcommand_hpp
#define moveunitcommand_hpp

#include "command.hpp"

class MoveUnitCommand : public Command
{
public:
    MoveUnitCommand(std::shared_ptr<unit::Base> enemyBase,std::shared_ptr<unit::Unit> unit){
        this->enemyBase = enemyBase;
        this->unit = unit;

    };
    void moveUnit()
    {
        auto enemyBasePosition = enemyBase->getPosition();
        auto unitPosition = unit->getPosition();

        if (unitPosition.x < enemyBasePosition.x) {
            unit->moveRight();
        }
        else {
            unit->moveLeft();
        }

       
        if (unitPosition.y < enemyBasePosition.y) {
            unit->moveBottom();
        }
        else if (unitPosition.y > enemyBasePosition.y) {
            unit->moveTop();
        }
    }

    void Execute() override {
        moveUnit();
    }
private:
    std::shared_ptr<unit::Base> enemyBase;
    std::shared_ptr<unit::Unit> unit;
};
#endif /* moveunitcommand_hpp */
