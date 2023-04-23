
#include "terminallog.hpp"

void TerminalLog::writeTo(const std::string& msg, TYPE type)
{
    std::cout << getMessageType(type) + " " + msg + "\n";
}
