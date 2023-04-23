#pragma once
#include "NeutralBoardUnit.h"
class DirtPit : public NeutralBoardUnit
{
public:
	std::vector<ActionMeta> turnAction() override;
	std::string getName() override;
};

