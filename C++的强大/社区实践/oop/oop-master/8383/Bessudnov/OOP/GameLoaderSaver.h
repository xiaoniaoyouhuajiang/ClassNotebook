#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "GameManager.h"
#include "GameField.h"
#include "NeutralObject.h"

class GameLoaderSaver {
private:
	std::vector<int> saveState;
	GameManager *blueTeamGameManagerOriginator;
	GameManager *redTeamGameManagerOriginator;
	NeutralObjectContainer *nObjectsOriginator;
	GameField *gameFieldOriginator;


	GameManager::GameManagerSnapshot *blueTeamSnapshot;
	GameManager::GameManagerSnapshot *redTeamSnapshot;
	NeutralObjectContainer::NObjectsContainerSnapshot *nObjectsSnapshot;
	GameField::GameFieldSnapshot *gameFieldSnapshot;

	std::ofstream saveFile;
	std::ifstream loadFile;

public:
	GameLoaderSaver(GameManager *blueTeam, GameManager *redTeam, NeutralObjectContainer *nObjects, GameField *field);
	~GameLoaderSaver() {
		saveFile << saveState.size() << std::endl;
		for (auto &st : saveState) {
			saveFile << st << " ";
		}
		saveFile << std::endl;

		saveFile << *gameFieldSnapshot;
		saveFile << *blueTeamSnapshot;
		saveFile << *redTeamSnapshot;
		saveFile << *nObjectsSnapshot;
		

		saveFile.close();
		loadFile.close();
	};

	void saveGame(std::vector<int> &state);
	std::vector<int> &loadGame();
};



