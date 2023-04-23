#include "TerminalLogger.hpp"

void TerminalLogger::print() {
    count++;
    std::cout << *this << std::endl;
}

std::ostream& operator<< (std::ostream &out, const TerminalLogger &logger){
    out << logger.count << " [TERMINAL] : " << logger.log;
    return out;
}
