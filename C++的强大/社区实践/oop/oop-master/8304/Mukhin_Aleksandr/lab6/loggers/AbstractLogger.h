#ifndef LAB2_ABSTRACTLOGGER_H
#define LAB2_ABSTRACTLOGGER_H

#include <string>
#include <fstream>
#include <iostream>

class AbstractLogger {
protected:
    unsigned int number = 1;
    std::ofstream output;
public:
    AbstractLogger() = default;
    explicit AbstractLogger(std::string filename);
    std::string filename{};
    virtual bool write(std::string) = 0;
    friend std::ostream& operator<< (AbstractLogger*, std::string);
    ~AbstractLogger();
};


#endif
