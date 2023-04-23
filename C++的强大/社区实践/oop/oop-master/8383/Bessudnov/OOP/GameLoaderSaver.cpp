#include "pch.h"
#include "GameLoaderSaver.h"
#include "GameManager.h"
#include "GameField.h"
#include "NeutralObject.h"
#include "MyException.h"
#include "Logger.h"
#include <algorithm>


std::vector<int> &GameLoaderSaver::loadGame() {
	if (!gameFieldSnapshot || !redTeamSnapshot || !blueTeamSnapshot || !nObjectsSnapshot) {
		blueTeamSnapshot = new GameManager::GameManagerSnapshot;
		redTeamSnapshot = new GameManager::GameManagerSnapshot;
		nObjectsSnapshot = new NeutralObjectContainer::NObjectsContainerSnapshot;
		gameFieldSnapshot = new GameField::GameFieldSnapshot;

		int saveStatesCount;
		loadFile >> saveStatesCount;
		saveState.resize(saveStatesCount);
		for (auto &st : saveState) {
			loadFile >> st;
		}
		loadFile >> *gameFieldSnapshot;
		loadFile >> *blueTeamSnapshot;
		loadFile >> *redTeamSnapshot;
		loadFile >> *nObjectsSnapshot;
	}

	gameFieldOriginator->loadField(gameFieldSnapshot);
	nObjectsOriginator->loadNObjects(nObjectsSnapshot);
	redTeamGameManagerOriginator->loadGame(redTeamSnapshot);
	blueTeamGameManagerOriginator->loadGame(blueTeamSnapshot);

	return saveState;
}

GameLoaderSaver::GameLoaderSaver(GameManager *blueTeam, GameManager *redTeam, NeutralObjectContainer *nObjects, GameField *field)
	: blueTeamGameManagerOriginator(blueTeam), redTeamGameManagerOriginator(redTeam), nObjectsOriginator(nObjects),
	gameFieldOriginator(field) {
	try {
		saveFile.open("gameSave.txt");
		if (!saveFile.is_open()) {
			throw FileException("Failed to open file", "gameSave.txt", saveFile.rdstate());
		}


		loadFile.open("gameSave.txt");
		if (!loadFile.is_open()) {
			throw FileException("Failed to open file", "gameSave.txt", loadFile.rdstate());
		}


	} catch (FileException &exception) {
		LoggerProxy logger;
		logger.logEvent(new LogEntry(exception.getMes()));
	}
	
}

void GameLoaderSaver::saveGame(std::vector<int> &state) {
	gameFieldSnapshot = gameFieldOriginator->saveField();
	nObjectsSnapshot = nObjectsOriginator->saveObjects();
	redTeamSnapshot = redTeamGameManagerOriginator->saveGame();
	blueTeamSnapshot = blueTeamGameManagerOriginator->saveGame();

	saveState.clear();
	for (auto &par : state) {
		saveState.push_back(par);
	}
}
