
#ifndef Logger_h
#define Logger_h
#include <string>
#include <iostream>
#include <fstream>


enum TypeLog{CONSOLE, INFILE, CONSOLE_AND_FILE};

extern std::string logsName;

class LogInfo{
private:
    std::string messageForLog;
    
public:
    LogInfo( std::string messageForLog):messageForLog(messageForLog){};
    
    friend std::ostream& operator <<(std::ostream& os, const LogInfo& log){
        os << log.messageForLog <<std::endl;
        return os;
    }
};


class ILogger{
public:
    virtual void request(LogInfo* log){};
};


class Logger: public ILogger{
private:
    std::ofstream outputFile;
    
public:
    Logger();
    ~Logger();
    virtual void request(LogInfo* log) override;
};


class LogProxy: public ILogger{
private:
    Logger* logger;
    TypeLog type;
public:
    LogProxy(Logger* logger, TypeLog type = INFILE):logger(logger), type(type){}
    void request(LogInfo* log) override;
    void switchType(TypeLog newType);
    TypeLog getType();
};

class Unit;
class Base;

class Adapter: public Logger{
public:
    void InfoUnit(Unit* unit);
    void InfoBase(Base* base);
    void InfoAttack(Unit* unit, Unit* enemy, int damage);
    void InfoAttack(Unit* unit, Base* enemy, int damage);
    void InfoMove(Unit* unit, int oldCoordX, int oldCoordY);
    void InfoStr(std::string mess);
    void InfoErrorCode(const std::error_code& code);
};



#endif 
