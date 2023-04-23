#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "stdafx.h"
#include "GameObjects.h"
#include "GameMap.h"
#include "my_list.h"
#include "logger.h"
#include "base.h"

int main() {

	Logger* L = new Logger;
	Proxy* proxy = new Proxy(L,true,true,false);
	Adapter LOGGER(proxy);
	LOGGER.LOG("Hellow!");

	std::shared_ptr<GameMap> map = std::make_shared<GameMap>(*(new GameMap(5, 5)));

	Base myBase(0, 0, Factions::Player, map);
	Base enemyBase(4, 4, Factions::Enemy, map);

	myBase.createUnit(1,1,1);
	myBase.createUnit(2,1,1);

	enemyBase.createUnit(3, 1, 1);
	enemyBase.createUnit(4, 1, 1);

	map->unitStatistic();

	std::cout << std::endl;

	map->printLand();
	
	std::cout << std::endl;

	map->createNObj(2, 2, 1);
	map->createNObj(2, 3, 2);

	map->printNObj();

	std::cout << std::endl;

	system("Pause");
	return 0;
}