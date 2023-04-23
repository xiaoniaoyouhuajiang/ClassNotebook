#pragma once

#include "State.h"

class State2 : public State {
public:
    bool handle(std::string s) override;
};
