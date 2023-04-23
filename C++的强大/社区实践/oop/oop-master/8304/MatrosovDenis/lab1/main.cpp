#include "stdafx.h"
#include "GameObjects.h"
#include "GameMap.h"
#include "my_list.h"

int main() {

	GameMap Map(10, 10);
	Cavalry newUnite(1, 1, Factions::Player);
	Map.addObject(newUnite);
	newUnite = Cavalry(6, 6, Factions::Enemy);
	Map.addObject(newUnite);
	newUnite = Cavalry(7, 6, Factions::Enemy);
	Map.addObject(newUnite);
	newUnite = Cavalry(8, 6, Factions::Enemy);
	Map.addObject(newUnite);

	std::shared_ptr<Node> tmpHead = std::make_shared<Node>(Map.getObjects().begin()->takeHead());
	for (int i = 0; i < 4; i++) {
		tmpHead->data->printStatistic();
		tmpHead = tmpHead->next;
	}
	
	system("Pause");
	system("cls");

	Map.moveObject(Map.Check(1, 1), 5, 5);

	Map.Check(5, 5)->printStatistic();
	Map.Check(6, 6)->printStatistic();

	system("Pause");
	system("cls");

	Map.Check(5, 5)->Attack(Map.Check(6, 6));

	Map.Check(6, 6)->printStatistic();


	system("Pause");
	return 0;
}