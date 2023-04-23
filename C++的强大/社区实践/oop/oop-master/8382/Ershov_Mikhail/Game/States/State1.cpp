#include "State1.h"

bool State1::handle(std::string s) {
    std::string character;
    character.push_back(s[0]);
    character.push_back(s[1]);
    if (character == "MS" || character == "MW" || character == "EA" || character == "EI") return true;
    return false;
}

//"OD" "OR" "MS" "MW" "EA" "EI"