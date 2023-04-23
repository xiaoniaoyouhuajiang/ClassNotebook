#pragma once

//#include "Field.h"
#include <iostream>

using namespace std;

class Field;
class Base;

class Command {
public:
	virtual void execute(string&) = 0;
	virtual ~Command() = default;
};

class CommandBase : public Command {
public:
    CommandBase(Field* field, Base* base, int x, int y, string type);
    void execute(string& str);

private:
    Field* field;
    Base* base;
    int x;
    int y;
    string type;
};