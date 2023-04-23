#include "Logger.h"

Logger::Logger(){
    loggerOn = false;
    writeToFile = false;
    ptr = nullptr;
}

void Logger::print(std::string message) {
    if (!loggerOn) {
        return;
    }
    if (writeToFile){
        ptr = new File("logs.txt");
        ptr->write(message);
        delete  ptr;
    }
    else{
        std::cout << "log message: " << message;
    }
}
