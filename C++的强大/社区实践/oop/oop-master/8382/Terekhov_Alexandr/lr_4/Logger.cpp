#include "Logger.h"

LoggerF::LoggerF() {
    file.open("LOG.txt", std::ios_base::out);
    if (!file.is_open()) {
        exit(1);
    }
    file << time.show() << "  Start!\n";
}

LoggerF::~LoggerF() {
    file.close();
}

LoggerF& LoggerF::operator<<(std::string log) {
    file << time.show() << "  " << log << "\n";
    lg << "Очень важно";
    return *this;
}

LoggerC::LoggerC(){
    std::cout << time.show() << "Start!\n";
}

LoggerC &LoggerC::operator<<(std::string log) {
    std::cout << time.show() << log << "\n";
    lg << "Очень важно";
    return *this;
}

std::string CurrentTime::show() {
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string str = ctime(&time);
    str.erase(str.end() - 1);
    return str;
}

std::string CurrentTimeCon::showC() {
    return "";
}

std::string CurrentTimeCon::show() {
    return showC();
}
