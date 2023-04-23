#include <iostream>
#include <ctime>
#include "GameBoardStd.h"

int main() {
	srand(time(0));
	auto city = BoardStd::newBoard();
	city->info();
	city->newCityHall();
	city->newBuild();
	city->info();
	return 0;
}