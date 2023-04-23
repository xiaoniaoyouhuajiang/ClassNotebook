#pragma once
#include "PlayableBoardUnit.h"
class PongoBaseBoardUnit;
class PongoBoardUnit : public PlayableBoardUnit
{
public:
	//каждый игровой юнит(не база), которым можем ходить(кавалерия,артиллерия)
	PongoBoardUnit(PongoBaseBoardUnit* base);//в конструкторе приним.в себя указатель на базу, которой они принадлежат и хранят его
	PongoBoardUnit(QJsonObject snapshot, PongoBaseBoardUnit* base);
	virtual ~PongoBoardUnit();
	static int getUnitCount();
	static void resetUnitCount() { unit_count = 0; };
	QJsonObject getSnapshot() override;
	virtual std::string getClassName() = 0;
protected:
	PongoBaseBoardUnit* _base;
private:
	static int unit_count;
};

