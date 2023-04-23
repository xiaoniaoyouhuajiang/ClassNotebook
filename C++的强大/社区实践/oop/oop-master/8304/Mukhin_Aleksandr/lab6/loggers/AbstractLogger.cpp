#include "AbstractLogger.h"

AbstractLogger::AbstractLogger(std::string filename) {
    this->filename = filename;
    output.open(filename, std::ios::app);
}

AbstractLogger::~AbstractLogger() {
    output.close();
}

std::ostream& operator<< (AbstractLogger* log, std::string information) {
    if (log->filename.empty()) {
        std::cout << log->number++ << ") " << information << std::endl;
        return std::cout;
    } else {
        if (log->output.is_open()) {
            log->output << log->number++ << ") " << information << std::endl;
            return log->output;
        }
    }
    return std::cout;
}
