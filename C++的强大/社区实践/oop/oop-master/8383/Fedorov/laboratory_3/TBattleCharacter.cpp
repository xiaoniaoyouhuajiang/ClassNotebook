
#include "TBattleCharacter.h"


Event TBattleCharacter::getAttackAttribute(){
    Event attribute;
    attribute.type = Event::ATTACK;
    attribute.attackAttribute.bonus = 0;
    attribute.attackAttribute.damage = damagePoint;
    attribute.attackAttribute.negativeEffect = 0;
    attribute.attackAttribute.distant = distantAttack;
    return attribute;
}


TBattleCharacter::TBattleCharacter() {

}
