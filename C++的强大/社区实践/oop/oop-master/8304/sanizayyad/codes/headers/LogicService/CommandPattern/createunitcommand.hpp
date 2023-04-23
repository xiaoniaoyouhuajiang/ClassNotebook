
#ifndef createunitcommand_hpp
#define createunitcommand_hpp

#include "command.hpp"

using namespace unit;
class CreateUnitCommand : public Command
{
    
public:
    CreateUnitCommand(std::shared_ptr<unit::Base> homeBase,std::shared_ptr<unit::Base> enemyBase,std::string type){
        this->homeBase = homeBase;
        this->enemyBase = enemyBase;
        this->type = type;
    };
    std::shared_ptr<unit::Unit> createUnit() {
        auto enemyBasePosition = enemyBase->getPosition();
        auto homeBasePosition = homeBase->getPosition();
        srand(time(0));

        int dx = 0;
        int dy = 0;
        auto choose = rand() % 3;

        switch (choose) {
        case 1:
            dy++;
            break;
        case 2:
            dy--;
            break;
        }

        if (homeBasePosition.x < enemyBasePosition.x) {
            dx++;
        }
        else {
            dx--;
        }
        
        
        if(type == "short"){
           return homeBase->createShortRangeUnit(dx, dy);
        }
        else if(type == "long"){
            return homeBase->createLongRangeUnit(dx, dy);
        }else{
            return homeBase->createDynamicRangeUnit(dx, dy);
        }
        
        return NULL;
    }
    std::shared_ptr<unit::Unit> getUnit() {
        unit = createUnit();
        return unit;
    }
    void Execute() override {
        getUnit();
    }
private:
    std::shared_ptr<unit::Base> homeBase;
    std::shared_ptr<unit::Base> enemyBase;
    std::string type;
    std::shared_ptr<unit::Unit> unit;
    
};
#endif /* createunitcommand_hpp */
