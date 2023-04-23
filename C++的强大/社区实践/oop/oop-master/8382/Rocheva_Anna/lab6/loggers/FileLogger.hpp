#ifndef LABOOP_FILELOGGER_HPP
#define LABOOP_FILELOGGER_HPP

#include "Logger.hpp"
#include <utility>
#include "fstream"

class FileLogger : public Logger{
public:
    explicit FileLogger(std::string name) : fileName(name), count(0){ out.open(fileName, std::ios::app);};
    ~FileLogger() {out.close();};
    void print() final;
    void setLog(std::string logString) final {this->log = logString;};
    void addLog(std::string logString) final {log += logString;};
    void setFormat(int format) final {this->format = format;};
    int getFormat() final { return format;};
    friend std::ostream& operator<< (std::ostream &out, const FileLogger &logger);
private:
    std::string fileName;
    std::ofstream out;
    std::string log;
    int count;
    int format;
};


#endif //LABOOP_FILELOGGER_HPP
