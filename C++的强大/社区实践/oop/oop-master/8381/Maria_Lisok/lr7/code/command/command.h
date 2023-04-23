#ifndef COMMAND_H
#define COMMAND_H
#include <map>
#include <iostream>
#include "enums.h"
using namespace std;
struct Data{
    int x, y;
    UnitsType unitType;
    NeutralType neutralType;
    int base;
};
class Command{
public:
    virtual map<string, int> mainInfoAboutObj()=0;
    virtual ~Command()=default;
protected:
    virtual map<string, int> noSuchAct()=0;
    Actions action;
    map<string, Data > params;

};
#endif // COMMAND_H
