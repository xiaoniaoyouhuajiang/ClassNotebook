#pragma once

#include <string>

class State {
public:
    virtual bool handle(std::string s) = 0;
};
