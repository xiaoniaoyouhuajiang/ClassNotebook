#pragma once

#include <GAME/controller/BaseRules.hpp>

class Rules3 : public BaseRules<3> {
public:
	virtual GameBoard* makeBoard() override;
};