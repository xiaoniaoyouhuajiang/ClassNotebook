#include "TypeError.h"

TypeError::TypeError(std::string place, std::string have) {
    message_error = "Error:" + place + ", params is " + have + ", but expected type int";
}

const char* TypeError::what() const noexcept {
    return message_error.c_str();
}
