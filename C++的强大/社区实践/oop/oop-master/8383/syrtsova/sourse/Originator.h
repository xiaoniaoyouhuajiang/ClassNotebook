#pragma once

#include "Concretememento.h"
#include "fstream"
#include "Rule_1.h"
#include "Rule_2.h"
#include "Game.hpp"

/// Класс Организатора

/**
* Создатель содержит некоторое важное состояние, которое может со временем меняться.
* Он также объявляет метод созранения состояния внутри снимка и метод восстановления из него
*/
class Originator
{
private:
	std::string fout;
	std::ofstream out;
	std::ifstream fin;
public:
	Originator(std::string fout, bool isSave);
	~Originator();

	void takeMemento(Game<Rules>* game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, Units* selectedUnit, int& currNumBase);
	Memento *save(Game<Rules>* game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, Units* selectedUnit, int& currNumBase);
	void restore(Game<Rules>* game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, int& currNumBase);
};