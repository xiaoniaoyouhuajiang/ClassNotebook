#ifndef attackcommand_hpp
#define attackcommand_hpp


#include "command.hpp"


class AttackCommand : public Command
{
public:
    AttackCommand(std::shared_ptr<BattleField> battleField,std::shared_ptr<unit::Unit> unit, std::shared_ptr<Adapter> log){
        this->battleField = battleField;
        this->log = log;
        this->unit = unit;
    };
    bool attack() {
        auto unitPosition = unit->getPosition();
        auto weapon = unit->getWeapon();
        auto dist = static_cast<int>(weapon->getDistanceAttack());
        auto player = unit->getPlayer();

        for (int i = unitPosition.y - dist; i <= unitPosition.y + dist; ++i) {
            for (int j = unitPosition.x - dist; j <= unitPosition.x + dist; ++j) {
                if (j < battleField->getWidth() && j >= 0 && i < battleField->getHeight() && i >= 0) {
                    if (sqrt(pow(i - unitPosition.y, 2) + pow(j - unitPosition.x, 2)) <= dist) {
                        auto cell = battleField->getFieldCell(Position2D(j, i));
                        if (!cell->isEmpty()) {
                            auto enemy = cell->getUnit();
                            if (enemy->getPlayer() != player) {
                                log->writeTo(UnitLog::attackMessage(unit, enemy));
                                log->writeTo(UnitLog::healthMessage(enemy,weapon->getDamage() * enemy->getArmor()->getResistance()));

                                enemy->makeDamage(weapon->getDamage() *enemy->getArmor()->getResistance());
                                attacked = true;
                                return true;
                            }
                        }
                    }
                }
            }
        }
        attacked = true;
        return false;
    }
    bool getExecution(){
        return attacked;
    }
    void Execute() override {
        attack();
    }
private:
    std::shared_ptr<BattleField> battleField;
    std::shared_ptr<unit::Unit> unit;
    std::shared_ptr<Adapter> log;
    bool attacked;
};
#endif /* attackcommand_hpp */
