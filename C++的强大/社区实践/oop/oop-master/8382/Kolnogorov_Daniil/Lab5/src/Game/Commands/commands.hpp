#pragma once

#include "../game.hpp"
#include <string>
#include <vector>

using namespace std;

class CommandMemento;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(Game* game) = 0;
    virtual CommandMemento get_memento() = 0;
    virtual bool save_to_history() { return true; }
};

class CommandHandler {
public:
    CommandHandler* next;

    virtual ~CommandHandler() = default;
    virtual bool can_handle(vector<string> command) = 0;
    virtual Command* handle(vector<string> command) = 0;
    void set_next(CommandHandler* next) { this->next = next; }
};
