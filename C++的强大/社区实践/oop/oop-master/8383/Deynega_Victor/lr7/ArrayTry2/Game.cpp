#include "Game.h"
#include "Rules.h"


Game::Game() {
	loser = 0;
	rule = new Rule1();
	turnCounter = 30;
}


void Game::startNewGame(){
    rule = new Rule1();
    this->turnCounter = 30;
}


/*void Game::play() {
	while (turnCounter) {
		if (rule->whoLose() == 1) {
			std::cout << "Defence won!\n";
			return;
		}
		if (rule->whoLose() == 2) {
            std::cout << "Attack won!\n";
			return;
		}
        if (rule->action(turnCounter, 0) == 1) { //start new game
			turnCounter = 30;
            rule = new Rule1;
			loser = 0;
			continue;
		}
		turnCounter--;
        //rule->board->draw();
	}
}
*/
