#include <locale>
#include <iostream>
#include "Field.h"
#include "Base.h"
#include <sstream>
#include "InputProcessor.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	srand(2);

	//демонстрация 1, создание поля, базы, юнита, взаимодействие с нейтральным объектом
	/*Field* f = new Field(3, 7);
	f->visualizeField();
	Base* base = f->createAndSetBase(f);
	f->visualizeField();
	Unit* unit1 = base->createAndSetUnit(UnitTypes::HORSEMAN, 1, 1, 2);//f->createAndSetUnit(UnitTypes::HORSEMAN, 1, 1, 2, f);
	f->visualizeField();
	std::cout << "Атака: " << unit1->getAttack() << " " << unit1->getAttackBuff() << "\n";
	unit1->doMove(1, 1);
	f->visualizeField();
	std::cout << "Атака: " << unit1->getAttack() << " " << unit1->getAttackBuff() << "\n";
	unit1->doMove(1, 5);
	f->visualizeField();
	std::cout << "Атака: " << unit1->getAttack() << " " << unit1->getAttackBuff() << "\n";
	f->deleteBase(base);
	f->visualizeField();
	delete f; */




	//демонстрация 2, создание поля и нескольких юнитов, взаимодействие между юнитами и ландшафтом
	/*Field* f = new Field(10, 10);
	f->visualizeField();
	Base* base = f->createAndSetBase(f);
	f->visualizeField();
	base->createAndSetUnit(UnitTypes::HORSEMAN, 1);
	base->createAndSetUnit(UnitTypes::RANGE, 1);
	f->visualizeField();

	base->writeBaseState();

	std::cout << "Атака: " << base->getUnit(1)->getAttack() << "\n";

	//if (base->getUnit(1)->doAttack(base->getUnit(2))) {
	//	std::cout << "unit1 win!\n";
	//}

	f->deleteBase(base);
	//f->visualizeField();
	delete f;*/


	//демонстрация 3, создание поля и юнита, передвижение юнита, взаимодействие с ландшафтом
	/*Field* f = new Field(3, 7);
	Base* base = f->createAndSetBase(f);
	f->visualizeField();

	Unit* unit1 = base->createAndSetUnit(UnitTypes::HORSEMAN, 1, 1, 2);
	std::cout << "Атака: " << base->getUnit(1)->getAttack() << "\n";
	f->visualizeField();
	unit1->doMove(0, 4);
	std::cout << "Атака теперь: " << base->getUnit(1)->getAttack() << "\n";
	f->visualizeField();
	f->deleteBase(base);
	delete f;*/


	Field* f = new Field(10, 10);
	Base* base = f->createAndSetBase(f);
	f->visualizeField();

	InputProcessor inputProcessor(base);

	std::cout << "Поддерживаются команды вида:\nattack attackerId targetId\nmove unitId xCoord yCoord\ncreate typeId lvl\nbaseLog\nunitInfo id\nexit\n";

	std::string input;
	std::getline(std::cin, input);

	while (!inputProcessor.processString(input)) {
		std::getline(std::cin, input);
	}

	f->deleteBase(base);
	delete f;

	return 0;
}


