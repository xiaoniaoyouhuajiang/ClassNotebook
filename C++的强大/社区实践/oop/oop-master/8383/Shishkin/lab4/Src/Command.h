#pragma once

//#include "Field.h"
#include <iostream>
#include "Base.h"

using namespace std;

class Field;
//class Base;

class Command {
public:
	virtual void execute(string&) = 0;
	virtual ~Command() = default;
};

class CommandBase : public Command {
public:
    CommandBase(Field* field, Base* base, string type);
    void execute(string& str);

private:
    Field* field;
    Base* base;
    string type;
};

class CommandField : public Command {
public:
    CommandField(Field* field, string type);
    void execute(string& str);

private:
    Field* field;
    string type;
};
