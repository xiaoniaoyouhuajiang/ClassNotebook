#pragma once
#include "BoardUnit.h"
class NeutralBoardUnit : public BoardUnit
{
	QJsonObject getSnapshot() override;
};

