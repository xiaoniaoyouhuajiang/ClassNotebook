
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "iostream"
#include "ostream"
#include "fstream"
#include <stdio.h>
#include <time.h>



class Logger
{
public:
    std::ofstream out;
    Logger() {
        out.open("./log.txt", std::ios_base::out | std::ios_base::app);
    }
    ~Logger() {
        out.close();
    }

    friend std::ostream& operator << (std::ostream& out, std::string str) {
        out  << str << std::endl;
        return out;
    }

    bool WriteToFile(std::string str) {
        if (out.is_open())
        {
            time_t rawtime;
            time(&rawtime);
            out << "Time:" << ctime(&rawtime) << " Message:" << str << std::endl;
        }
        return true;
    }
    bool WriteToTerminal(std::string str) {
        time_t rawtime;
        time(&rawtime);
        std::cout << "Time: " << ctime(&rawtime) << " Message: " << str << std::endl;
        return true;
    }
};

class Proxy
{
public:
    Proxy(Logger* write, bool logToFile, bool logToTerminal, bool withoutLog) {
        this->write = write;
        this->logToFile = logToFile;
        this->logToTerminal = logToTerminal;
        this->withoutLog = withoutLog;
    }

    Logger* write;
    bool logToFile;
    bool logToTerminal;
    bool withoutLog;

    bool SpecificRequest(std::string str) {
        if (withoutLog) {

        }
        else {
            if (logToFile) {
                this->write->WriteToFile(str);
            }
            if (logToTerminal) {
                this->write->WriteToTerminal(str);
            }
        }
        return true;
    }
};

class Target
{
public:
    virtual ~Target() = default;

    virtual bool LOG(std::string str) const {
        return true;
    }
};

class Adapter : public Target
{
public:
    Proxy* write_;
    Adapter(Proxy* write) : write_(write) {}
    bool LOG(std::string str) const override {
        this->write_->SpecificRequest(str);
        return true;
    }
};