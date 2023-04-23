#include <ctime>
#include "ComplexLogger.h"

bool ComplexLogger::write(std::string information) {
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    logger->write(std::string(asctime(timeinfo)) + "\t\t\t\t\t\t: " + information + '\n');
    return true;
}
