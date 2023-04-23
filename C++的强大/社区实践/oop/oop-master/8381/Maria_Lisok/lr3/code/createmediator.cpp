#include "createmediator.h"

#include "playingfield.h"
CreateMediator::CreateMediator(PlayingField *field, Base *base):field(field), base(base)
{

}

void CreateMediator::notify(Unit *item, unsigned x, unsigned y)
{
    field->addUnit(item, x, y);
}
