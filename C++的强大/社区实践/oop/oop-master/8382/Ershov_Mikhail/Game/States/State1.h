#pragma once

#include "State.h"

class State1 : public State {
public:
    bool handle(std::string s) override;
};
