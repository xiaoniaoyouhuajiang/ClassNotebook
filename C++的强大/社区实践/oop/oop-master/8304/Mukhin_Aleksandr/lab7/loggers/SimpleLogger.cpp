#include "SimpleLogger.h"

bool SimpleLogger::write(std::string information) {
    this << information;
    return true;
}

SimpleLogger::SimpleLogger() {
    output << "Start recording!" << std::endl;
}

SimpleLogger::~SimpleLogger() {
    output << "End recording!" << std::endl;
}
