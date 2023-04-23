//
// Created by Alex on 13.04.2020.
//

#include <iostream>
#include "TerminalLog.h"

std::ostream &operator<<(std::ostream &out, const TerminalLog &terminalLog) {
    out  << "Log(" << terminalLog.log_message << ")\n";
    return out;
}

void TerminalLog::log() {
    std::cout << *this;
}

void TerminalLog::setLogMessage(const std::string &logMessage) {
    log_message = logMessage;
}

void TerminalLog::logMessage(const std::string &logMessage) {
    setLogMessage(logMessage);
    log();
}

