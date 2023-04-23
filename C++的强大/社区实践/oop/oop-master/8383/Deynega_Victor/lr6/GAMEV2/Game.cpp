#include "Game.h"
#include "Rules.h"


Game<Rule1>::Game() {
	loser = 0;
	rule = new Rule1();
	turnCounter = 30;
}

Game<Rule1>* Game<Rule1>::getGame() {
	if (ptr == nullptr) {
		this->ptr = new Game();
	}
	return ptr;
}

Game<Rule2>::Game() {
	loser = 0;
	rule = new Rule2();
	turnCounter = 30;
}

Game<Rule2>* Game<Rule2>::getGame() {
	if (ptr == nullptr) {
		this->ptr = new Game();
	}
	return ptr;
}

void Game<Rule1>::play() {

}


void Game<Rule2>::play() {
	while (turnCounter) {
		if (rule->whoLose() == 1) {
			std::cout << "Defence won!\n";
			return;
		}
		if (rule->whoLose() == 2) {
			std::cout << "Defence won!\n";
			return;
		}
		if (rule->action(turnCounter) == 1) { //start new game
			turnCounter = 30;
			rule = new Rule2;
			loser = 0;
			continue;
		}
		turnCounter--;
		rule->board->draw();
	}
}

