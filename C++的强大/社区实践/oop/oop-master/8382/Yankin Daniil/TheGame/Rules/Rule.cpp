#include "Rule.h"

Rule::Rule(uint16_t playerCount) : playerCount(playerCount) {}

void Rule::setPlayerCount(uint16_t playerCount) {
    if (playerCount < 2 || playerCount > 4) {
        return;
    }
    this->playerCount = playerCount;
}
