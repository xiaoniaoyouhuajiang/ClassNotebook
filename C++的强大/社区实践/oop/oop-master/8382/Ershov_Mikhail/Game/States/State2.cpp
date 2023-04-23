#include "State2.h"

bool State2::handle(std::string s) {
    std::string character;
    character.push_back(s[0]);
    character.push_back(s[1]);
    if (character == "OR" || character == "OD") return true;
    return false;
}