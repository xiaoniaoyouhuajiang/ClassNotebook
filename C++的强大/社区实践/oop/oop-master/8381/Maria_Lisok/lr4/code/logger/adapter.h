#ifndef ADAPTER_H
#define ADAPTER_H
#include <map>
#include "logger.h"

#include "enums.h"
#include "convertEnum.h"
class Adapter
{
public:
    Adapter(Logger*);
    ~Adapter();
    void setLogger(Logger *value);
    void makeLog(Actions act, map<string, int> data);
private:
    string baseAddLog(map<string, int> data);
    string neutralAddLog(map<string, int> data);
    string unitAddLog(map<string, int> data);
    string attackLog(map<string, int> data);
    string moveLog(map<string, int> data);
    string gameInfoLog(map<string, int> data);
    string baseInfoLog(map<string, int> data);
    string userInfoLog(map<string, int> data);
    string neutralInfoLog(map<string, int> data);
    string landCellInfo(map<string, int> data);
    Logger* logger;

};

#endif // ADAPTER_H
