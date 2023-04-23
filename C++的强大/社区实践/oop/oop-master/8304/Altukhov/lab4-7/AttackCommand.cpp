#include "AttackCommand.h"

AttackCommand::AttackCommand(Base*& myBase, Base*& enemyBase, int arg1, int arg2) {
	this->myBase = myBase; 
	this->enemyBase = enemyBase;
	args.push_back(arg1); 
	args.push_back(arg2); 
}


void AttackCommand::execute() {//args[attackerId, targetId]

	Unit* unit1 = myBase->getUnit(args[0]);

	if (unit1 && unit1->getAttacked()) {
		log << (std::string)"Юнит уже атаковал в этом ходу!\n";
		return;
	}

	if (args[1] == 0) {//атака базы
		if (!unit1 ) {
			//std::cout << "Юнита с таким id не существует!\n";
			log << (std::string)"Юнита с таким id не существует!\n";
			return;
		}
		log << ("Юнит " + std::to_string(args[0]) + " атакует базу!\n");
		unit1->doAttackOnBase(enemyBase);
		myBase->getParentField()->visualizeField();
		return;
	}
	
	Unit* unit2 = enemyBase->getUnit(args[1]);
	if (!unit1 || !unit2) {
		//std::cout << "Юнита с таким id не существует!\n";
		log << (std::string)"Юнита с таким id не существует!\n";
		return;
	}
	//std::cout << "Юнит " << args[0] << " атакует юнита " << args[1] << "!\n";
	log << ("Юнит " + std::to_string(args[0]) + " атакует юнита " + std::to_string(args[1]) + "!\n");
	//myBase->getUnit(args[0])->doAttack(myBase->getUnit(args[1]));
	unit1->doAttack(unit2);
	myBase->getParentField()->visualizeField();
}