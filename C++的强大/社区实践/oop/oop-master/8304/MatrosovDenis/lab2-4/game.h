#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "stdafx.h"
#include "GameObjects.h"
#include "GameMap.h"
#include "my_list.h"
#include "logger.h"
#include "base.h"

/*
################################
Фасад игры
################################
*/

class Facade
{
public:
	Facade() {
		L = new Logger;
		proxy = new Proxy(L, true, true, false);
		LOGGER = Adapter(proxy);

		std::shared_ptr<GameMap> map = std::make_shared<GameMap>(*(new GameMap(5, 5)));

		Base myBase(0, 0, Factions::Player, map);
		Base enemyBase(4, 4, Factions::Enemy, map);

		isRun = false;
	}
	void Attack(int x1,int y1,int x2,int y2) {
		std::shared_ptr<BaseUnit> u1 = map->Check(x1, y1);
		std::shared_ptr<BaseUnit> u2 = map->Check(x2, y2);
		if (u1 && u2) {
			int r = u1->Range();
			if (abs(u1->getX() - u2->getX()) <= r && abs(u1->getY() - u2->getY()) <= r) {
				u2->GetDamage(map->checkLand(x1, y1)->RecalculateDamage(u1->Power()));
				LOGGER.LOG("Attack has been done");
			}
		}
	}



	void Move(int x1, int y1, int x2, int y2) {
		std::shared_ptr<BaseUnit> u1 = map->Check(x1, y1);
		if (u1) {
			int r = u1->Endurance();
			if (abs(u1->getX() - x2) <= r && abs(u1->getY() - y2) <= r) {
				if (map->checkLand(x2, y2)->is_passable && map->Check(x2,y2) == nullptr) {
					u1->Move(x2, y2);
					LOGGER.LOG("Move has been done");
				}
			}
		}
	}

	void AddUnit(int x, int y, Factions f, int type) {
		if (f == Factions::Player) {
			map->UserBase()->createUnit(x, y, type);
			LOGGER.LOG("Unit has been added");
		}
		if (f == Factions::Enemy) {
			map->EnemyBase()->createUnit(x, y, type);
			LOGGER.LOG("Unit has been added");
		}
	}

	void AddNObj(int x, int y, int type)
	{
		map->createNObj(x, y, type);
		LOGGER.LOG("Create new neutral object");
	}

	~Facade() {
		delete L;
		delete proxy;
	}

	void run();

private:
	std::shared_ptr<GameMap> map;
	Logger* L;
	Proxy* proxy;
	Adapter LOGGER;
	bool isRun;
};

class Command
{
public:
	virtual ~Command() {}
	void execute() {};
protected:
	Command(Facade* p) : pgame(p) {}
	Facade* pgame;
};

class RunCommand : public Command {
public:
	RunCommand(Facade* p) : Command(p) {}
	void execute() {
		pgame->run();
	}
};

class CreateNObjCommand : public Command {
public:
	CreateNObjCommand(Facade* p) : Command(p) {}
	void execute(int x,int y, int type) {
		pgame->AddNObj(x, y, type);
	}
};

class MoveCommand : public Command {
public:
	MoveCommand(Facade* p) : Command(p) {}
	void execute(int x, int y, int x2, int y2) {
		pgame->Move(x,y,x,y2);
	}
};

class AttackCommand : public Command {
public:
	AttackCommand(Facade* p) : Command(p) {}
	void execute(int x, int y, int x2, int y2) {
		pgame->Attack(x, y, x, y2);
	}
};

class AddUnitCommand : public Command {
public:
	AddUnitCommand(Facade* p) : Command(p) {}
	void execute(int x, int y, Factions f, int type) {
		pgame->AddUnit(x, y, f, type);
	}
};