#pragma once

#include <GAME/controller/BaseRules.hpp>

class Rules2 : public BaseRules<2> {
public:
	virtual GameBoard* makeBoard() override;
};