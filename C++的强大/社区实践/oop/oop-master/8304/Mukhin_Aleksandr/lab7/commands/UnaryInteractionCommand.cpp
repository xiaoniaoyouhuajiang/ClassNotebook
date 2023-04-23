#include "UnaryInteractionCommand.h"

void UnaryInteractionCommand::execute() const {
    if (command == "neutral object action") {
        cell.neutral_object->interaction();
    } else if (command == "landscape action") {
        cell.landscape->interaction();
    }
}
