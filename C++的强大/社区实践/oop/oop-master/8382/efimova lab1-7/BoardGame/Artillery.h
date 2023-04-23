#pragma once
#include "PlayableBoardUnit.h"
#include "BoardUnitFactory.h"
class Artillery : public PlayableBoardUnit
{
public:
	Artillery() {};
	ActionMeta turnAction() override;
};

class Catapult : public Artillery
{
public:
	Catapult();
	ActionMeta userAction() override;
	ActionMeta defend(ActionMeta) override;
	BoardUnit* getCopy() override;
};

class Cannon : public Artillery
{
public:
	Cannon();
	ActionMeta userAction() override;
	ActionMeta defend(ActionMeta) override;
	BoardUnit* getCopy() override;
};

class ArtilleryFactory : public BoardUnitFactory //фабрика
{
public:
	ArtilleryFactory() {};
	BoardUnit* getType(int type) override;
};

