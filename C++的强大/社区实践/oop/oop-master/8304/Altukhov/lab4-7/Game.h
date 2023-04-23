#pragma once
#include "Field.h"
#include "Base.h"
#include "InputProcessor.h"
#include "ProxyLog.h"

template <typename Rule>
class Game
{
private:
	static Game* instance;
	Field* field;
	InputProcessor inputProcessor;
	Base* base1;
	Base* base2;
	ProxyLog* log;
	bool activeGame = false;
	Game() {
		
	
	};
public:
	static Game* getGame() {

		static Game* instance = new Game;
		return instance;

	}

	void startGame() {
		
		if (activeGame)
			return;
		activeGame = true;
		log = new ProxyLog(true, true, true, false);

		field = new Field(10, 10);
		field->addLog(log);
		base1 = field->createAndSetBase(field, 1);
		base1->addLog(log);
		base2 = field->createAndSetBase(field, 2);
		base2->addLog(log);
		inputProcessor = InputProcessor(base1, base2, field);
		inputProcessor.addLog(log);
		std::cout << "Поддерживаются команды вида:\nattack attackerId targetId\nmove unitId xCoord yCoord\ncreate typeId lvl\nbaseLog\nunitInfo id\nnextTurn\nshowField\nsave fileName\nload fileName\nexit\n";

		std::string input;
		//std::getline(std::cin, input);
		int res = 0;
		while (!(res = Rule::checkGameEnd(base1, base2))) {
			std::getline(std::cin, input);
			bool timeToExit = inputProcessor.processString(input);
			if (timeToExit)
				break;
		}
		if (res == 1) {
			log << (std::string)"Победил игрок 1\n";
		}
		if (res == 2) {
			log << (std::string)"Победил игрок 2\n";
		}
		deleteGame();
		std::cout << "Начать новую игру? 1 - да, 0 - нет\n";
		int answer = 0;
		std::cin >> answer;
		if (answer == 1) {
			startGame();
		}
	
	}

	int checkGameEnd() {
		return Rule::checkGameEnd(this);
	
	}

	void deleteGame() {
		
		if (!activeGame)
			return;
		activeGame = false;
		field->deleteBase(base1);
		field->deleteBase(base2);
		delete field;
		delete log;
	}
	~Game() {
		deleteGame();
	}
};

