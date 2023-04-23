#include "pch.h"
#include "Game.h"
#include "GameBases.h"
#include "GameUnits.h"
#include <iostream>


//Rules
int UnitsDomination::ruleAction() {
	int result = currentState->stateAction();
	if (isTurnsEnded()) {
		switchState(new WinRuleStateUnitsDomination);
	}
	return result;
}

GameManager * UnitsDomination::getRedTeam() {
	Game<UnitsDomination> *gameInstance;
	gameInstance = Game<UnitsDomination>::getInstance();
	return gameInstance->getRedTeamManager();
}

GameManager * UnitsDomination::getBlueTeam() {
	Game<UnitsDomination> *gameInstance;
	gameInstance = Game<UnitsDomination>::getInstance();
	return gameInstance->getBlueTeamManager();
}

int DewDomination::ruleAction() {
	int result = currentState->stateAction();
	if (isTurnsEnded()) {
		switchState(new WinRuleStateDewDomination);
	}
	return result;
}

GameManager *DewDomination::getRedTeam() {
	Game<DewDomination> *gameInstance;
	gameInstance = Game<DewDomination>::getInstance();
	return gameInstance->getRedTeamManager();
}

GameManager * DewDomination::getBlueTeam() {
	Game<DewDomination> *gameInstance;
	gameInstance = Game<DewDomination>::getInstance();
	return gameInstance->getBlueTeamManager();
}


int WinRuleStateUnitsDomination::countUnits(GameManager *manager) {
	return manager->gameUnits->units.size();
}

//RuleStates
int WinRuleStateUnitsDomination::stateAction() {
	std::cout << "The END" << std::endl;
	int redTeamUnitsCount;
	int blueTeamUnitsCount;

	redTeamUnitsCount = countUnits(ruleOwner->getRedTeam());
	blueTeamUnitsCount = countUnits(ruleOwner->getBlueTeam());

	std::cout << "Blue Team units: " << blueTeamUnitsCount << std::endl;
	std::cout << "Red Team units: " << redTeamUnitsCount << std::endl;

	if (redTeamUnitsCount == blueTeamUnitsCount) {
		std::cout << "Winner is friendship" << std::endl;
	}

	if (redTeamUnitsCount > blueTeamUnitsCount) {
		std::cout << "It's a goal by RED Team" << std::endl;
	}

	if (blueTeamUnitsCount > redTeamUnitsCount) {
		std::cout << "It's a goal by BLUE Team" << std::endl;
	}

	return -1;

}

int QueueRuleState::stateAction() {
	GameManager *manager = ruleOwner->getGameManager();
	int result;

	result = 0;
	if (ruleOwner->actionsCheck()) {
		result = manager->playerAction();
		if (result == 2) {
			ruleOwner->useAction();
		}
	} else {
		ruleOwner->switchTeams();
		ruleOwner->turnEnd();
	}

	return result;
}

int StartRuleState::stateAction() {
	GameManager *manager = ruleOwner->getGameManager();
	manager->pickBases(0.0);
	ruleOwner->switchTeams();

	manager = ruleOwner->getGameManager();
	manager->pickBases(1.0);
	ruleOwner->switchTeams();

	ruleOwner->switchState(new QueueRuleState);
	return 0;
}

int WinRuleStateDewDomination::countDew(GameManager *manager) {
	int dewAmount; 
	dewAmount = 0;
	for (auto &base : manager->baseContainer->bases) {
		dewAmount += base->dew.getVal();
	}

	return dewAmount;
}

int WinRuleStateDewDomination::stateAction() {
	std::cout << "The END" << std::endl;
	int redTeamDewAmount;
	int blueTeamDewAmount;

	redTeamDewAmount = countDew(ruleOwner->getRedTeam());
	blueTeamDewAmount = countDew(ruleOwner->getBlueTeam());

	std::cout << "Blue Team dew: " << blueTeamDewAmount << std::endl;
	std::cout << "Red Team dew: " << redTeamDewAmount << std::endl;

	if (redTeamDewAmount == blueTeamDewAmount) {
		std::cout << "Winner is friendship" << std::endl;
	}

	if (redTeamDewAmount > blueTeamDewAmount) {
		std::cout << "It's a goal by RED Team" << std::endl;
	}

	if (blueTeamDewAmount > redTeamDewAmount) {
		std::cout << "It's a goal by BLUE Team" << std::endl;
	}

	return -1;

}

void GameRule::fillState(std::vector<int>& save) {
	save.push_back(absoluteActions);
	save.push_back(availableActions);
	save.push_back(turns);
}

void GameRule::loadState(std::vector<int>& save) {
	absoluteActions = save[0];
	availableActions = save[1];
	turns = save[2];
}
