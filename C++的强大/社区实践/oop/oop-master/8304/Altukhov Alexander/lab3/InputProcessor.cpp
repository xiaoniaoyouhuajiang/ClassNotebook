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


bool InputProcessor::checkArguments(std::vector<std::string>& args, int numberOfArgs) {

	if (args.size() != (numberOfArgs + 1))
		return false;
	for (int i = 1; i < args.size(); i++) {
		try {
			int arg = std::stoi(args[i]);
			if (!(arg >= 0)) {
				std::cout << "Ошибка! Некорректные аргументы\n";
				return false;
			}
		}
		catch (const std::invalid_argument& ia) {
			std::cerr << "Ошибка! Некорректный аргумент: " << ia.what() << '\n';
			return false;
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
				std::cout << "Ошибка! Некорректные аргументы\n";
				return false;
			}
			attack(args);

		}
		else if(args[0] == "move") {
			if (!checkArguments(args, 3)) {
				std::cout << "Ошибка! Некорректные аргументы\n";
				return false;
			}
			move(args);
		}
		else if (args[0] == "create") {
			if (!checkArguments(args, 2)) {
				std::cout << "Ошибка! Некорректные аргументы\n";
				return false;
			}
			create(args);
		}
		else if (args[0] == "baseLog") {
			baseLog();
		}
		else if (args[0] == "unitInfo") {
			if (!checkArguments(args, 1)) {
				std::cout << "Ошибка! Некорректные аргументы\n";
				return false;
			}
			unitInfo(args);
		}
		else if (args[0] == "exit") {
			return true;
		}
		else {
			std::cout << "Неизвестная команда\n";
		}
	}
	
	return false;
}


void InputProcessor::attack(std::vector<std::string>& args) {

	AttackCommand command(base, std::stoi(args[1]), std::stoi(args[2]));
	command.execute();
}

void InputProcessor::move(std::vector<std::string>& args) {

	MoveCommand command(base, std::stoi(args[1]), std::stoi(args[2]), std::stoi(args[3]));
	command.execute();
}

void InputProcessor::create(std::vector<std::string>& args) {

	CreateCommand command(base, std::stoi(args[1]), std::stoi(args[2]));
	command.execute();
}

void InputProcessor::baseLog() {
	BaseLogCommand command(base);
	command.execute();
}

void InputProcessor::unitInfo(std::vector<std::string>& args) {
	UnitInfoCommand command(base, std::stoi(args[1]));
	command.execute();
}