#include "InteractionError.h"

InteractionError::InteractionError(std::string place, int old_x, int old_y, int dest_x, int dest_y) {
    message_error = "Error:" + place + ", old_x = " + std::to_string(old_x) + ", old_y = " +
        std::to_string(old_y) + ", dest_x = " + std::to_string(dest_x) + ", dest_y = " + std::to_string(dest_y);
}

InteractionError::InteractionError(std::string place, int x, int y) {
    message_error = "Error:" + place + ", at x = " + std::to_string(x) + ", y = " + std::to_string(y);
}

const char* InteractionError::what() const noexcept {
    return message_error.c_str();
}
