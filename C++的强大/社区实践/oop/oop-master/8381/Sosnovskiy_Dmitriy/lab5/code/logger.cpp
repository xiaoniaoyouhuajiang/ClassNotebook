#include "logger.h"

std::ostream& operator<<(std::ostream& os, LogData* logData)
{
    time_t seconds = time(0);
    tm* timeinfo = localtime(&seconds);
    os << asctime(timeinfo) << logData->convertToString().toStdString().c_str();
    return os;
}

QTextStream& operator<<(QTextStream& os, LogData* logData)
{
    time_t seconds = time(0);
    tm* timeinfo = localtime(&seconds);
    os << asctime(timeinfo) << logData->convertToString().toStdString().c_str();
    return os;
}
