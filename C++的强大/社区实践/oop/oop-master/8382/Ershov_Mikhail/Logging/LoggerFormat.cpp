#define _CRT_SECURE_NO_WARNINGS
#include "LoggerFormat.h"

string FormatterTime::format(string str) {
    time_t rawtime;
    char buffer[80];
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "[%H:%M:%S] ", timeinfo);
    return buffer + str;
}

//-----------------------------------------------------

string FormatterEmpty::format(string str) { 
    return str; 
}