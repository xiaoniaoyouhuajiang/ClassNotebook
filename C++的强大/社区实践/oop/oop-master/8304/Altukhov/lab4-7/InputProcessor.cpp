#include "InputProcessor.h"
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

std::vector<std::string> InputProcessor::split(const std::string& s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		 elems.push_back(std::move(item));
	}
	return elems;
}


bool InputProcessor::checkArguments(std::vector<std::string>& args, int numberOfArgs, bool stringArg) {

	if (args.size() != (numberOfArgs + 1))
		return false;
	for (int i = 1; i < args.size(); i++) {

		if (stringArg) {
			//nothing
		}
		else {
			try {
				int arg = std::stoi(args[i]);
				if (!(arg >= 0)) {
					//std::cout << "Ошибка! Некорректные аргументы\n";
					log << (std::string)"Ошибка! Некорректные аргументы\n";
					return false;
				}
			}
			catch (const std::invalid_argument& ia) {
				std::cerr << "Ошибка! Некорректный аргумент: " << args[i] << ". Тип ошибки: " << ia.what() << '\n';
				return false;
			}
		}
	}
	return true;

}


bool InputProcessor::processString(std::string& input) {//true - exit

	auto args = split(input, ' ');
	//for (int i = 0; i < args.size(); i++) {
	//	std::cout << args[i] << ";;;\n";
	//}
	if (args.size() >= 1) {
		if (args[0] == "attack") {
			if (!checkArguments(args, 2)) {
				//std::cout << "Ошибка! Некорректные аргументы\n";
				log << (std::string)"Ошибка! Некорректные аргументы\n";
				return false;
			}
			attack(args);

		}
		else if(args[0] == "move") {
			if (!checkArguments(args, 3)) {
				//std::cout << "Ошибка! Некорректные аргументы\n";
				log << (std::string)"Ошибка! Некорректные аргументы\n";
				return false;
			}
			move(args);
		}
		else if (args[0] == "create") {
			if (!checkArguments(args, 2)) {
				//std::cout << "Ошибка! Некорректные аргументы\n";
				log << (std::string)"Ошибка! Некорректные аргументы\n";
				return false;
			}
			create(args);
		}
		else if (args[0] == "baseLog") {
			baseLog();
		}
		else if (args[0] == "unitInfo") {
			if (!checkArguments(args, 1)) {
				//std::cout << "Ошибка! Некорректные аргументы\n";
				log << (std::string)"Ошибка! Некорректные аргументы\n";
				return false;
			}
			unitInfo(args);
		}
		else if (args[0] == "save") {
			if (!checkArguments(args, 1, true)) {
				//std::cout << "Ошибка! Некорректные аргументы\n";
				log << (std::string)"Ошибка! Некорректные аргументы\n";
				return false;
			}
			save(args);
		}
		else if (args[0] == "load") {
			if (!checkArguments(args, 1, true)) {
				//std::cout << "Ошибка! Некорректные аргументы\n";
				log << (std::string)"Ошибка! Некорректные аргументы\n";
				return false;
			}
			load(args);
		}
		else if (args[0] == "nextTurn") {
			endOfTurn();
		}
		else if (args[0] == "showField") {
			showField();
		}
		else if (args[0] == "exit") {
			return true;
		}
		else {
			//std::cout << "Неизвестная команда\n";
			log << (std::string)"Неизвестная команда\n";
		}
	}
	
	return false;
}


void InputProcessor::attack(std::vector<std::string>& args) {

	AttackCommand command(state->getRightBase(), state->getOtherBase(), std::stoi(args[1]), std::stoi(args[2]));
	command.addLog(log);
	command.execute();
}

void InputProcessor::move(std::vector<std::string>& args) {

	MoveCommand command(state->getRightBase(), std::stoi(args[1]), std::stoi(args[2]), std::stoi(args[3]));
	command.addLog(log);
	command.execute();
}

void InputProcessor::create(std::vector<std::string>& args) {

	CreateCommand command(state->getRightBase(), std::stoi(args[1]), std::stoi(args[2]));
	command.addLog(log);
	command.execute();
}

void InputProcessor::baseLog() {
	BaseLogCommand command(state->getRightBase());
	command.addLog(log);
	command.execute();
}

void InputProcessor::unitInfo(std::vector<std::string>& args) {
	UnitInfoCommand command(state->getRightBase(), std::stoi(args[1]));
	command.addLog(log);
	command.execute();
}

void InputProcessor::save(std::vector<std::string>& args) {
	SaveCommand command(state->getRightBase(), state->getOtherBase(), args[1]);
	command.addLog(log);
	command.execute();
}

void InputProcessor::load(std::vector<std::string>& args) {
	LoadCommand command(state->getRightBase(), state->getOtherBase(), args[1]);
	command.addLog(log);
	//command.execute();
	int turn = command.specExecute();
	if (turn == 1) {
		log << (std::string)"Ход игрока 1:\n";
		onlyChangeState(1);
	}
	else if (turn == 2) {
		log << (std::string)"Ход игрока 2:\n";
		onlyChangeState(2);
	}
}

void InputProcessor::addLog(ProxyLog* log)
{
	this->log = log;
}

void InputProcessor::endOfTurn()
{
	if (curPlayer == 1) {
		log << (std::string)"Конец хода игрока 1. Ход игрока 2:\n";
		changeState(2);
	}
	else if (curPlayer == 2) {
		log << (std::string)"Конец хода игрока 2. Ход игрока 1:\n";
		changeState(1);
	}
}

void InputProcessor::showField() {
	this->field->visualizeField();
}

void InputProcessor::changeState(int playerNum)
{
	if (playerNum == 1) {
		base->prepareToNextTurn();
		delete state;
		state = new FirstPlayerState(base, base2);
		curPlayer = playerNum;
	}
	else if (playerNum == 2) {
		base2->prepareToNextTurn();
		delete state;
		state = new SecondPlayerState(base2, base);
		curPlayer = playerNum;
	}
}
void InputProcessor::onlyChangeState(int playerNum)
{
	if (playerNum == 1) {
		delete state;
		state = new FirstPlayerState(base, base2);
		curPlayer = playerNum;
	}
	else if (playerNum == 2) {
		delete state;
		state = new SecondPlayerState(base2, base);
		curPlayer = playerNum;
	}
}