#pragma once
#include "Rule.h"


class EliminationRule : public Rule
{
public:
    EliminationRule(uint16_t playerCount = 2);
    StartInit getStartInit(uint16_t width, uint16_t height) override;
    std::list<uint16_t> getPlayerOrder() override;
    std::pair<bool, std::vector<uint16_t>> checkEndGame() override;
};
