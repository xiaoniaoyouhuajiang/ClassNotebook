#include "../headers/logger.hpp"
#include "../headers/exceptions.hpp"

std::string Logger::getBuffer() {
    return buffer;
}
void Logger::appendBuffer(std::string newMessage) {
    buffer += newMessage;
}
void Logger::cleanBuffer() {
    buffer = std::string("");
}

FileLogger::FileLogger() {
    file.open(path, std::ios::out | std::ios::app);
    if (file.fail())
        throw FileErrorException(path, 3);
}
FileLogger::~FileLogger() {
    file.close();
}

void FileLogger::log(){
    file << buffer;
}

void TerminalLogger::log(){
    std::cout << buffer;
}