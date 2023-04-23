#ifndef LABOOP_NOLOGGER_HPP
#define LABOOP_NOLOGGER_HPP

#include "Logger.hpp"

class NoLogger : public Logger{
public:
    void setLog(std::string log) final {};
    void print() final {};
    void addLog(std::string logString) final {};
    void setFormat(int format) final {};
    int getFormat() final { return 0;};
};


#endif //LABOOP_NOLOGGER_HPP
