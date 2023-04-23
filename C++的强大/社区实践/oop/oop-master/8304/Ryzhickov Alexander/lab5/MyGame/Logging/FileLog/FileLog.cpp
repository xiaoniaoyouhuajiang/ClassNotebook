//
// Created by Alex on 13.04.2020.
//

#include <iostream>
#include "FileLog.h"

std::ostream &operator<<(std::ostream &out, const FileLog &fileLog) {
    out  << "Log(" << fileLog.log_message << ")\n";
    return out;
}

void FileLog::log() {
    fin << *this;
}

FileLog::FileLog(const std::string &path) : path(path) {
    fin.open(path);
}

void FileLog::setLogMessage(const std::string &logMessage) {
    log_message = logMessage;
}

void FileLog::logMessage(const std::string &logMessage) {
    setLogMessage(logMessage);
    log();
}

FileLog::~FileLog() {
    fin.close();
}
