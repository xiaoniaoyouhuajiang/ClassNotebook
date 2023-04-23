#ifndef LABOOP_ADAPTER_HPP
#define LABOOP_ADAPTER_HPP

#include "Logger.hpp"
#include "../GameField.hpp"

class Adapter: public Logger {
public:
    explicit Adapter(GameField *field) : field(field), logger(nullptr){};
    void print() final {logger->print();};
    void setLogger(Logger *logger1) {this->logger = logger1;};
    void addLog(std::string logString) final;
    void setLog(std::string logString) final;
    void setFormat(int format) final {};
    int getFormat() final {};
private:
    Logger *logger;
    GameField *field;
};


#endif //LABOOP_ADAPTER_HPP
