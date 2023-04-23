#include "NeutralObject.h"


void NeutralObject::interaction() const {
    this->mediator->make_action();
}