#pragma once

#include <string>

using namespace std;

class CommandMemento {
public:
    string memento;

    CommandMemento(string memento) : memento(memento){};
};
