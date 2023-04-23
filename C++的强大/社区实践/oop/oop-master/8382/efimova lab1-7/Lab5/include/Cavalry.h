#pragma once
#include "PongoBoardUnit.h"
#include "BoardUnitFactory.h"
class PongoBaseBoardUnit;

class Cavalry : public PongoBoardUnit
{
public:
	Cavalry(PongoBaseBoardUnit* base);
	Cavalry(QJsonObject snapshot, PongoBaseBoardUnit* base) : PongoBoardUnit(snapshot, base) {};
	std::vector<ActionMeta> turnAction() override;
	std::string getClassName() override;
};

class HeavyCavalry : public Cavalry
{
public:
	HeavyCavalry(PongoBaseBoardUnit* base);
	HeavyCavalry(QJsonObject snapshot, PongoBaseBoardUnit* base) : Cavalry(snapshot, base) {};
	std::vector<ActionMeta> userAction(Board::BoardCell targetCell, int action = -1) override;
	std::vector<ActionMeta> defend(ActionMeta) override;
	std::string getName() override;
};

class LightCavalry : public Cavalry
{
public:
	LightCavalry(PongoBaseBoardUnit* base);
	LightCavalry(QJsonObject snapshot, PongoBaseBoardUnit* base) : Cavalry(snapshot, base) {};
	std::vector<ActionMeta> userAction(Board::BoardCell targetCell, int action = -1) override;
	std::vector<ActionMeta> defend(ActionMeta) override;
	std::string getName() override;
};

class CavalryFactory : public BoardUnitFactory
{
public:
	CavalryFactory(PongoBaseBoardUnit* base) : BoardUnitFactory(base) {};
	PlayableBoardUnit* createUnit(int type) override;
	PlayableBoardUnit* createUnit(QJsonObject snapshot) override;
};
