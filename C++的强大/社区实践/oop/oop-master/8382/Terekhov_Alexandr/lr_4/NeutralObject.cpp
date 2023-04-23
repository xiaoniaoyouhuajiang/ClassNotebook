#include "NeutralObject.h"

NeutralObject::NeutralObject(char pict) : AbstractObject(pict) {}

HealthBox::HealthBox() : NeutralObject('+') {}

ArmorBox::ArmorBox() : NeutralObject('o') {}

RandomBox::RandomBox() : NeutralObject('?') {}

RareBox::RareBox() : NeutralObject('X') {}
