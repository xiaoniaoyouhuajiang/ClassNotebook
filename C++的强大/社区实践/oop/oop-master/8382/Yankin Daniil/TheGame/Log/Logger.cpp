#include "Logger.h"
#include <stdexcept>

FileLogger::FileLogger(std::string logFileName) {
    fileStream.open(logFileName);
    if (!fileStream.is_open())
        throw std::runtime_error("Open log file error") ;
}

FileLogger::~FileLogger() {
    fileStream.close();
}

void FileLogger::log(std::string& info) {
    this->info = info;
    time.update();
    fileStream << time << " || " << *this << std::endl;
}

std::string FileLogger::getInfo() {
    return info;
}



TerminalLogger::TerminalLogger() {}

void TerminalLogger::log(std::string& info) {
    this->info = info;
    time.update();
    std::cout << time << " || " << *this << std::endl;
}

std::string TerminalLogger::getInfo() {
    return info;
}



std::ostream& operator<<(std::ostream& stream, ILogger& logger) {
    return stream << logger.getInfo();
}
