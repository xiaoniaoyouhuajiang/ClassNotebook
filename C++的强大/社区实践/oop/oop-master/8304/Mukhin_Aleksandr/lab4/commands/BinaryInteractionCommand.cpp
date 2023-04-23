#include "BinaryInteractionCommand.h"

void BinaryInteractionCommand::execute() const {
    if (command == "unit action") {
        cell1.unit->interaction();
    } else if (command == "base action") {
        cell1.base->interaction();
    }
}
