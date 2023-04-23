#include "attackunit.h"

AttackUnit::AttackUnit(Game<Rules> *game, Unit* who, Object* whom)
    :game_(game), who_(who), whom_(whom)
{

}
