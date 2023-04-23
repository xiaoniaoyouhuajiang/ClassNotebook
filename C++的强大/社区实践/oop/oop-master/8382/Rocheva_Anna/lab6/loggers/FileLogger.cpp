#include "FileLogger.hpp"

void FileLogger::print() {
    if (out.is_open()){
        count++;
        out << *this << std::endl;
    }
}

std::ostream& operator<< (std::ostream &out, const FileLogger &logger){
    out << logger.count << " [" << logger.fileName << "] : " << logger.log;
    return out;
}
