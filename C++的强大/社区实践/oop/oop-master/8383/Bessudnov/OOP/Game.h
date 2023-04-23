#pragma once
#include "GameManager.h"
#include "NeutralObject.h"
#include "GameField.h"
#include "GameVisualiser.h"
#include "GameLoaderSaver.h"
#include <vector>


class GameRule;

template<typename Rule>
class Game {
private:

	GameLoaderSaver *loaderSaver;

	GameVisualiser *visualiser;
	GameRule *rule;
	GameManager *blueTeamManager;
	GameManager *redTeamManager;
	GameField *gameField;
	NeutralObjectContainer *neutralObjects;
	Game();

	GameManager *currentTeam;

	static Game *game;
	void saveGame();
	void loadGame();

public:
	void newGame();
	~Game();

	static Game *getInstance();

	GameManager *getCurrentTeam() {
		return currentTeam;
	}

	GameManager *getBlueTeamManager() {
		return blueTeamManager;
	}

	GameManager *getRedTeamManager() {
		return redTeamManager;
	}

	void switchTeams() {
		currentTeam->isActive = false;
		if (currentTeam == blueTeamManager) {
			currentTeam = redTeamManager;
		} else {
			currentTeam = blueTeamManager;
		}

		currentTeam->isActive = true;
	}

	int gameCycle();

};

//class for states of rules
//using state pattern
//drives rule behavoiur over game time
class RuleState {
protected:
	GameRule *ruleOwner;
public:
	RuleState() = default;
	void initRuleOwner(GameRule *rule) {
		ruleOwner = rule;
	}


	virtual ~RuleState() = default;
	virtual int stateAction() = 0;
};

class StartRuleState : public RuleState {
public:
	int stateAction();
};

class QueueRuleState : public RuleState {
public:
	int stateAction();
};

class WinRuleStateUnitsDomination : public RuleState {
private:
	int countUnits(GameManager *manager);
public:
	int stateAction();
};

class WinRuleStateDewDomination : public RuleState {
private:
	int countDew(GameManager *manager);
public:
	int stateAction();
};



////////////RULES/////////////////////////
class GameRule {
protected:
	int absoluteActions;
	int availableActions;
	int turns;
	RuleState *currentState;
public:
	GameRule() : currentState(new StartRuleState) {
		currentState->initRuleOwner(this);
	}

	void switchState(RuleState *state) {
		currentState = state;
		currentState->initRuleOwner(this);
	}

	void resetActions() {
		availableActions = absoluteActions;
	}

	void useAction() {
		availableActions--;
	}

	int actionsCheck() {
		if(availableActions == 0) {
			resetActions();
			return 0;
		}

		return 1;
	}

	void fillState(std::vector<int> &save);
	void loadState(std::vector<int> &save);

	virtual void turnEnd() = 0;
	virtual bool isTurnsEnded() = 0;


	virtual ~GameRule() {
		delete currentState;
	};
	virtual int ruleAction() = 0;
	virtual GameManager *getGameManager() = 0;
	virtual GameManager *getBlueTeam() = 0;
	virtual GameManager *getRedTeam() = 0;
	virtual void switchTeams() = 0;
};



//players try to collect maximum amount of dew for limited turns count
class DewDomination : public GameRule { 
public:
	DewDomination() : GameRule() {
		absoluteActions = 10;
		availableActions = 10;
		turns = 4;
	}
	int ruleAction();

	GameManager *getGameManager() {
		Game<DewDomination> *gameInstance;
		gameInstance = Game<DewDomination>::getInstance();

		return gameInstance->getCurrentTeam();
	}

	void turnEnd() {
		turns--;
	}

	bool isTurnsEnded() {
		if (turns == 0) {
			return true;
		}

		return false;
	}

	void switchTeams() {
		Game<DewDomination> *gameInstance;
		gameInstance = Game<DewDomination>::getInstance();
		gameInstance->switchTeams();
	}

	GameManager *getRedTeam();
	GameManager *getBlueTeam();
};

//players try to have as much units as possible at the end of the game;
class UnitsDomination : public GameRule {
public:
	UnitsDomination() : GameRule() {
		absoluteActions = 10;
		availableActions = 10;
		turns = 6;
	}


	void turnEnd() {
		turns--;
	}

	bool isTurnsEnded() {
		if (turns == 0) {
			return true;
		}

		return false;
	}

	int ruleAction();

	GameManager *getGameManager() {
		Game<UnitsDomination> *gameInstance;
		gameInstance = Game<UnitsDomination>::getInstance();

		return gameInstance->getCurrentTeam();
	}

	void switchTeams() {
		Game<UnitsDomination> *gameInstance;
		gameInstance = Game<UnitsDomination>::getInstance();
		gameInstance->switchTeams();
	}

	GameManager *getRedTeam();
	GameManager *getBlueTeam();
};



template<typename Rule>
inline void Game<Rule>::saveGame() {
	std::vector<int> ruleStates;
	rule->fillState(ruleStates);

	loaderSaver->saveGame(ruleStates);
}

template<typename Rule>
inline void Game<Rule>::loadGame() {
	std::vector<int> ruleStates;
	
	ruleStates = loaderSaver->loadGame();
	rule->loadState(ruleStates);
}

template<typename Rule>
inline void Game<Rule>::newGame() {
	rule = new Rule();
	gameField = new GameField("Map01.txt");
	neutralObjects = new NeutralObjectContainer("Objects01.txt", gameField);
	visualiser = new GameVisualiser(gameField, neutralObjects);

	redTeamManager = new GameManager(gameField, neutralObjects, visualiser);
	blueTeamManager = new GameManager(gameField, neutralObjects, visualiser);

	loaderSaver = new GameLoaderSaver(blueTeamManager, redTeamManager, neutralObjects, gameField);

	visualiser->setBlueTeam(blueTeamManager);
	visualiser->setRedTeam(redTeamManager);

	currentTeam = blueTeamManager;
	currentTeam->isActive = true;

}

template<typename Rule>
Game<Rule>::Game() {
}

template<typename Rule>
Game<Rule>::~Game() {
}

template<typename Rule>
int Game<Rule>::gameCycle() {
	for (;;) {
		int result;
		result = rule->ruleAction();

		switch (result) {
		case -1:
			return 0;
		case -2:
			saveGame();
			break;
		case -3:
			loadGame();
			break;
		case -4:
			return 1;
		default:
			break;
		}

		visualiser->update();
	}
}

template<typename Rule>
Game<Rule> *Game<Rule>::game = nullptr;

template<typename Rule>
Game<Rule> *Game<Rule>::getInstance() {
	if (game == nullptr) {
		game = new Game();
	}

	return game;
}