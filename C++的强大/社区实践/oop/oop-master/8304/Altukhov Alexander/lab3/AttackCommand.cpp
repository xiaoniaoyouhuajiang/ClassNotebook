#include "AttackCommand.h"

AttackCommand::AttackCommand(Base*& myBase, int arg1, int arg2) {
	this->myBase = myBase; 
	args.push_back(arg1); 
	args.push_back(arg2); 
}


void AttackCommand::execute() {//args[attackerId, targetId]
	
	Unit* unit1 = myBase->getUnit(args[0]);
	Unit* unit2 = myBase->getUnit(args[1]);
	if (!unit1 || !unit2) {
		std::cout << "Юнита с таким id не существует!\n";
		return;
	}
	std::cout << "Юнит " << args[0] << " атакует юнита " << args[1] << "!\n";
	//myBase->getUnit(args[0])->doAttack(myBase->getUnit(args[1]));
	unit1->doAttack(unit2);
	myBase->getParentField()->visualizeField();
}