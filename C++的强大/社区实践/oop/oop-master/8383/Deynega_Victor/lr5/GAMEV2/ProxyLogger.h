#pragma once
#include "Logger.h"

class ProxyLogger : public Logger {
public:
    void switchLogStream(std::string mode);
    void turnOnOffLog(std::string mode);
};